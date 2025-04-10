// --- Libraries ---
#include <Servo.h> // Include the Servo library for controlling the ultrasonic sensor's servo motor

// --- Motor A Pins ---
const int enA = 6;  // Enable pin for Motor A (PWM)
const int in1 = 9;  // Control pin 1 for Motor A
const int in2 = 8;  // Control pin 2 for Motor A

// --- Motor B Pins ---
const int enB = 5;  // Enable pin for Motor B (PWM)
const int in3 = 4;  // Control pin 1 for Motor B
const int in4 = 3;  // Control pin 2 for Motor B

// --- Ultrasonic Sensor Pins ---
const int trigPin = 12; // Trigger pin for ultrasonic sensor
const int echoPin = 11; // Echo pin for ultrasonic sensor

// --- Servo Motor Pin ---
const int servoPin = 7; // Control pin for the servo motor
Servo scanner;          // Create a Servo object to control the scanner

// --- Buzzer Pin ---
const int buzzerPin = 10; // Control pin for the buzzer

// --- Initial Setup ---
void setup() {
  // Initialize motor control pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize buzzer pin as output
  pinMode(buzzerPin, OUTPUT);

  // Attach the servo motor to its control pin
  scanner.attach(servoPin);

  // Set initial motor speeds
  setMotorSpeed(170, 170); // Set both motors to a speed of 170 (range: 0-255)
}

// --- Main Loop ---
void loop() {
  // Measure distance to the nearest object
  long distance = readDistance();

  // Control the buzzer based on the measured distance
  controlBuzzer(distance);

  // Obstacle avoidance behavior
  if (distance > 0 && distance < 15) {
    // If an obstacle is detected within 15 cm:
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
    // If path is clear, move forward
    moveForward();
  }

  delay(100); // Short delay before the next loop iteration
}

// --- Function Definitions ---

// Set the speed for both motors
void setMotorSpeed(int speedA, int speedB) {
  analogWrite(enA, speedA);
  analogWrite(enB, speedB);
}

// Measure distance using the ultrasonic sensor
long readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // Convert duration to distance in centimeters
}

// Control the buzzer based on distance
void controlBuzzer(long distance) {
  if (distance > 0 && distance < 5) {
    tone(buzzerPin, 1000); // Constant beep for very close obstacles
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
    noTone(buzzerPin); // No sound if distance is safe
  }
}

// Scan surroundings and choose direction to turn
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

  // Decide direction based on measured distances
  if (rightDist > leftDist) {
    return "RIGHT";
  } else {
    return "LEFT";
  }
}

// Move the robot forward
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Move the robot backward
void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Turn the robot to the right
void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Turn the robot to the left
void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Stop both motors
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
