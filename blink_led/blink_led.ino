// Simple Blink LED Program
int yellow = 9;  // The built-in LED on most Arduino boards
int red = 8;
int green = 10;

void setup() {
    pinMode(yellow, OUTPUT);
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    Serial.begin(9600);
    Serial.println("Hello World, Arduino!");
}

void loop() {
    digitalWrite(yellow, HIGH);  // Turn LED on
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    delay(1000);                 // Wait for 1 second
    digitalWrite(yellow, LOW);   // Turn LED off
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    delay(1000);                 // Wait for 1 second
    Serial.println("Looping...");
}
