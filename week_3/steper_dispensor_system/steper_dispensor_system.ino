#include <Stepper.h>

const int stepsPerRevolution = 2048; // 1 full rotation (28BYJ-48)
const int dispenseSteps = 512;       // 1/4 rotation (adjust as needed)

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

const int buttonPin = 2;
int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  myStepper.setSpeed(10);  // Adjust speed (RPM)
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Debounce the button
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && buttonState == HIGH) {
      Serial.println("Dispensing...");
      myStepper.step(dispenseSteps);
      Serial.println("Done.");
    }
    buttonState = reading;
  }

  lastButtonState = reading;
}
