const int sensorPin = 8; // Digital pin connected to OUT

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(sensorPin);
  Serial.println(sensorValue); // 0 = black (absorbs IR), 1 = white (reflects IR)
  delay(200);
}
