// --- Libraries ---
#include <Servo.h>             // Include the Servo library for controlling the ultrasonic sensor's servo motor
#include <LiquidCrystal.h>     // Include liquid crystal library for LCD

// --- Motor A Pins ---
const int enA = 6;             // Enable pin for Motor A (PWM)
const int in1 = 9;             // Control pin 1 for Motor A
const int in2 = 8;             // Control pin 2 for Motor A

// --- Motor B Pins ---
const int enB = 5;             // Enable pin for Motor B (PWM)
const int in3 = 4;             // Control pin 1 for Motor B
const int in4 = 3;             // Control pin 2 for Motor B

// --- Ultrasonic Sensor Pins ---
const int trigPin = 12;        // Trigger pin for ultrasonic sensor
const int echoPin = 11;        // Echo pin for ultrasonic sensor

// --- Servo Motor Pin ---
const int servoPin = 7;        // Control pin for the servo motor
Servo scanner;                 // Create a Servo object to control the scanner

// --- Buzzer Pin ---
const int buzzerPin = 2;       // Control pin for the buzzer

// --- IR Sensor Pin ---
const int irSensorPin = 10;    // Digital pin for IR obstacle sensor

// --- LED as an eye ---
const int eyeLed = 13;         // LED eye on pin 13

// --- LCD on analog pins A0–A5 ---
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); // (RS, E, D4, D5, D6, D7)

// LCD glitch prevention
String lastLine1 = "";
String lastLine2 = "";

// --- Initial Setup ---
void setup() {
  delay(500); // Give power rails time to stabilize

  // Initialize output pins
  pinMode(eyeLed, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(irSensorPin, INPUT); // IR sensor as input

  // Setup LCD
  lcd.begin(16, 2);
  delay(5);
  lcd.setCursor(0, 0);
  lcd.print("Robie Jr. Ready!");
  delay(1500);
  lcd.clear();

  // Attach servo
  scanner.attach(servoPin);

  // Set initial motor speeds
  setMotorSpeed(170, 170);
}

// --- Main Loop ---
void loop() {
  long distance = readDistance();
  bool irObstacle = digitalRead(irSensorPin) == LOW; // LOW = Obstacle detected

  controlBuzzer(distance);

  // IR Sensor takes priority
  if (irObstacle) {
    stopMotors();
    lcdStatus("IR Obstacle!", "");
    delay(500);
    moveBackward();
    lcdStatus("Avoiding", "IR Object");
    delay(800);
    stopMotors();
    delay(500);
  }
  // Ultrasonic obstacle avoidance
  else if (distance > 0 && distance < 15) {
    stopMotors();
    lcdStatus("Obstacle!", "");
    delay(500);
    moveBackward();
    lcdStatus("Moving", "Backward");
    delay(800);
    stopMotors();
    delay(500);
    String direction = scanAndChooseDirection();
    if (direction == "LEFT") {
      turnLeft();
      lcdStatus("Turning", "Left");
      delay(300);
    } else {
      turnRight();
      lcdStatus("Turning", "Right");
      delay(300);
    }
    stopMotors();
    delay(500);
  } else {
    moveForward();
    lcdStatus("Moving", "Forward");
  }

  delay(100);
}

// --- Function Definitions ---

void setMotorSpeed(int speedA, int speedB) {
  analogWrite(enA, speedA);
  analogWrite(enB, speedB);
}

long readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void controlBuzzer(long distance) {
  if (distance > 0 && distance < 5) {
    tone(buzzerPin, 1000);
  } else if (distance >= 5 && distance < 10) {
    tone(buzzerPin, 1000); delay(100); noTone(buzzerPin); delay(100);
  } else if (distance >= 10 && distance < 20) {
    tone(buzzerPin, 1000); delay(200); noTone(buzzerPin); delay(300);
  } else {
    noTone(buzzerPin);
  }
}

String scanAndChooseDirection() {
  long leftDist, rightDist;
  scanner.write(0);
  delay(400);
  rightDist = readDistance();
  scanner.write(190);
  delay(400);
  leftDist = readDistance();
  scanner.write(90);
  delay(300);
  return (rightDist > leftDist) ? "RIGHT" : "LEFT";
}

void moveForward() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  digitalWrite(eyeLed, HIGH);
}

void moveBackward() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  digitalWrite(eyeLed, LOW);
}

void turnRight() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  digitalWrite(eyeLed, LOW);
}

void turnLeft() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  digitalWrite(eyeLed, LOW);
}

void stopMotors() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
  digitalWrite(eyeLed, LOW);
}

void lcdStatus(String line1, String line2) {
  if (line1 != lastLine1 || line2 != lastLine2) {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(line2);
    lastLine1 = line1;
    lastLine2 = line2;
  }
}

void blinkEye(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(eyeLed, HIGH); delay(150);
    digitalWrite(eyeLed, LOW); delay(150);
  }
}
