#include <LowPower.h>
#include <TimerOne.h>

// Pin za tipku
const int buttonPin = 2; // Tipka na pinu 2

// Zastavica za buđenje kontrolera
volatile bool wakeUpFlag = true;

void setup() {
  // Konfiguracija pinova
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Tipka je povezana na GND
  
  // Omogućavanje prekida na tipki
  attachInterrupt(digitalPinToInterrupt(buttonPin), wakeUp, FALLING); // Buđenje na pad rubu

  // Pokrećemo timer interrupt
  Timer1.initialize(10000000); // 10 sekundi
  Timer1.attachInterrupt(wakeUp); // Timer prekid
}

void loop() {

  if (wakeUpFlag) {
    blink(3);
    wakeUpFlag = false;
    enterSleepMode();
  }

}

// Funkcija za ulazak u Sleep mode
void enterSleepMode() {
  // Prebacivanje mikrokontrolera u Power-down mode
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);  // Sleep dok se ne probudi, isključi ADC i BOD
}

// Funkcija za treptanje lampice
void blink(int blinkCount) {
  for (int i = 0; i < blinkCount; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
  }
}

// ISR za timer
void wakeUp() {
  wakeUpFlag = true;
}