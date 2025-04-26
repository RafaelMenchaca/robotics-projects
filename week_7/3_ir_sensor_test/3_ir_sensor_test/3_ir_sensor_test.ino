// --- Libraries ---
#include <Wire.h>                 // Communication library for I2C devices
#include <Adafruit_GFX.h>          // Graphics library for OLED displays
#include <Adafruit_SSD1306.h>      // Driver for SSD1306 OLED

// --- OLED Display Settings ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1              // No hardware reset pin used
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Motor A Pins (Left Motor) ---
const int enA = 6;                 // PWM speed control for Motor A
const int in1 = 9;                 // Motor A direction control
const int in2 = 8;                 // Motor A direction control

// --- Motor B Pins (Right Motor) ---
const int enB = 5;                 // PWM speed control for Motor B
const int in3 = 4;                 // Motor B direction control
const int in4 = 3;                 // Motor B direction control

// --- LED Eye Indicator ---
const int eyeLed = 13;             // LED pin to show motion status

// --- IR Sensor Pins ---
const int irLeftPin   = A0;         // Left sensor physically right-wired
const int irCenterPin = 10;         // Center sensor
const int irRightPin  = A1;         // Right sensor physically left-wired

// --- Setup ---
void setup() {
  delay(500);                      // Small delay for voltage stabilization
  Serial.begin(9600);               // Initialize serial monitor for debugging

  // Initialize motor control pins
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize LED Eye
  pinMode(eyeLed, OUTPUT);

  // Initialize IR sensors
  pinMode(irLeftPin, INPUT);
  pinMode(irCenterPin, INPUT);
  pinMode(irRightPin, INPUT);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);  // Infinite loop if OLED not found
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Robie Jr. Multi IR Ready");
  display.display();
  delay(1500);
  display.clearDisplay();

  setMotorSpeed(135, 135);          // Set initial motor speed for smooth control
}

// --- Main Loop ---
void loop() {
  // --- Read IR Sensor Values ---
  // 1 = black detected, 0 = white detected
  bool leftOnLine   = digitalRead(irRightPin);  // Swapped physically
  bool centerOnLine = digitalRead(irCenterPin);
  bool rightOnLine  = digitalRead(irLeftPin);   // Swapped physically

  // --- Debug Print ---
  Serial.print("Left: ");
  Serial.print(leftOnLine);
  Serial.print(" | Center: ");
  Serial.print(centerOnLine);
  Serial.print(" | Right: ");
  Serial.println(rightOnLine);

  // --- Line Following Decision Tree ---
  if (centerOnLine && !leftOnLine && !rightOnLine) {
    moveForward();   // Center detected, go straight
    oledStatus("Following", "Line: Center");
  }
  else if (!centerOnLine && leftOnLine && !rightOnLine) {
    turnLeft();      // Only left sees black, adjust left
    oledStatus("Adjusting", "Curve: Left");
  }
  else if (!centerOnLine && !leftOnLine && rightOnLine) {
    turnRight();     // Only right sees black, adjust right
    oledStatus("Adjusting", "Curve: Right");
  }
  else if (leftOnLine && centerOnLine && rightOnLine) {
    moveForward();   // All sensors detect black, intersection or big straight
    oledStatus("Intersection", "Moving Forward");
  }
  else if (!leftOnLine && !centerOnLine && !rightOnLine) {
    // --- Line Lost: No black detected ---
    static bool turnLeftNext = true;  // Alternates turns left/right

    stopMotors();
    oledStatus("Line Lost", "Searching...");

    delay(300);  // Pause before search attempt

    if (turnLeftNext) {
      turnLeft();
      oledStatus("Searching", "Turning Left");
    } else {
      turnRight();
      oledStatus("Searching", "Turning Right");
    }

    delay(400);    // Rotate time to scan surroundings
    turnLeftNext = !turnLeftNext;  // Alternate next search turn
  }

  delay(70);  // Short pause to improve stability
}

// --- Motor Functions ---
void setMotorSpeed(int speedA, int speedB) {
  analogWrite(enA, speedA); // Speed Motor A
  analogWrite(enB, speedB); // Speed Motor B
}

void moveForward() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);  // Motor A forward
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);  // Motor B forward
  digitalWrite(eyeLed, HIGH);                       // Turn on LED
  delay(80);                                        // Small movement pulse
}

void turnLeft() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);  // Motor A forward
  digitalWrite(in3, LOW);  digitalWrite(in4, HIGH); // Motor B backward
  digitalWrite(eyeLed, LOW);                        // LED off while turning
  delay(100);                                       // Time to turn
}

void turnRight() {
  digitalWrite(in1, LOW);  digitalWrite(in2, HIGH); // Motor A backward
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);  // Motor B forward
  digitalWrite(eyeLed, LOW);                        // LED off while turning
  delay(100);                                       // Time to turn
}

void stopMotors() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);  // Motor A stop
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);  // Motor B stop
  digitalWrite(eyeLed, LOW);                       // LED off when stopped
}

// --- OLED Display Helper ---
void oledStatus(String line1, String line2) {
  static String lastLine1 = "";  // Remember last messages
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




// // Test to adjust IR sensor 
// void setup() {
//   Serial.begin(9600);
//   pinMode(10, INPUT);
//   pinMode(A0, INPUT);
//   pinMode(A1, INPUT);

// }
//   // detects Wihte == 1
//   // detects Black == 0
// void loop() {
//   int center = digitalRead(10);
//   int right = digitalRead(A0);
//   int left = digitalRead(A1);
//   Serial.print("Left: ");
//   Serial.print(digitalRead(left));
//   Serial.print(" | Center: ");
//   Serial.print(digitalRead(center));
//   Serial.print(" | Right: ");
//   Serial.println(digitalRead(right));
  
//   delay(200);
// }
