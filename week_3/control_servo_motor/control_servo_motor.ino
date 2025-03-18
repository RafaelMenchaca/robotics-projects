// #include <Servo.h>

// Servo myServo;  // Create servo object

// void setup() {
//   myServo.attach(9);  // Attach servo to pin 9
// }

// void loop() {
//   myServo.write(0);   // Move to 0 degrees
//   delay(1000);
//   myServo.write(45);  // Move to 90 degrees
//   delay(1000);
//   myServo.write(90); // Move to 180 degrees
//   delay(1000);
//   myServo.write(135); // Move to 180 degrees
//   delay(1000);
//   myServo.write(180); // Move to 180 degrees
//   delay(1000);
//   myServo.write(135);   // Move to 0 degrees
//   delay(1000);
//   myServo.write(90);   // Move to 0 degrees
//   delay(1000);
//   myServo.write(45);   // Move to 0 degrees
//   delay(1000);
// }

// #include <Servo.h>

// Servo myServo;
// const int servoPin = 9;
// const int moveDelay = 1000;  // Time delay between moves (adjustable)

// int angles[] = {0, 45, 90, 135, 180, 135, 90, 45};  // Movement sequence
// int numSteps = sizeof(angles) / sizeof(angles[0]); // Number of steps

// void setup() {
//   myServo.attach(servoPin);
// }

// void loop() {
//   for (int i = 0; i < numSteps; i++) {
//     myServo.write(angles[i]);  // Move servo to the next angle
//     delay(moveDelay);          // Wait before next move
//   }
// }

#include <Servo.h>

Servo myServo;
const int buttonPin = 7;  // Button connected to Pin 7
int buttonState = 0;
int lastButtonState = HIGH;
int servoPosition = 45;
int red_led = 6;      // Red LED connected to Pin 6
int yellow_led = 10;  // Yellow LED connected to Pin 10
int green_led = 11;   // Green LED connected to Pin 11

void setup() {
  myServo.attach(9);  // Attach servo to pin 9
  pinMode(buttonPin, INPUT_PULLUP);  // Enable internal pull-up resistor
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {  
    // Toggle position: 0° -> 90° -> 180° -> 0°
    servoPosition += 45;
    if (servoPosition > 135) {
      servoPosition = 45; 
    }

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
    
    myServo.write(servoPosition);
    delay(200);  // Debounce delay
  }

  lastButtonState = buttonState;  // Store last state
}
