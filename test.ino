#include "HX711.h"
#include <SoftwareSerial.h>

#define DOUT  3
#define CLK  2

HX711 scale;
SoftwareSerial espSerial(18, 19); // RX, TX (povezano s ESP-01)

float previousWeight = 0.0;
const float threshold = 5.0; // prag za promjenu težine

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare();  // postavi trenutnu vrijednost na 0

  Serial.println("Scale ready");
  espSerial.println("AT");
  delay(1000);
}

void loop() {
  if (scale.is_ready()) {
    float weight = scale.get_units(10);

    if (abs(weight - previousWeight) > threshold) {
      previousWeight = weight;

      Serial.print("New weight: ");
      Serial.println(weight);

      // Formatiranje i slanje poruke ESP-u
      String message = "Weight: " + String(weight, 2) + " g";
      sendToESP(message);
    }
  } else {
    Serial.println("Scale not ready");
  }

  delay(1000);
}

void sendToESP(String msg) {
  // Ovime se šalje naredba ESP-u, pretpostavlja se da ESP šalje HTTP zahtjev
  espSerial.println(msg);
}