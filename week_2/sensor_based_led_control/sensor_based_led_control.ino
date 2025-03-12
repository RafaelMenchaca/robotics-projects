int sensorPin = A0;   // Sensor connected to A0
int ledPin = 9;       // LED connected to Pin 9
int sensorValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);  // Read sensor
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue > 500) {  // Threshold (adjust if needed)
    digitalWrite(ledPin, HIGH);  // Turn LED ON
  } else {
    digitalWrite(ledPin, LOW);   // Turn LED OFF
  }

  delay(500);  // Small delay to stabilize readings
}
