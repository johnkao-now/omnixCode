#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
#define trig A1
#define echo A0
#include <Servo.h>
#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif
int LX;
int LY;
int distance;
int angle = 0;
int data[180];
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int currentDistancea, currentDistanceb, currentDistancetotal;
void setup() {
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);              // tell servo to go to position in variable 'pos'
  delay(1000);
  Serial.begin(9600);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  delay(2100);
}

void loop() {
  //  testdrawline();
  //  display.display();
  for (pos = 0; pos <= 180; pos += 4) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);   // tell servo to go to position in variable 'pos'
    distance = averageDistance();
    data[angle] = distance;
    display.clearDisplay();
    LX = 64 + 64 * cos(toRadians(pos));
    LY = 64 - 64 * sin(toRadians(pos));
    Serial.print(LX);
    Serial.print("        ");
    Serial.println(LY);
    display.drawLine(LX, LY, 64, 64, WHITE);
    display.display();
  }
  for (pos = 180; pos >= 0; pos -= 4) { // goes from 180 degrees to 0 degrees
    // in steps of 1 degree
    myservo.write(pos);   // tell servo to go to position in variable 'pos'
    distance = averageDistance();
    data[angle] = distance;
    display.clearDisplay();
    LX = 64 + 64 * cos(toRadians(pos));
    LY = 64 - 64 * sin(toRadians(pos));
    Serial.print(LX);
    Serial.print("        ");
    Serial.println(LY);
    display.drawLine(LX, LY, 64, 64, WHITE);
    display.display();ss
  }
}
float toRadians(float degrees) {
  return degrees / 360 * 2 * 3.14159267;
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
int averageDistance() {
  currentDistancea = getDistance() + getDistance() / 2;
  delayMicroseconds(3);
  currentDistanceb = getDistance() + getDistance() + getDistance() / 3;
  currentDistancetotal = currentDistancea + currentDistanceb / 2;
  return currentDistancetotal;
}

