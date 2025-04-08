#include <TimerOne.h>

// Definiramo pinove za tipkala i LED diode
const int buttonPin1 = 2;         // Tipkalo 1 na pinu 2
const int buttonPin2 = 3;         // Tipkalo 2 na pinu 3
const int ledPin = 13;            // LED na pinu 13
const int potentiometerPin = A0;  // Potenciometar na analognom pinu A0
const int motionPin = 18;         // Senzor kretanja na pinu 8

// Globalne varijable za praćenje stanja
volatile bool button1Pressed = false;
volatile bool button2Pressed = false;
volatile bool motionDetected = false;
volatile bool timerFlag = false;

// Timer za generiranje prekida (prvo se inicijalizira u setup)
unsigned long lastMillis = 0;
const unsigned long timerInterval = 1000; // 1 sekunda

void setup() {
  // Postavljamo pinove
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(motionPin, INPUT);
  
  // Pokrećemo serijsku komunikaciju
  Serial.begin(9600);
  
  // Povezivanje prekida s pinovima
  attachInterrupt(digitalPinToInterrupt(buttonPin1), button1ISR, FALLING); // Prekid za tipkalo 1
  attachInterrupt(digitalPinToInterrupt(buttonPin2), button2ISR, FALLING); // Prekid za tipkalo 2
  attachInterrupt(digitalPinToInterrupt(motionPin), motionSensorISR, LOW); // Prekid za potenciometar
  
  // Pokrećemo timer interrupt
  Timer1.initialize(1000000); // 1 sekunda
  Timer1.attachInterrupt(timerISR); // Timer prekid
}

void loop() {
  // Provodimo neke radnje unutar glavne petlje
  if (button1Pressed) {
    Serial.println("Tipkalo 1 pritisnuto");
    button1Pressed = false; // Resetiranje flag-a
  }
  
  if (button2Pressed) {
    Serial.println("Tipkalo 2 pritisnuto");
    button2Pressed = false; // Resetiranje flag-a
  }

  if (motionDetected) {
    Serial.println("Kretanje detektirano");
    button2Pressed = false; // Resetiranje flag-a
  }
  
  if (timerFlag) {
    noInterrupts();  // Postavljanje prekida na najveći prioritet
    Serial.print("Vrijednost na potenciometru je: ");
    Serial.println(analogRead(potentiometerPin)); // Ispisivanje vrijednosti na potenciometru
    digitalWrite(ledPin, !digitalRead(ledPin)); // Bljeskanje LED-a
    timerFlag = false; // Resetiranje timer flag-a
    interrupts(); // Vraćanje ostalih prekida
  }
}

// ISR za tipkalo 1
void button1ISR() {
  button1Pressed = true;
}

// ISR za tipkalo 2
void button2ISR() {
  button2Pressed = true;
}

// ISR za timer
void timerISR() {
  timerFlag = true;
}

// ISR za timer
void motionSensorISR() {
  motionDetected = true;
}