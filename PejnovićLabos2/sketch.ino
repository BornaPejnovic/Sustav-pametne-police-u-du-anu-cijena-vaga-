#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <LowPower.h>

#define LED_PIN 13
#define BUTTON_PIN 2  // INT0 (eksterni prekid)

volatile bool wakeUpFlag = false;

// ISR - Eksterni prekid na INT0
void wakeUp() {
    wakeUpFlag = true;
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Unutarnji pull-up

    // Konfiguracija eksternog prekida na INT0 (pin 2)
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), wakeUp, FALLING);
}

void loop() {
    // LED trepće 5 sekundi
    for (int i = 0; i < 5; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(500);
        digitalWrite(LED_PIN, LOW);
        delay(500);
    }

    // Spavanje dok ne dođe prekid ili protekne 8 sekundi
    wakeUpFlag = false;
    while (!wakeUpFlag) {
        LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    }
}
