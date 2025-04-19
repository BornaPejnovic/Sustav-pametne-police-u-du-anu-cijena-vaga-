/**
 * @file scale_esp_communication.ino
 * @brief Program for measuring weight using HX711 and sending data to ESP-01 via SoftwareSerial.
 * 
 * This Arduino sketch uses the HX711 load cell amplifier to read weight measurements and sends
 * them to an ESP-01 module using AT commands through a software serial connection.
*/

#include "HX711.h"
#include <SoftwareSerial.h>
#include <TimerOne.h>
 
/// Data pin for HX711
#define DOUT  3
 
/// Clock pin for HX711
#define CLK  2

/// LED pin
#define LED  7
 
/// HX711 scale object for interfacing with load cell
HX711 scale;
 
/// Software serial communication with ESP-01 (RX = 18, TX = 19)
SoftwareSerial espSerial(18, 19);
 
/// Last measured weight
float previousWeight = 0.0;
 
/// Minimum change in weight required to trigger a new transmission (in grams)
const float threshold = 5.0;

/// Flag for the blink interrupt
bool blinkFlag = false;

/// Minimum mass that needs to be on the scale
const float minimalMass = 1000.0;
 
/**
  * @brief Arduino setup function.
  * 
  * Initializes serial communication, HX711 scale, and ESP-01 communication.
*/
void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

  pinMode(LED, OUTPUT);

  Timer1.initialize(500000);  // half second interval
 
  scale.begin(DOUT, CLK);
  scale.set_scale(0.42);
  scale.tare();  ///< Set the current load cell value as zero
 
  Serial.println("Scale ready");
  espSerial.println("AT");
  delay(1000);
}
 
/**
  * @brief Arduino main loop function.
  * 
  * Reads weight from HX711 and sends it to the ESP-01 module if the change exceeds the threshold.
*/
void loop() {
  scale.wait_ready();
  float weight = scale.get_units();

  if (abs(weight - previousWeight) > threshold) {
    previousWeight = weight;
    String message = "New weight: " + String(weight) + " g";
    Serial.println(message);

    // Send message to ESP and blink LED if mass falls below the minimum
    if (weight < minimalMass && blinkFlag == false) {
      sendToESP("More products needed!");
      blinkFlag = true;
      Timer1.attachInterrupt(blink);
    } 
    // Send message to ESP and stop blinking LED if mass returns to above the minimum
    else if (weight >= minimalMass && blinkFlag == true) {
      sendToESP("Products restocked!");
      blinkFlag = false;
      Timer1.detachInterrupt();
      digitalWrite(LED, LOW);
    }
    
  }
}
 
/**
  * @brief Sends a message to the ESP-01 module via SoftwareSerial.
  * 
  * @param msg Message string to be sent.
*/
void sendToESP(String msg) {
  espSerial.println(msg);
}

/**
  * @brief Blinks the LED
  * 
  * Turns the LED off if it was on and vice versa.
*/
void blink() {
  digitalWrite(LED, !digitalRead(LED));
}