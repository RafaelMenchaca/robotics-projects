int sensorPin = A0;   // Sensor connected to A0
int red_led = 9;      // Red LED connected to Pin 9
int yellow_led = 10;  // Yellow LED connected to Pin 10
int green_led = 11;   // Green LED connected to Pin 11
int buzzer = 6;       // buzzer to pin 6

const int LOW_THRESHOLD = 300;
const int HIGH_THRESHOLD = 700;

void setup() {
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // Read sensor value
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // LED Control Based on Sensor Value
  if (sensorValue < LOW_THRESHOLD) {
    digitalWrite(red_led, HIGH);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, LOW);
    tone(buzzer, 1000);
  } else if (sensorValue >= LOW_THRESHOLD && sensorValue <= HIGH_THRESHOLD) {
    digitalWrite(red_led, LOW);
    digitalWrite(yellow_led, HIGH);
    digitalWrite(green_led, LOW);
    tone(buzzer, 1000, 700);
  } else {
    digitalWrite(red_led, LOW);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, HIGH);
    tone(buzzer, 1000, 200);

  }

  delay(1000);  // Small delay to stabilize readings
}
