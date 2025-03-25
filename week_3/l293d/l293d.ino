// const int enA = 10;   // EN1 - motor speed control
// const int in1 = 8;    // IN1 - motor direction
// const int in2 = 9;    // IN2 - motor direction

// void setup() {
//   pinMode(enA, OUTPUT);
//   pinMode(in1, OUTPUT);
//   pinMode(in2, OUTPUT);
// }

// void loop() {
//   // Forward
//   digitalWrite(in1, HIGH);
//   digitalWrite(in2, LOW);
//   analogWrite(enA, 200);  // PWM speed (0–255)
//   delay(2000);

//   // Stop
//   analogWrite(enA, 0);
//   delay(1000);

//   // Reverse
//   digitalWrite(in1, LOW);
//   digitalWrite(in2, HIGH);
//   analogWrite(enA, 200);
//   delay(2000);

//   // Stop
//   analogWrite(enA, 0);
//   delay(1000);
// }

// Coil control pins
int in1 = 8;   // IN1
int in2 = 9;   // IN2
int in3 = 12;  // IN3
int in4 = 11;  // IN4

int delayTime = 5; // Speed (lower is faster)

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // Rotate clockwise
  for (int i = 0; i < 512; i++) {
    step1();
    step2();
    step3();
    step4();
  }

  delay(1000);

  // Rotate counter-clockwise
  for (int i = 0; i < 512; i++) {
    step4();
    step3();
    step2();
    step1();
  }

  delay(1000);
}

void step1() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(delayTime);
}
void step2() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(delayTime);
}
void step3() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(delayTime);
}
void step4() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(delayTime);
}
