// --- Libraries ---
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

// --- LED Eye ---
const int eyeLed = 13;

// --- IR Sensor Pins ---
const int irLeftPin   = A0;
const int irCenterPin = 10;
const int irRightPin  = A1;

// --- Setup ---
void setup() {
  delay(500);
  Serial.begin(9600);

  // Motor pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // LED Eye
  pinMode(eyeLed, OUTPUT);

  // IR sensors
  pinMode(irLeftPin, INPUT);
  pinMode(irCenterPin, INPUT);
  pinMode(irRightPin, INPUT);

  // OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Multi IR Test");
  display.display();
  delay(1500);
  display.clearDisplay();

  setMotorSpeed(150, 150);  // Adjust motor speed if needed
}

// --- Main Loop ---
void loop() {
  // 0 = Black detected | 1 = White surface
  bool leftOnBlack   = digitalRead(irLeftPin)   == LOW;
  bool centerOnBlack = digitalRead(irCenterPin) == LOW;
  bool rightOnBlack  = digitalRead(irRightPin)  == LOW;

  // Raw serial print (1 for white, 0 for black)
  Serial.print("Left: ");
  Serial.print(digitalRead(irLeftPin));
  Serial.print(" | Center: ");
  Serial.print(digitalRead(irCenterPin));
  Serial.print(" | Right: ");
  Serial.println(digitalRead(irRightPin));

  // --- Basic Line-Following IR Logic ---
  if (centerOnBlack && !leftOnBlack && !rightOnBlack) {
    moveForward();
    oledStatus("Following", "Line: Center");
  }
  else if (leftOnBlack) {
    turnLeft();
    oledStatus("Adjusting", "Line: Left");
  }
  else if (rightOnBlack) {
    turnRight();
    oledStatus("Adjusting", "Line: Right");
  }
  else {
    stopMotors();
    oledStatus("Line Lost", "Stopping...");
  }

  delay(100);
}

// --- Motor Control ---
void setMotorSpeed(int speedA, int speedB) {
  analogWrite(enA, speedA);
  analogWrite(enB, speedB);
}

void moveForward() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  digitalWrite(eyeLed, HIGH);
}

void turnLeft() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
  digitalWrite(eyeLed, LOW);
}

void turnRight() {
  digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  digitalWrite(eyeLed, LOW);
}

void stopMotors() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
  digitalWrite(eyeLed, LOW);
}

// --- OLED Helper ---
void oledStatus(String line1, String line2) {
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
