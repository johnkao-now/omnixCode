
#define trig A1 
#define echo A0
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int currentDistancea,currentDistanceb,currentDistancetotal;
void setup() {
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);              // tell servo to go to position in variable 'pos'
  delay(1000);     
  Serial.begin(9600);
  
}

void loop() {
  
  for (pos = 30; pos <= 150; pos += 4) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);   // tell servo to go to position in variable 'pos'
    Serial.print("Pos:");
    Serial.print(pos);
    Serial.print(" currentDistance:");
    currentDistancea = getDistance()+getDistance()/2;
    currentDistanceb = getDistance()+getDistance()+getDistance()/3;
    currentDistancetotal = currentDistancea+currentDistanceb/2;
    Serial.println(currentDistancetotal);
    delay(90);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 150; pos >= 30; pos -= 4) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);   // tell servo to go to position in variable 'pos'
    Serial.print("Pos:");
    Serial.print(pos);
    Serial.print(" currentDistance:");
    currentDistancea = getDistance()+getDistance()/2;
    currentDistanceb = getDistance()+getDistance()+getDistance()/3;
    currentDistancetotal = currentDistancea+currentDistanceb/2;
    Serial.println(currentDistancetotal);
    delay(90);                     // waits 15ms for the servo to reach the position
  }
}
int getDistance(){
  long duration, distance;
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  digitalWrite(trig,0);
  delayMicroseconds(2);
  digitalWrite(trig,1);
  delayMicroseconds(10);
  digitalWrite(trig,0);
  duration =pulseIn(echo,1);
  distance = duration/29/2; //Distance is measured in Centimeters
  return distance;
}
