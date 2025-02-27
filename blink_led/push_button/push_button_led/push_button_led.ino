int buttonPin = 7;  // Button connected to pin 7
int ledPin = 9;     // LED connected to pin 9
int buttonState = 0;

void setup() {
    pinMode(ledPin, OUTPUT);      // Set LED as output
    pinMode(buttonPin, INPUT);    // Set button as input
}

void loop() {
    buttonState = digitalRead(buttonPin);  // Read button state

    if (buttonState == HIGH) {  // If button is pressed
        digitalWrite(ledPin, HIGH);  // Turn LED ON
    } else {
        digitalWrite(ledPin, LOW);   // Turn LED OFF
    }
}
