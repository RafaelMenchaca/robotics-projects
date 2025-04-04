// Motor A
const int enA = 10;
const int in1 = 9;
const int in2 = 8;

// Motor B
const int enB = 5;
const int in3 = 4;
const int in4 = 3;

// Ultrasonic
const int trigPin = 12;
const int echoPin = 11;

void setup() {
  // Motor pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  analogWrite(enA, 200);
  analogWrite(enB, 200);

  Serial.begin(9600);
}

void loop() {
  long duration, distance;

  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance < 15) {
    Serial.println("Obstacle detected!");

    // Stop and pause
    stopMotors();
    delay(500);  // <- small pause before reacting

    // Reverse and pause
    moveBackward();
    delay(800);
    stopMotors();
    delay(500);  // <- pause before turning

    // Turn and pause
    turnRight();
    delay(600);
    stopMotors();
    delay(500);  // <- pause before moving forward again
  } else {
    moveForward();
  }

  delay(100); // Short loop delay
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
