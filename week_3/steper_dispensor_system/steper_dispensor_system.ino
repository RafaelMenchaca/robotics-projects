#include <Stepper.h>
#include <LiquidCrystal.h>


const int stepsPerRevolution = 2048; // 1 full rotation (28BYJ-48)
int dispenseSteps = 0;       // 1/4 rotation (adjust as needed)

Stepper myStepper(stepsPerRevolution, 9, 11, 10, 12);
LiquidCrystal lcd(3, 8, 4, 5, 6, 7);  // LCD pins (RS, E, D4, D5, D6, D7)

int potPin = A0;   // Potentiometer connected to A0
int potValue = 0;  // Variable to store potentiometer value
const int buttonPin = 2;
int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int green_led = 13;    // LED connected to 13

int lastDispenseSteps = -1;  // Add this at the top


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  myStepper.setSpeed(10);  // Adjust speed (RPM)
  Serial.begin(9600);
  lcd.begin(16, 2);  // Initialize the LCD, 16 columns and 2 rows
  pinMode(green_led, OUTPUT);


}

void loop() {
  potValue = analogRead(potPin);
  dispenseSteps = map(potValue, 0, 1023, 0, 2048);

  if (dispenseSteps != lastDispenseSteps) {
    lcd.setCursor(0, 0);
    lcd.print("Ready:           ");
    lcd.setCursor(0, 1);
    lcd.print(dispenseSteps);
    lcd.print(" Steps    ");
    lastDispenseSteps = dispenseSteps;
  }

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    digitalWrite(green_led, LOW);

    if (reading == LOW && buttonState == HIGH) {
      digitalWrite(green_led, HIGH);
      
      lcd.setCursor(0, 0);
      lcd.print("Dispensing...    ");
      lcd.setCursor(0, 1);
      lcd.print(dispenseSteps);
      lcd.print(" Steps    ");
      
      Serial.println("Dispensing...");
      Serial.print(dispenseSteps);
      Serial.println(" steps");

      myStepper.step(dispenseSteps);
      delay(500);

      Serial.println("Done.");

      lcd.setCursor(0, 0);
      lcd.print("Done.            ");
      delay(1000);
    }

    buttonState = reading;
  }

  lastButtonState = reading;
}
