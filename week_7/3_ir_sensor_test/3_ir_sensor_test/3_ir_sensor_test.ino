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
  Serial.begin(9600);  // For sensor feedback and debugging

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
  display.println("Robie Jr. Multi IR Ready");
  display.display();
  delay(1500);
  display.clearDisplay();

  // Motor speed preset
  setMotorSpeed(135, 135);  // Lower speed for smooth tracking
}

// --- Main Loop ---
void loop() {
  // Read all sensors: 1 = black, 0 = white
  // Correct sensor logic by swapping labels in software
  bool leftOnLine   = digitalRead(irRightPin);  // Right sensor is physically on the left
  bool centerOnLine = digitalRead(irCenterPin);
  bool rightOnLine  = digitalRead(irLeftPin);   // Left sensor is physically on the right


  // Debug output to Serial Monitor
  Serial.print("Left: ");
  Serial.print(leftOnLine);
  Serial.print(" | Center: ");
  Serial.print(centerOnLine);
  Serial.print(" | Right: ");
  Serial.println(rightOnLine);

  // === Line Following Logic ===
  if (centerOnLine && !leftOnLine && !rightOnLine) {
    moveForward();
    oledStatus("Following", "Line: Center");
  }
  else if (leftOnLine && !centerOnLine) {
    turnLeft();
    oledStatus("Adjusting", "Line: Left");
  }
  else if (rightOnLine && !centerOnLine) {
    turnRight();
    oledStatus("Adjusting", "Line: Right");
  }
  else if (leftOnLine && centerOnLine && rightOnLine) {
    // all balck
    moveForward();
    oledStatus("Intersection", "Moving Forward");
  }
   else if (!leftOnLine && !centerOnLine && !rightOnLine) {
    // All white = line lost
    static bool turnLeftNext = true;

    stopMotors();
    oledStatus("Line Lost", "Searching...");

    delay(400);  // Short pause before searching

    if (turnLeftNext) {
      turnLeft();
      oledStatus("Searching", "Turning Left");
    } else {
      turnRight();
      oledStatus("Searching", "Turning Right");
    }

    delay(400);  // Turning time

    turnLeftNext = !turnLeftNext;  // Alternate next turn direction
  }

  delay(80);  // Loop delay for smoother response
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
  delay(80);  // Small forward motion for control
}

void turnLeft() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
  digitalWrite(eyeLed, LOW);
  delay(100);  // Deliberate correction
}

void turnRight() {
  digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  digitalWrite(eyeLed, LOW);
  delay(100);  // Deliberate correction
}

void stopMotors() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
  digitalWrite(eyeLed, LOW);
}

// --- OLED Display Helper ---
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
