#include <Stepper.h>

// Number of steps per internal motor revolution 
const int stepsPerRevolution = 2048;

// Wiring configuration based on the ULN2003 interface
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Set the speed to 10 rpm:
  myStepper.setSpeed(10);
}

void loop() {
  // Step one revolution in one direction:
  myStepper.step(stepsPerRevolution);
  delay(500);

  // Step one revolution in the other direction:
  myStepper.step(-stepsPerRevolution);
  delay(500);
}
