// const int trigPin = 9;
// const int echoPin = 10;

// void setup() {
//   Serial.begin(9600);
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);
// }

// void loop() {
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);

//   long duration = pulseIn(echoPin, HIGH);
//   int distance = duration * 0.034 / 2; // Convert to cm

//   Serial.print("Distance: ");
//   Serial.print(distance);
//   Serial.println(" cm");

//   delay(500);
// }

// const int trigPin = 9;
// const int echoPin = 10;
// const int redLED = 3;
// const int yellowLED = 4;
// const int greenLED = 5;

// void setup() {
//   Serial.begin(9600);
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);
//   pinMode(redLED, OUTPUT);
//   pinMode(yellowLED, OUTPUT);
//   pinMode(greenLED, OUTPUT);
// }

// void loop() {
//   // Send ultrasonic pulse
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);

//   // Measure echo pulse duration
//   long duration = pulseIn(echoPin, HIGH);
//   int distance = duration * 0.034 / 2;

//   Serial.print("Distance: ");
//   Serial.print(distance);
//   Serial.println(" cm");

//   // LED feedback based on distance
//   if (distance < 10) {        // Too close
//     digitalWrite(redLED, HIGH);
//     digitalWrite(yellowLED, LOW);
//     digitalWrite(greenLED, LOW);
//   } 
//   else if (distance < 30) {   // Medium distance
//     digitalWrite(redLED, LOW);
//     digitalWrite(yellowLED, HIGH);
//     digitalWrite(greenLED, LOW);
//   } 
//   else {                      // Safe distance
//     digitalWrite(redLED, LOW);
//     digitalWrite(yellowLED, LOW);
//     digitalWrite(greenLED, HIGH);
//   }

//   delay(500);  // Update rate
// }

const int trigPin = 9;
const int echoPin = 10;
const int redLED = 3;
const int yellowLED = 4;
const int greenLED = 5;
const int buzzer = 6;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure echo pulse duration
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // LED & Buzzer feedback based on distance
  if (distance < 10) {         // Too close
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    tone(buzzer, 1000);  // Continuous sound 🚨
  } 
  else if (distance < 30) {   // Medium distance
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
    tone(buzzer, 1000, 300);  // Short beep ⚠️
  } 
  else {                      // Safe distance
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
    noTone(buzzer);  // No sound ✅
  }

  delay(500);  // Update rate
}
