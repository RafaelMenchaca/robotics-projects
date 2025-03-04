// Simple Blink LED Program
// int yellow = 9;  // The built-in LED on most Arduino boards
// int red = 8;
// int green = 10;

// void setup() {
//     pinMode(yellow, OUTPUT);
//     pinMode(red, OUTPUT);
//     pinMode(green, OUTPUT);
//     Serial.begin(9600);
//     Serial.println("Hello World, Arduino!");
// }

// void loop() {
//     digitalWrite(yellow, HIGH);  // Turn LED on
//     digitalWrite(red, HIGH);
//     digitalWrite(green, HIGH);
//     delay(1000);                 // Wait for 1 second
//     digitalWrite(yellow, LOW);   // Turn LED off
//     digitalWrite(red, LOW);
//     digitalWrite(green, LOW);
//     delay(1000);                 // Wait for 1 second
//     Serial.println("Looping...");
// }

// Advanced blink multiple leds
int led_pins[] = {8, 9, 10}; // pins coneccted to leds
int num_leds = 3; // number of leds

void setup(){
  for (int i = 0; i < num_leds; i++){
      pinMode(led_pins[i], OUTPUT); // set each led as an output
  }
}

void loop(){
  for (int i = 0; i < num_leds; i++){
      digitalWrite(led_pins[i], HIGH);
      delay(500);
      digitalWrite(led_pins[i], LOW);
      delay(500);
  }

  delay(1000);
}


