// #include <Servo.h>

// const int trigPin = 12;
// const int echoPin = 11;
// const int servoPin = 7;

// Servo scanner;

// void setup() {
//   Serial.begin(9600);
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);
//   scanner.attach(servoPin);
// }

// void loop() {
//   // Sweep from 0° to 180°
//   for (int angle = 0; angle <= 180; angle += 15) {
//     scanner.write(angle);
//     delay(100); // Give time to move

//     long distance = readDistance();
//     Serial.print("Angle: ");
//     Serial.print(angle);
//     Serial.print("° - Distance: ");
//     Serial.print(distance);
//     Serial.println(" cm");
//   }

//   // Optional: sweep back
//   for (int angle = 180; angle >= 0; angle -= 15) {
//     scanner.write(angle);
//     delay(100);

//     long distance = readDistance();
//     Serial.print("Angle: ");
//     Serial.print(angle);
//     Serial.print("° - Distance: ");
//     Serial.print(distance);
//     Serial.println(" cm");
//   }
// }

// // Function to measure distance
// long readDistance() {
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);

//   long duration = pulseIn(echoPin, HIGH);
//   long distance = duration * 0.034 / 2;
//   return distance;
// }


const int enA = 10;
const int in1 = 9;
const int in2 = 8;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(enA, HIGH);  // Full speed
}

void loop() {
}
