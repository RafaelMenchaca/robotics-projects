// void setup() {
//   Serial.begin(9600);  // Start serial communication at 9600 baud
// }

// void loop() {
//   Serial.println("Hello from Arduino!");
//   delay(1000);  // Wait 1 second
// }

int sensorPin = A0;  // Potentiometer or LDR connected to A0
int sensorValue = 0;

void setup() {
  Serial.begin(9600);  
}

void loop() {
  sensorValue = analogRead(sensorPin);  // Read the sensor
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  delay(500);  // Adjust delay for real-time readings
}
