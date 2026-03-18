#include <Ultrasonic.h>

// ---------- Ultrasonic Pins ----------
const int leftSensorTrig   = 12;
const int leftSensorEcho   = 13;
const int frontSensorTrig  = 10;
const int frontSensorEcho  = 11;
const int rightSensorTrig  = 2;
const int rightSensorEcho  = 3;

// ---------- Motor Pins ----------
const int motorLeftForward   = 7;
const int motorLeftBackward  = 8;
const int motorRightForward  = 4;
const int motorRightBackward = 5;
const int en_right_motor     = 9;
const int en_left_motor      = 6;

// ---------- Speed ----------
const int speedForward = 180;
const int speedTurn    = 150;
const int MIN_DISTANCE = 20;  // Minimum safe distance in cm
const int TURN_DELAY   = 300; // ms

// ---------- Ultrasonic Objects ----------
Ultrasonic leftSensor(leftSensorTrig, leftSensorEcho);
Ultrasonic frontSensor(frontSensorTrig, frontSensorEcho);
Ultrasonic rightSensor(rightSensorTrig, rightSensorEcho);

void setup() {
  Serial.begin(9600);
  pinMode(motorLeftForward,   OUTPUT);
  pinMode(motorLeftBackward,  OUTPUT);
  pinMode(motorRightForward,  OUTPUT);
  pinMode(motorRightBackward, OUTPUT);
  pinMode(en_left_motor,      OUTPUT);
  pinMode(en_right_motor,     OUTPUT);
  stopMotors();
  Serial.println("=== MAZE ROBOT STARTING ===");
  delay(2000);
}

void loop() {
  int distLeft  = leftSensor.read();
  int distFront = frontSensor.read();
  int distRight = rightSensor.read();

  Serial.print("L: "); Serial.print(distLeft);
  Serial.print("  F: "); Serial.print(distFront);
  Serial.print("  R: "); Serial.println(distRight);

  // ---------- Left-hand rule ----------
  if (distLeft > MIN_DISTANCE) {
    Serial.println("TURN LEFT");
    turnLeft();
  }
  else if (distFront > MIN_DISTANCE) {
    Serial.println("MOVE FORWARD");
    moveForward();
  }
  else if (distRight > MIN_DISTANCE) {
    Serial.println("TURN RIGHT");
    turnRight();
  }
  else {
    Serial.println("TURN AROUND");
    turnAround();
  }

  delay(50);
}

// ---------- Motor Functions ----------
void moveForward() {
  digitalWrite(motorLeftForward,   HIGH);
  digitalWrite(motorLeftBackward,  LOW);
  digitalWrite(motorRightForward,  HIGH);
  digitalWrite(motorRightBackward, LOW);
  analogWrite(en_left_motor,  speedForward);
  analogWrite(en_right_motor, speedForward);
}

void turnLeft() {
  digitalWrite(motorLeftForward,   LOW);
  digitalWrite(motorLeftBackward,  HIGH);
  digitalWrite(motorRightForward,  HIGH);
  digitalWrite(motorRightBackward, LOW);
  analogWrite(en_left_motor,  speedTurn);
  analogWrite(en_right_motor, speedTurn);
  delay(TURN_DELAY);
  stopMotors();
}

void turnRight() {
  digitalWrite(motorLeftForward,   HIGH);
  digitalWrite(motorLeftBackward,  LOW);
  digitalWrite(motorRightForward,  LOW);
  digitalWrite(motorRightBackward, HIGH);
  analogWrite(en_left_motor,  speedTurn);
  analogWrite(en_right_motor, speedTurn);
  delay(TURN_DELAY);
  stopMotors();
}

void turnAround() {
  digitalWrite(motorLeftForward,   LOW);
  digitalWrite(motorLeftBackward,  HIGH);
  digitalWrite(motorRightForward,  HIGH);
  digitalWrite(motorRightBackward, LOW);
  analogWrite(en_left_motor,  speedTurn);
  analogWrite(en_right_motor, speedTurn);
  delay(TURN_DELAY * 2);
  stopMotors();
}

void stopMotors() {
  digitalWrite(motorLeftForward,   LOW);
  digitalWrite(motorLeftBackward,  LOW);
  digitalWrite(motorRightForward,  LOW);
  digitalWrite(motorRightBackward, LOW);
  analogWrite(en_left_motor,  0);
  analogWrite(en_right_motor, 0);
}
