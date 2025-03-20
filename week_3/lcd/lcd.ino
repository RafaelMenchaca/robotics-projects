#include <Servo.h>
#include <LiquidCrystal.h>

Servo myServo;
LiquidCrystal lcd(3, 8, 4, 5, 6, 7);  // LCD pins (RS, E, D4, D5, D6, D7)

const int buttonPin = 2;  // Button connected to Pin 2
int buttonState = 0;
int lastButtonState = HIGH;
int servoPosition = 45;
int red_led = 12;     // Red LED connected to Pin 12
int yellow_led = 10;  // Yellow LED connected to Pin 10
int green_led = 11;   // Green LED connected to Pin 11

void setup() {
  myServo.attach(9);  // Attach servo to pin 9
  pinMode(buttonPin, INPUT_PULLUP);  // Enable internal pull-up resistor
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);

  lcd.begin(16, 2);  // Initialize the LCD, 16 columns and 2 rows
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {  
    // Toggle position: 0° -> 90° -> 180° -> 0°
    servoPosition += 45;
    if (servoPosition > 135) {
      servoPosition = 45; 
    }

    // Update LEDs based on servo position
    if (servoPosition == 45){
      digitalWrite(red_led, LOW);
      digitalWrite(yellow_led, LOW);
      digitalWrite(green_led, HIGH);
    } else if (servoPosition == 90){
      digitalWrite(red_led, LOW);
      digitalWrite(yellow_led, HIGH);
      digitalWrite(green_led, LOW);
    } else if (servoPosition == 135){
      digitalWrite(red_led, HIGH);
      digitalWrite(yellow_led, LOW);
      digitalWrite(green_led, LOW);
    }
    
    // Clear LCD screen and show the new servo position
    lcd.clear();  // Clear the previous display content
    lcd.setCursor(0, 0);  // Set cursor to the first line
    lcd.print("Servo Pos: ");  // Display label
    lcd.print(servoPosition);  // Display servo position value
    
    myServo.write(servoPosition);  // Move the servo to the new position
    delay(200);  // Debounce delay
  }

  lastButtonState = buttonState;  // Store last state
}
