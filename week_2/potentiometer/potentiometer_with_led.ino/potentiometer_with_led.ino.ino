int ledPin = 9;
int potPin = A0;
int potValue;
int fadeSpeed;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(potPin);  
  fadeSpeed = map(potValue, 0, 1023, 5, 50);  // Adjust speed (smaller = faster)
  
  Serial.print("Fade Speed: ");
  Serial.println(fadeSpeed);

  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness);
    delay(fadeSpeed);
  }

  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    delay(fadeSpeed);
  }
}
