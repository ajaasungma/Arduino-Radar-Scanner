
#include <Servo.h>
Servo myServo;
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 7;
const int ledPin = 4;
long duration;
int distance;
float filteredDistance = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  myServo.attach(8);
}
void loop() {
  // Forward sweep
  for (int i = 0; i <= 180; i++) {
    myServo.write(i);
    delay(40);
    distance = calculateDistance();
    filteredDistance = 0.7 * filteredDistance + 0.3 * distance;
    if(distance == 0) {
      return;
    }
    if (filteredDistance < 15) {
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(ledPin, HIGH);
    }
    else {
      digitalWrite(buzzerPin, LOW);
      digitalWrite(ledPin, LOW);
    }

    Serial.print(i);
    Serial.print(",");
    Serial.print((int)filteredDistance);
    Serial.print(".");
    // Serial.print("Angle: ");
    // Serial.print(i);
    // Serial.print(" | Distance: ");
    // Serial.println(filteredDistance);
  }
  // Return sweep:
  for (int i = 180; i >= 0; i--) {
    myServo.write(i);
    delay(40);
    distance = calculateDistance();
    if(distance == 0) {
      return;
    }
    filteredDistance = 0.7 * filteredDistance + 0.3 * distance;

    if (filteredDistance < 15) {
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(ledPin, HIGH);
    }
    else {
      digitalWrite(buzzerPin, LOW);
      digitalWrite(ledPin, LOW);
    }

    Serial.print(i);
    Serial.print(",");
    Serial.print((int)filteredDistance);
    Serial.print(".");    
    // Serial.print("Angle: ");
    // Serial.print(i);
    // Serial.print(" | Distance: ");
    // Serial.println(filteredDistance);
  }
}
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}