// ===============================
// Line Follower Robot using Arduino
// ===============================

// IR Sensor Pins
#define IR_LEFT  9
#define IR_RIGHT 12

// Left Motor (Motor A)
#define ENA 11
#define IN1 6
#define IN2 5

// Right Motor (Motor B)
#define ENB 10
#define IN3 3
#define IN4 4

// Speed Settings
#define BASE_SPEED 65
#define TURN_SPEED 55
#define STOP_DELAY 200

// Sensor States
#define ON_LINE 0
#define OFF_LINE 1

// ===============================
// Setup Function
// ===============================
void setup() {

  // IR Sensors
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  // Motor A
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Motor B
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);

  stopMotors();

  // Wait for 2 seconds before starting
  delay(2000);
}

// ===============================
// Main Loop
// ===============================
void loop() {

  int leftSensor = digitalRead(IR_LEFT);
  int rightSensor = digitalRead(IR_RIGHT);

  // Both sensors detect the line
  if (leftSensor == ON_LINE && rightSensor == ON_LINE) {

    moveForward(BASE_SPEED);

  }

  // Left sensor detects line
  else if (leftSensor == ON_LINE && rightSensor == OFF_LINE) {

    turnLeft();

  }

  // Right sensor detects line
  else if (leftSensor == OFF_LINE && rightSensor == ON_LINE) {

    turnRight();

  }

  // Line lost
  else {

    stopMotors();

  }
}

// ===============================
// Move Forward
// ===============================
void moveForward(int speed) {

  // Left Motor
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  // Right Motor
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

// ===============================
// Turn Left
// ===============================
void turnLeft() {

  // Left Motor Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, BASE_SPEED);

  // Right Motor Stop
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

// ===============================
// Turn Right
// ===============================
void turnRight() {

  // Left Motor Stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  // Right Motor Forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, BASE_SPEED);
}

// ===============================
// Stop Motors
// ===============================
void stopMotors() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

// ===============================
// Reverse Robot
// ===============================
void reverse() {

  // Left Motor Reverse
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, TURN_SPEED);

  // Right Motor Reverse
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, TURN_SPEED);
}