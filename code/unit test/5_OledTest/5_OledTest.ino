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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
    display.drawChar(5, 10, 'H', WHITE, BLACK, 4);
  display.display();
  delay(20000);
}

void loop() {
  // put your main code here, to run repeatedly:
  // draw many lines
  testdrawline();
  display.display();

}
void testdrawline() {
  for (int16_t i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(64, 64, 0, i, WHITE);
    display.display();
    display.clearDisplay();/////////OK
  }
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(64, 64, i, 0, WHITE);
    display.display();
    display.clearDisplay();/////OK
  }
  for (int16_t i = 0; i < display.height(); i += 4) {
    display.drawLine(64, 64, display.width() - 1, i, WHITE);
    display.display();
    display.clearDisplay();/////////OK
  }
  for(int i = 64; i > 0; i -= 4) {
    display.drawLine(64, 64, 128, i, WHITE);
    display.display();
    display.clearDisplay(); ////////// ok
  }
  for (int i = 128; i > 0; i -= 4) {
    display.drawLine(64, 64, i, 0, WHITE);
    display.display();
    display.clearDisplay();//////////ok
  }
  for (int i = 0 - 1; i <= 64; i += 4) {
    display.drawLine(64, 64, 0, i, WHITE);
    display.display();
    display.clearDisplay();
  }
}
