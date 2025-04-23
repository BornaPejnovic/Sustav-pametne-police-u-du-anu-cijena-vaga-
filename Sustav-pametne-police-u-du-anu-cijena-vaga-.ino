/**
 * @file scale_esp_communication.ino
 * @brief Program for measuring weight using HX711 and sending data to ESP-01 via SoftwareSerial.
 * 
 * This Arduino sketch uses the HX711 load cell amplifier to read weight measurements and sends
 * them to an ESP-01 module using AT commands through a software serial connection.
*/

#include <HX711.h>
#include <SoftwareSerial.h>
#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>
#include <LowPower.h>

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

// LCD object with I2C communication for displaying the current weight
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
/// Last measured weight
float previousWeight = 0.0;
 
/// Minimum change in weight required to trigger a new transmission (in grams)
const float threshold = 5.0;

/// Flag for the blink interrupt
bool blinkFlag = false;

/// Minimum mass that needs to be on the scale
const float minimalMass = 1000.0;

/// Flag for waking up the controller
volatile bool hx711Ready = false;
 
/**
  * @brief Arduino setup function.
  * 
  * Initializes ESP-01 communication, pin modes, HX711 scale and I2C LCD.
*/
void setup() {
  espSerial.begin(9600);

  pinMode(LED, OUTPUT);

  Timer1.initialize(500000);  // half second interval

  attachInterrupt(digitalPinToInterrupt(DOUT), hx711ISR, FALLING);  // interrupt for wake-up
 
  scale.begin(DOUT, CLK);
  scale.set_scale(0.42);
  scale.tare();  // set the current load cell value as zero
 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Scale Ready");

  espSerial.println("AT");
  delay(1000);
}
 
/**
  * @brief Arduino main loop function.
  * 
  * Reads weight from HX711 and sends it to the ESP-01 module if the change exceeds the threshold.
*/
void loop() {
  if (!hx711Ready) {
    // Sleep until HX711 sets DOUT low (data ready)
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  }

  // Clear the flag
  hx711Ready = false;

  // Proceed with reading the scale
  scale.wait_ready();
  float weight = scale.get_units();

  if (abs(weight - previousWeight) > threshold) {
    previousWeight = weight;

    // checks if scale is not calibrated
    if (weight < 0) {
      String message = "Recalibration needed!";
      sendToESP(message);
      displayMessage(message);
      Timer1.attachInterrupt(blink);  // blinks the LED
      while(true);    // stops the arduino
    }

    // checks if scale is over capacity
    if (weight > 5000) {
      displayMessage("Scale over capacity!");
    } else {
      displayWeight(weight);

      // Send message to ESP and blink LED if mass falls below the minimum
      if (weight <= minimalMass && blinkFlag == false) {
        sendToESP("More products needed!");
        blinkFlag = true;
        Timer1.attachInterrupt(blink);
      } 
      // Send message to ESP and stop blinking LED if mass returns to above the minimum
      else if (weight > minimalMass && blinkFlag == true) {
        sendToESP("Products restocked!");
        blinkFlag = false;
        Timer1.detachInterrupt();
        if (digitalRead(LED) == HIGH) {
          digitalWrite(LED, LOW);   // turns off the LED if it is on
        }
      }
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
  * @brief Interrupt function that sets the wake-up flag to true.
*/
void hx711ISR() {
  hx711Ready = true;
}

/**
  * @brief Blinks the LED
  * 
  * Turns the LED off if it was on and vice versa.
*/
void blink() {
  digitalWrite(LED, !digitalRead(LED));
}

/**
  * @brief LCD communication for displaying weight.
  * 
  * @param weight Weight number to be displayed.
  * 
  * Displays the new weight value when change is detected.
*/
void displayWeight(float weight) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weight:");
  lcd.setCursor(0, 1);
  lcd.print(weight, 1);  // One decimal precision
  lcd.print(" g");
}

/**
  * @brief LCD communication for displaying messages.
  * 
  * @param Message string to be displayed.
  * 
  * Displays the sent message. Checks if the message is too long and moves the next word to the second row. If the message is too long, displays error message.
*/
void displayMessage(String message) {
  lcd.clear();
  lcd.setCursor(0, 0);

  // If the message fits on one line, print and return
  if (message.length() <= 16) {
    lcd.print(message);
    return;
  }

  // Otherwise, split into two lines
  String line1 = "";
  String line2 = "";
  int spaceIndex = 0;

  // Break the message into words
  while (message.length()) {
    int nextSpace = message.indexOf(' ', spaceIndex);
    if (nextSpace == -1) nextSpace = message.length();

    String word = message.substring(spaceIndex, nextSpace);

    // Try adding to line 1
    if (line1.length() + word.length() + 1 <= 16) {
      if (line1.length() > 0) line1 += " ";
      line1 += word;
    } else {
      if (line2.length() > 0) line2 += " ";
      line2 += word;
    }

    // Move to next word
    if (nextSpace >= message.length()) break;
    spaceIndex = nextSpace + 1;
  }

  // Check if message is too long
  if (line2.length() > 16) {
    lcd.print("Message too");
    lcd.setCursor(0, 1);
    lcd.print("long!");
  } 
  // Print both lines
  else {
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }
}