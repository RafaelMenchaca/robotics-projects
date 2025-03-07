// int buttonPin = 7;
// int ledPin = 9;
// int buttonState = 0;
// int lastButtonState = HIGH;
// bool ledState = false;

// void setup() {
//   pinMode(buttonPin, INPUT_PULLUP);
//   pinMode(ledPin, OUTPUT);
// }

// void loop() {
//   buttonState = digitalRead(buttonPin);

//   if (buttonState == LOW && lastButtonState == HIGH) {  // Detect new press
//     ledState = !ledState;  // Toggle LED state
//     digitalWrite(ledPin, ledState ? HIGH : LOW);
//     delay(200);  // Debounce delay
//   }
  
//   lastButtonState = buttonState;  // Store last state
// }

int buttonPin = 7;
int redLed = 9;
int greenLed = 10;
int yellowLed = 11;
int buttonState = 0;
int lastButtonState = HIGH;
int ledMode = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {  
    ledMode++;  // Move to next mode
    if (ledMode > 3) ledMode = 0;  // Reset after 3rd press

    // Update LED states
    if (ledMode == 0) {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, LOW);
      digitalWrite(yellowLed, LOW);
    } else if (ledMode == 1) {
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);
      digitalWrite(yellowLed, LOW);
    } else if (ledMode == 2) {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
      digitalWrite(yellowLed, LOW);
    } else if (ledMode == 3) {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, LOW);
      digitalWrite(yellowLed, HIGH);
    }
    delay(200);  // Debounce delay
  }

  lastButtonState = buttonState;
}
