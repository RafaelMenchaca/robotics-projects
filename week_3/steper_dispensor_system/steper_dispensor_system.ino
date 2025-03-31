// #include <Stepper.h>
// #include <LiquidCrystal.h>


// const int stepsPerRevolution = 2048; // 1 full rotation (28BYJ-48)
// int dispenseSteps = 0;       // 1/4 rotation (adjust as needed)

// Stepper myStepper(stepsPerRevolution, 9, 11, 10, 12);
// LiquidCrystal lcd(3, 8, 4, 5, 6, 7);  // LCD pins (RS, E, D4, D5, D6, D7)

// int potPin = A0;   // Potentiometer connected to A0
// int potValue = 0;  // Variable to store potentiometer value
// const int buttonPin = 2;
// int buttonState = HIGH;
// int lastButtonState = HIGH;
// unsigned long lastDebounceTime = 0;
// unsigned long debounceDelay = 50;
// int green_led = 13;    // LED connected to 13

// int lastDispenseSteps = -1;  // Add this at the top


// void setup() {
//   pinMode(buttonPin, INPUT_PULLUP);
//   myStepper.setSpeed(10);  // Adjust speed (RPM)
//   Serial.begin(9600);
//   lcd.begin(16, 2);  // Initialize the LCD, 16 columns and 2 rows
//   pinMode(green_led, OUTPUT);


// }

// void loop() {
//   potValue = analogRead(potPin);
//   dispenseSteps = map(potValue, 0, 1023, 0, 2048);

//   if (dispenseSteps != lastDispenseSteps) {
//     lcd.setCursor(0, 0);
//     lcd.print("Ready:           ");
//     lcd.setCursor(0, 1);
//     lcd.print(dispenseSteps);
//     lcd.print(" Steps    ");
//     lastDispenseSteps = dispenseSteps;
//   }

//   int reading = digitalRead(buttonPin);

//   if (reading != lastButtonState) {
//     lastDebounceTime = millis();
//   }

//   if ((millis() - lastDebounceTime) > debounceDelay) {
//     digitalWrite(green_led, LOW);

//     if (reading == LOW && buttonState == HIGH) {
//       digitalWrite(green_led, HIGH);
      
//       lcd.setCursor(0, 0);
//       lcd.print("Dispensing...    ");
//       lcd.setCursor(0, 1);
//       lcd.print(dispenseSteps);
//       lcd.print(" Steps    ");
      
//       Serial.println("Dispensing...");
//       Serial.print(dispenseSteps);
//       Serial.println(" steps");

//       myStepper.step(dispenseSteps);
//       delay(500);

//       Serial.println("Done.");

//       lcd.setCursor(0, 0);
//       lcd.print("Done.            ");
//       delay(1000);
//     }

//     buttonState = reading;
//   }

//   lastButtonState = reading;
// }

#include <Stepper.h>
#include <Servo.h>
#include <LiquidCrystal.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 9, 11, 10, 12);  // Pin order matters!

// Servo myServo;
// const int servoPin = 6;  // Make sure it's a PWM-capable pin like D3, D5, D6, D9, D10, or D11

LiquidCrystal lcd(3, 8, 4, 5, 6, 7);
const int servoPin = A1;
Servo myServo;




// #include <LiquidCrystal.h>

// LiquidCrystal lcd(3, 8, 4, 5, 6, 7);

// Button pins
const int scrollBtn = 2;
// const int selectBtn = 12;
// const int selectBtn = A1; // Works just like D2, D3, etc.
// const int selectBtn = A1;
const int selectBtn = A2;




// Menu setup
const int menuLength = 3;
int menuIndex = 0;
String menuItems[menuLength] = {
  "1. Dispense Steps",
  "2. Servo Action",
  "3. Show Pot Value"
};

// Button state tracking
int lastScrollState = HIGH;
int lastSelectState = HIGH;

void setup() {
  myServo.attach(servoPin);

  myStepper.setSpeed(10);       // Must be set or motor won’t move
  // myServo.attach(servoPin);     // Attach the servo pin
  // myServo.attach(servoPin);

  pinMode(scrollBtn, INPUT_PULLUP);
  // pinMode(selectBtn, INPUT_PULLUP);
  pinMode(selectBtn, INPUT_PULLUP);
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("> ");
  lcd.print(menuItems[menuIndex]);
}

void loop() {
  int scrollState = digitalRead(scrollBtn);
  int selectState = digitalRead(selectBtn);
  
  int buttonState = digitalRead(selectBtn);
  Serial.println(buttonState);
  delay(200);  // Slow it down for readability
  

  // Scroll menu
  if (scrollState == LOW && lastScrollState == HIGH) {
    menuIndex++;
    if (menuIndex >= menuLength) menuIndex = 0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("> ");
    lcd.print(menuItems[menuIndex]);
  }

  // Select item
  if (selectState == LOW && lastSelectState == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Selected:");
    lcd.setCursor(0, 1);
    lcd.print(menuItems[menuIndex]);
    delay(1000);

    // Perform action based on selection
    if (menuIndex == 0) {
      // Dispense Steps (Stepper Motor)
      int potValue = analogRead(A0);
      int steps = map(potValue, 0, 1023, 0, 2048);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dispensing...");
      lcd.setCursor(0, 1);
      lcd.print(steps);
      lcd.print(" steps");

      myStepper.step(steps);
      delay(1000);
    }

    else if (menuIndex == 1) {
      Serial.println("Moving servo...");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Moving Servo...");
      myServo.write(0);
      delay(500);
      myServo.write(90);
      delay(500);
      myServo.write(0);
      delay(500);
    }

    else if (menuIndex == 2) {
      // Show Pot Value
      int potValue = analogRead(A0);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Potentiometer:");
      lcd.setCursor(0, 1);
      lcd.print(potValue);
      delay(1500);
    }

    // Return to menu
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("> ");
    lcd.print(menuItems[menuIndex]);

  }

  lastScrollState = scrollState;
  lastSelectState = selectState;
}
