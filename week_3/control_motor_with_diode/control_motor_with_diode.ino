const int motorPin = 9;  // PWM pin to control transistor base

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Ramp motor speed up
  for (int speed = 0; speed <= 255; speed += 5) {
    analogWrite(motorPin, speed);
    delay(300);
  }

  // Ramp motor speed down
  for (int speed = 255; speed >= 0; speed -= 5) {
    analogWrite(motorPin, speed);
    delay(300);
  }

  delay(1000);
}
