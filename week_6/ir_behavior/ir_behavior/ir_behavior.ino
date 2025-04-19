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

// --- Buzzer ---
const int buzzerPin = 2;

// --- IR Sensor ---
const int irSensorPin = 10;  // TCRT5000 sensor connected to pin 10

// --- LED Eye ---
const int eyeLed = 13;

// --- Setup ---
void setup() {

  delay(500); // Give power rails time to stabilize

  Serial.begin(9600);  // ✅ Start serial communication for debugging

  delay(500);  // Let power stabilize

  // Pin modes
  pinMode(eyeLed, OUTPUT);
  pinMode(enA, OUTPUT); pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT); pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(irSensorPin, INPUT);

  // Attach servo
  scanner.attach(servoPin);

  // Setup OLED
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

  setMotorSpeed(170, 170);
}

// --- Main Loop ---
void loop() {

  int irValue = digitalRead(irSensorPin);
  Serial.print("IR Sensor Value: ");
  Serial.println(irValue);
  delay(100);


  bool onLine = digitalRead(irSensorPin) == HIGH;  // HIGH = black line

  if (onLine) {
    moveForward();  // Keep following the line
    lcdStatus("Line Detected", "Moving on it...");
  } else {
    stopMotors();   // Stop if it loses the line
    lcdStatus("NO LINE Detected", "Stop moving");
  }

  delay(200);  // Short delay to stabilize output


  delay(50);  // Short pause for stability
}

// --- Motor Functions ---
void setMotorSpeed(int speedA, int speedB) {
  analogWrite(enA, speedA);
  analogWrite(enB, speedB);
}

void moveForward() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  digitalWrite(eyeLed, HIGH);
}

void stopMotors() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
  digitalWrite(eyeLed, LOW);
}

// --- OLED Display ---
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
