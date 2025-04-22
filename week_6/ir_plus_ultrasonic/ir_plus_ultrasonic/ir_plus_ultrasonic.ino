// --- Libraries ---
#include <Servo.h>             // For controlling the servo scanner
#include <Wire.h>              // I2C for OLED
#include <Adafruit_GFX.h>      // Graphics library for OLED
#include <Adafruit_SSD1306.h>  // OLED display driver

// --- OLED Settings ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Motor A Pins ---
const int enA = 6;
const int in1 = 9;
const int in2 = 8;

// --- Motor B Pins ---
const int enB = 5;
const int in3 = 4;
const int in4 = 3;

// --- Servo ---
const int servoPin = 7;
Servo scanner;

// --- Ultrasonic Sensor ---
const int trigPin = 12;
const int echoPin = 11;

// --- IR Sensor ---
const int irSensorPin = 10;  // TCRT5000 sensor

// --- Buzzer ---
const int buzzerPin = 2;

// --- LED Eye ---
const int eyeLed = 13;

// --- Setup ---
void setup() {
  delay(500); // Power stabilization
  Serial.begin(9600); // For debugging

  // Pin Modes
  pinMode(eyeLed, OUTPUT);
  pinMode(enA, OUTPUT); pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT); pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(irSensorPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Servo setup
  scanner.attach(servoPin);

  // OLED Setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);  // Stop if OLED fails
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Robie Jr. Ready!");
  display.display();
  delay(1500);
  display.clearDisplay();

  setMotorSpeed(150, 150); // Moderate speed for better control
}

// --- Main Loop ---
void loop() {
  bool onLine = digitalRead(irSensorPin) == HIGH; // HIGH = black line
  long distance = readDistance();

  Serial.print("IR Sensor: ");
  Serial.print(onLine ? "ON LINE" : "OFF LINE");
  Serial.print(" | Distance: ");
  Serial.println(distance);

  static bool lastTurnLeft = true;

  if (onLine) {
    // ✅ IR sensor sees black line: follow it
    moveForward();
    lcdStatus("Line Detected", "Following...");
    delay(150);
  } 
  else if (distance > 0 && distance < 15) {
    // 📏 Obstacle detected with ultrasonic
    stopMotors();
    lcdStatus("Obstacle Ahead!", "Avoiding...");
    delay(500);
    moveBackward();
    lcdStatus("Backing Up", "");
    delay(700);
    stopMotors();
    delay(300);

    String safeTurn = scanAndChooseDirection();
    if (safeTurn == "LEFT") {
      turnLeft();
      lcdStatus("Turning", "Left");
    } else {
      turnRight();
      lcdStatus("Turning", "Right");
    }
    delay(300);
    stopMotors();
    delay(300);
  } 
  else {
    // ❌ No line & no obstacle: search using alternating turns
    if (lastTurnLeft) {
      turnRight();
      lcdStatus("Line Lost", "Turning Right");
    } else {
      turnLeft();
      lcdStatus("Line Lost", "Turning Left");
    }
    lastTurnLeft = !lastTurnLeft;
    delay(300);
    stopMotors();
    delay(300); // Give IR sensor time to detect again
  }

  delay(50); // Short cooldown between decisions
}

// --- Function Definitions ---

void setMotorSpeed(int speedA, int speedB) {
  analogWrite(enA, speedA);
  analogWrite(enB, speedB);
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

long readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // Convert to cm
}

String scanAndChooseDirection() {
  long leftDist, rightDist;

  // Scan right
  scanner.write(0);
  delay(400);
  rightDist = readDistance();

  // Scan left
  scanner.write(190);
  delay(400);
  leftDist = readDistance();

  // Center again
  scanner.write(90);
  delay(300);

  return (rightDist > leftDist) ? "RIGHT" : "LEFT";
}

// --- OLED Display Function ---
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
