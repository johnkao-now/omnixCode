#include <Servo.h>
#define trig A1
#define echo A0
int angle = 0;
int turn = 0;
Servo myservo;
void setup() {
  for (int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);
}
void AMove(int mode)// 0 is no action, 1 is foward, 2, is backward (movement)
{
  if (mode == 0) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
  }
  else if (mode == 1) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
  }
  else if (mode == 2) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
  }
}
void BMove(int mode)// 0 is no action, 1 is foward, 2, is backward (movement)
{
  if (mode == 0) {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  else if (mode == 1) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  }
  else if (mode == 2) {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }
}
void CMove(int mode)// 0 is no action, 1 is foward, 2, is backward (movement)
{
  if (mode == 0) {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  else if (mode == 1) {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  else if (mode == 2) {
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }
}
void DMove(int mode)// 0 is no action, 1 is foward, 2, is backward (movement)
{
  if (mode == 0) {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
  else if (mode == 1) {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
  }
  else if (mode == 2) {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
  }
}
void robotMove(int Direction)
{
  switch (Direction) {  // 0 = stop, 1 = forward....5 =
    case 0:
      AMove(0);
      BMove(0);
      CMove(0);
      DMove(0);
      break;
    case 1:
      AMove(1);
      BMove(1);
      CMove(1);
      DMove(1);
      break;
    case 2:
      AMove(2);
      BMove(2);
      CMove(2);
      DMove(2);
      break;
    case 3:
      AMove(1);
      BMove(2);
      CMove(2);
      DMove(1);
      break;
    case 4:
      AMove(2);
      BMove(1);
      CMove(1);
      DMove(2);
      break;
  }
}
int getDistance() {
  long duration, distance;
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trig, 0);
  delayMicroseconds(2);
  digitalWrite(trig, 1);
  delayMicroseconds(10);
  digitalWrite(trig, 0);
  duration = pulseIn(echo, 1);
  distance = duration / 29 / 2; //Distance is measured in Centimeters
  return distance;
}

bool checkSides(int dir) {
  if (dir == 0) {
    myservo.write(5);
  } else {
    myservo.write(175);
  }
  delay(700);
  
  if (getDistance() > 15) {
    Serial.println("ok!");
    return 1;
  }
  else {
    Serial.println("nope!");
    return 0;
  }
}

void loop() {
  Serial.print(turn);
  Serial.println(getDistance());
  if (getDistance() > 15) {
    robotMove(1);
  } else {
    robotMove(0);
    if (turn == 1) {
      if (checkSides(0)) {
        robotMove(3);
        myservo.write(90);
        delay(1000);
        robotMove(0);
        turn = 1;
      }
      else if (checkSides(1)) {
        robotMove(4);
        myservo.write(90);
        delay(1000);
        robotMove(0);
        turn = 0;
      } else {
        robotMove(2);
        while (checkSides(0) + checkSides(1) == 0) {}
        robotMove(0);
        myservo.write(90);
        if (turn == 1) {
          if (checkSides(0)) {
            robotMove(3);
            myservo.write(90);
            delay(2000);
            robotMove(0);
            turn = 1;
          } if (checkSides(1)) {
            robotMove(4);
            myservo.write(90);
            delay(2000);
            robotMove(0);
            turn = 0;
          }
        }
      }
    } else if (turn == 0) {
      if (checkSides(1)) {
        robotMove(4);
        myservo.write(90);
        delay(1000);
        robotMove(0);
        turn = 0;
      }
      else if (checkSides(0)) {
        robotMove(3);
        myservo.write(90);
        delay(1000);
        robotMove(0);
        turn = 1;
      } else {
        robotMove(2);
        while (checkSides(0) + checkSides(1) == 0) {}
        robotMove(0);
        myservo.write(90);
        if (turn == 1) {
          if (checkSides(0)) {
            robotMove(3);
            myservo.write(90);
            delay(2000);
            robotMove(0);
            turn = 1;
          } if (checkSides(1)) {
            robotMove(4);
            myservo.write(90);
            delay(2000);
            robotMove(0);
            turn = 0;
          }
        }
      }
    }
  }
}
