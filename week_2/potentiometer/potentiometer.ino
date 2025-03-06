int potPin = A0;   // Potentiometer connected to A0
int ledPin = 9;    // LED connected to PWM pin 9
int potValue = 0;  // Variable to store potentiometer value
int brightness = 0; // Mapped brightness value

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // Start Serial Monitor
}

void loop() {
  potValue = analogRead(potPin);  // Read potentiometer (0-1023)
  brightness = map(potValue, 0, 1023, 0, 255);  // Scale to PWM range (0-255)
  
  analogWrite(ledPin, brightness);  // Set LED brightness
  Serial.print("Potentiometer: ");
  Serial.print(potValue);
  Serial.print(" | LED Brightness: ");
  Serial.println(brightness);
  
  delay(10);  // Small delay for stability
}
