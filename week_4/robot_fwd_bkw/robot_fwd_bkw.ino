#include <Servo.h>

// Motor A
const int enA = 6; // 6 instead of 10 SERVO library makes error in PWM 9 and 10
const int in1 = 9;
const int in2 = 8;

// Motor B
const int enB = 5;
const int in3 = 4;
const int in4 = 3;

// Ultrasonic Sensor
const int trigPin = 12;
const int echoPin = 11;

// Servo
const int servoPin = 7;

Servo scanner;


// Buzzer
const int buzzerPin = 10;

void setup() {


  // Motor pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Buzzer
  pinMode(buzzerPin, OUTPUT);

  // Servo
  scanner.attach(servoPin);


  analogWrite(enA, 170); // speed from 0 to 250
  analogWrite(enB, 170);

  // digitalWrite(enA, HIGH); 
  // digitalWrite(enB, HIGH);

  Serial.begin(9600);
}

// Function to measure distance
  long readDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    return duration * 0.034 / 2;
  }

  // Smart scan and decision function
  String scanAndChooseDirection() {
    long leftDist, rightDist;

    // Look left
    scanner.write(45);
    delay(400);
    leftDist = readDistance();

    // Look right
    scanner.write(135);
    delay(400);
    rightDist = readDistance();

    // Return to center
    scanner.write(90);
    delay(300);

    // Debug output
    Serial.print("Left: ");
    Serial.print(leftDist);
    Serial.print(" cm | Right: ");
    Serial.print(rightDist);
    Serial.println(" cm");

    if (rightDist > leftDist) {
      return "RIGHT";
    } else {
      return "LEFT";
    }
  }

void loop() {

  

  long duration, distance;

  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Buzzer control based on distance
  if (distance > 0 && distance < 5) {
    tone(buzzerPin, 1000);  // Constant beep
  } else if (distance >= 5 && distance < 10) {
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
    delay(100);
  } else if (distance >= 10 && distance < 20) {
    tone(buzzerPin, 1000);
    delay(200);
    noTone(buzzerPin);
    delay(300);
  } else {
    noTone(buzzerPin);  // No sound if safe
  }

  // Obstacle avoidance
  if (distance > 0 && distance < 15) {
    stopMotors();
    delay(500);
    moveBackward();
    delay(800);
    stopMotors();
    delay(500);
    String direction = scanAndChooseDirection();

    if (direction == "LEFT") {
      turnLeft();
      delay(600);
    } else {
      turnRight();
      delay(600);
    }
    stopMotors();
    delay(500);
  } else {
    moveForward();
  }

  delay(100);
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
