#include <avr/interrupt.h>
#include <avr/io.h>

// Pinovi
#define BUTTON1 2 // Eksterni prekid INT0
#define BUTTON2 3 // Eksterni prekid INT1
#define PIR_SENSOR 18 // PIR senzor prekid
#define LED1 5
#define LED2 6

volatile bool button1Pressed = false;
volatile bool button2Pressed = false;
volatile bool motionDetected = false;

void setup() {
    Serial.begin(9600);
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);
    pinMode(PIR_SENSOR, INPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    
    // Postavljanje eksternih prekida
    attachInterrupt(digitalPinToInterrupt(BUTTON1), button1ISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON2), button2ISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIR_SENSOR), pirISR, RISING);
    
    // Timer prekid
    cli(); // Isključivanje globalnih prekida
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mod, 1024 prescaler
    OCR1A = 15624; // 1 sekunda
    TIMSK1 |= (1 << OCIE1A);
    sei(); // Uključivanje globalnih prekida
}

void loop() {
    if (button1Pressed) {
        cli(); // Onemogući druge prekide
        Serial.println("Tipka 1 pritisnuta");
        digitalWrite(LED1, !digitalRead(LED1));
        sei(); // Ponovno omogući prekide
        button1Pressed = false;
    }
    if (button2Pressed) {
        Serial.println("Tipka 2 pritisnuta");
        digitalWrite(LED2, !digitalRead(LED2));
        button2Pressed = false;
    }
    if (motionDetected) {
        Serial.println("Kretanje detektirano!");
        digitalWrite(LED1, HIGH);
        delay(5000); // Drži LED upaljenom 5 sekundi
        digitalWrite(LED1, LOW);
        motionDetected = false;
    }
}

// ISR za tipkala
void button1ISR() {
    button1Pressed = true;
}
void button2ISR() {
    button2Pressed = true;
}

// ISR za PIR senzor
void pirISR() {
    motionDetected = true;
}

// ISR za timer
ISR(TIMER1_COMPA_vect) {
    Serial.println("Timer prekid - 1 sekunda prošla");
}
