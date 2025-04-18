// --- Libraries ---
// Servo library to control the ultrasonic sensor's servo motor
#include <Servo.h>             

// OLED display libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- OLED Settings ---
#define SCREEN_WIDTH 128        // OLED width in pixels
#define SCREEN_HEIGHT 64        // OLED height in pixels
#define OLED_RESET -1           // No reset pin used
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Motor A Pins (Left motor) ---
const int enA = 6;              // PWM speed control for Motor A
const int in1 = 9;              // Direction control pin 1
const int in2 = 8;              // Direction control pin 2

// --- Motor B Pins (Right motor) ---
const int enB = 5;              // PWM speed control for Motor B
const int in3 = 4;              // Direction control pin 1
const int in4 = 3;              // Direction control pin 2

// --- Ultrasonic Sensor Pins ---
const int trigPin = 12;         // Ultrasonic trigger
const int echoPin = 11;         // Ultrasonic echo return

// --- Servo Motor ---
const int servoPin = 7;         // Controls ultrasonic scanning servo
Servo scanner;                  // Servo instance

// --- Buzzer ---
const int buzzerPin = 2;        // Output pin for buzzer

// --- IR Obstacle Sensor ---
const int irSensorPin = 10;     // Digital output pin from IR sensor (LOW = obstacle)

// --- LED Eye ---
const int eyeLed = 13;          // LED to simulate Robie Jr.'s "eye"

// --- Setup ---
void setup() {
  delay(500); // Allow power rails to stabilize

  // --- Pin Modes ---
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
  pinMode(irSensorPin, INPUT);  // IR sensor input

  // --- OLED Initialization ---
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Freeze if OLED not found
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Robie Jr. Ready!");
  display.display();
  delay(1500);
  display.clearDisplay();

  // --- Attach Servo ---
  scanner.attach(servoPin);

  // --- Set Initial Motor Speed ---
  setMotorSpeed(170, 170);
}

// --- Main Loop ---
void loop() {
  long distance = readDistance();                    // Measure ultrasonic distance
  bool irObstacle = digitalRead(irSensorPin) == LOW; // IR sensor detects line (LOW = object detected)

  controlBuzzer(distance);  // Buzzer sound logic based on distance

  // --- IR Obstacle Detected (priority) ---
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

  // --- Ultrasonic Obstacle Avoidance ---
  else if (distance > 0 && distance < 15) {
    stopMotors();
    lcdStatus("Obstacle!", "");
    delay(500);
    moveBackward();
    lcdStatus("Moving", "Backward");
    delay(800);
    stopMotors();
    delay(500);
    String direction = scanAndChooseDirection();  // Scan left and right
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
  }

  // --- Move Forward ---
  else {
    moveForward();
    lcdStatus("Moving", "Forward");
  }

  delay(100); // Short delay between loops
}

// --- Motor Speed Control ---
void setMotorSpeed(int speedA, int speedB) {
  analogWrite(enA, speedA);
  analogWrite(enB, speedB);
}

// --- Ultrasonic Distance Reading ---
long readDistance() {
  digitalWrite(trigPin, LOW);  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;  // Convert to cm
}

// --- Buzzer Logic Based on Distance ---
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

// --- Smart Scanning with Servo ---
String scanAndChooseDirection() {
  long leftDist, rightDist;

  scanner.write(0);   // Look right
  delay(400);
  rightDist = readDistance();

  scanner.write(190); // Look left
  delay(400);
  leftDist = readDistance();

  scanner.write(90);  // Return to center
  delay(300);

  return (rightDist > leftDist) ? "RIGHT" : "LEFT";
}

// --- Motor Movement Controls ---
void moveForward() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  digitalWrite(eyeLed, HIGH);  // Eye ON
}

void moveBackward() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  digitalWrite(eyeLed, LOW);   // Eye OFF
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

// --- OLED Display Status Function ---
void lcdStatus(String line1, String line2) {
  static String lastLine1 = "";
  static String lastLine2 = "";

  if (line1 != lastLine1 || line2 != lastLine2) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(line1);
    display.setCursor(0, 16);
    display.println(line2);
    display.display();
    lastLine1 = line1;
    lastLine2 = line2;
  }
}

// --- Optional: LED Blink Effect for Personality ---
void blinkEye(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(eyeLed, HIGH); delay(150);
    digitalWrite(eyeLed, LOW);  delay(150);
  }
}
