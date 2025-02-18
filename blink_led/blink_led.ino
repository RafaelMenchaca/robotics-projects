// Simple Blink LED Program
int ledPin = 13;  // The built-in LED on most Arduino boards

void setup() {
    pinMode(ledPin, OUTPUT);
}

void loop() {
    digitalWrite(ledPin, HIGH);  // Turn LED on
    delay(1000);                 // Wait for 1 second
    digitalWrite(ledPin, LOW);   // Turn LED off
    delay(1000);                 // Wait for 1 second
}
