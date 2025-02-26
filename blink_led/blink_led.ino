// Simple Blink LED Program
int ledPin = 9;  // The built-in LED on most Arduino boards

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
    Serial.println("Hello World, Arduino!");
}

void loop() {
    digitalWrite(ledPin, HIGH);  // Turn LED on
    delay(1000);                 // Wait for 1 second
    digitalWrite(ledPin, LOW);   // Turn LED off
    delay(1000);                 // Wait for 1 second
    delay(1000);
    Serial.println("Looping...");
}
