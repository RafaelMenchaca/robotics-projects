int ledPin = 9; // conecct the led to pin 9

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  // Start Serial Communication at 9600 baud rate

}

void loop() {
  // Fade in brightness (from 0 to 255)
  for (int brightness = 0; brightness <= 255; brightness ++){
    analogWrite(ledPin, brightness);
    delay(5);
  }

  // Fade out brightness (from 255 to 0)
  for (int brightness = 255; brightness >= 0; brightness --){
    analogWrite(ledPin, brightness);
    delay(5);
  }

  Serial.println("Arduino is running...");  // Print message to Serial Monitor
  delay(1000);  // Wait 1 second
}
