#define Urx A0
#define Ury A1
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#define OLED_RESET 4
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
Adafruit_SH1106 display(OLED_RESET);
#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif
int speedFactor = 0;
int dotX = 64;
int dotY = 32;
int r = 3;
int x;
int y;
void setup() {
  pinMode(Urx, INPUT);
  pinMode(Ury, INPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(115200);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  delay(1000);
  display.clearDisplay();
  display.drawChar(5, 10, 'M', WHITE, BLACK, 2);
  display.drawChar(20, 10, 'o', WHITE, BLACK, 2);
  display.drawChar(35, 10, 'v', WHITE, BLACK, 2);
  display.drawChar(50, 10, 'e', WHITE, BLACK, 2);
  display.drawChar(70, 10, 'T', WHITE, BLACK, 2);
  display.drawChar(85, 10, 'h', WHITE, BLACK, 2);
  display.drawChar(100, 10, 'e', WHITE, BLACK, 2);
  display.drawChar(30, 30, 'D', WHITE, BLACK, 3);
  display.drawChar(55, 30, 'o', WHITE, BLACK, 3);
  display.drawChar(80, 30, 't', WHITE, BLACK, 3);
  display.display();
  delay(8000);
  display.clearDisplay();

}

void loop() {
  analyzeX();
  analyzeY();
  explode();
  inhale();
  display.clearDisplay();
  display.drawCircle(dotX, dotY, r, WHITE);
  display.drawCircle(dotX, dotY, r - 2, WHITE);
  display.drawCircle(dotX, dotY, r - 4, WHITE);
  display.drawCircle(dotX, dotY, r - 6, WHITE);
  display.drawCircle(dotX, dotY, r - 8, WHITE);
  display.drawCircle(dotX, dotY, r - 10, WHITE);
  display.drawCircle(dotX, dotY, r - 12, WHITE);
  display.drawCircle(dotX, dotY, r - 14, WHITE);
  display.drawCircle(dotX, dotY, r - 16, WHITE);
  display.display();
  delay(50);
}
int readX () {
  x = analogRead(Urx);
  return x;
}
int readY () {
  y = analogRead(Ury);
  return y;
}
void analyzeX() {
  if (readY() > 750) {
    dotX += (2 + speedFactor);
  } else if (readY() < 350) {
    dotX -= (2 + speedFactor);
  }
}
void analyzeY() {
  if (readX() < 350) {
    dotY += (2 + speedFactor);
  } else if (readX() > 750) {
    dotY -= (2 + speedFactor);
  }
}
void explode() {
  if (!digitalRead(2)) {
    r = r + 2;
    speedFactor += 5;
  }

}
void inhale() {
  if (!digitalRead(3)) {
    r = r - 2;
    speedFactor += 10;
  }

}
