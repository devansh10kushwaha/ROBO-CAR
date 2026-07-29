#include <SoftwareSerial.h>

SoftwareSerial BT(8, 7);      // RX, TX

// -------- IR Sensors --------
#define IR_LEFT   9
#define IR_RIGHT  12

// -------- Motor Driver --------
#define ENA 11
#define IN1 6
#define IN2 5

#define ENB 10
#define IN3 3
#define IN4 4

// -------- Speed --------
#define SPEED 150

// -------- Sensor States --------
#define ON_LINE 0
#define OFF_LINE 1

bool autoMode = false;

void setup() {

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  BT.begin(9600);

  stopRobot();
}

void loop() {

  // ---------- Bluetooth ----------
  if (BT.available()) {

    char cmd = BT.read();

    switch(cmd) {

      case 'A':
        autoMode = true;
        stopRobot();
        break;

      case 'M':
        autoMode = false;
        stopRobot();
        break;

      case 'F':
        if(!autoMode) forward();
        break;

      case 'B':
        if(!autoMode) backward();
        break;

      case 'L':
        if(!autoMode) left();
        break;

      case 'R':
        if(!autoMode) right();
        break;

      case 'S':
        stopRobot();
        break;
    }
  }

  // ---------- Auto Line Following ----------
  if(autoMode){

    int leftSensor = digitalRead(IR_LEFT);
    int rightSensor = digitalRead(IR_RIGHT);

    if(leftSensor == ON_LINE && rightSensor == ON_LINE){

      forward();

    }
    else if(leftSensor == ON_LINE && rightSensor == OFF_LINE){

      left();

    }
    else if(leftSensor == OFF_LINE && rightSensor == ON_LINE){

      right();

    }
    else{

      stopRobot();

    }
  }

}

// ---------- Forward ----------
void forward(){

  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  analogWrite(ENA,SPEED);
  analogWrite(ENB,SPEED);
}

// ---------- Backward ----------
void backward(){

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  analogWrite(ENA,SPEED);
  analogWrite(ENB,SPEED);
}

// ---------- Left ----------
void left(){

  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);

  analogWrite(ENA,SPEED);
  analogWrite(ENB,0);
}

// ---------- Right ----------
void right(){

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  analogWrite(ENA,0);
  analogWrite(ENB,SPEED);
}

// ---------- Stop ----------
void stopRobot(){

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);

  analogWrite(ENA,0);
  analogWrite(ENB,0);
}