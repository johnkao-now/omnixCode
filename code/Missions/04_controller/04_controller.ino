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
#include <RF24.h>
const byte address[6] = "00030";
RF24 radio(A5, A6);
int btnA = 2;
int btnB = 3;
int btnC = 4;
int btnD = 5;
int dotX = 1;
struct dataStruct {
  unsigned long _micros;
  bool btnA;
  bool btnB;
  bool btnC;
  bool btnD;
} myData;
void setup() {
  pinMode(Urx, INPUT);
  pinMode(Ury, INPUT);
  pinMode(6, INPUT_PULLUP);
  Serial.begin(115200);
  btnSetup();
  radioSetup();
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  delay(1000);
  display.clearDisplay();
  display.drawChar(35, 5, 'T', WHITE, BLACK, 2);
  display.drawChar(50, 5, 'h', WHITE, BLACK, 2);
  display.drawChar(65, 5, 'e', WHITE, BLACK, 2);
  display.drawChar(2, 20, 'E', WHITE, BLACK, 2);
  display.drawChar(17, 20, 'x', WHITE, BLACK, 2);
  display.drawChar(32, 20, 'p', WHITE, BLACK, 2);
  display.drawChar(47, 20, 'l', WHITE, BLACK, 2);
  display.drawChar(62, 20, 'o', WHITE, BLACK, 2);
  display.drawChar(77, 20, 'r', WHITE, BLACK, 2);
  display.drawChar(92, 20, 'e', WHITE, BLACK, 2);
  display.drawChar(107, 20, 'r', WHITE, BLACK, 2);

  display.drawChar(17, 50, 'S', WHITE, BLACK, 1);
  display.drawChar(32, 50, 't', WHITE, BLACK, 1);
  display.drawChar(47, 50, 'a', WHITE, BLACK, 1);
  display.drawChar(62, 50, 'r', WHITE, BLACK, 1);
  display.drawChar(77, 50, 't', WHITE, BLACK, 1);
  display.drawChar(92, 50, 'u', WHITE, BLACK, 1);
  display.drawChar(107, 50, 'p', WHITE, BLACK, 1);

  for (int i = 0; i < 64; i++) {
    display.drawCircle(dotX, 43, 3, WHITE);
    dotX += 2;
    delay(200);
    display.display();
  }
  dotX = 1;
  for (int i = 0; i < 128; i++) {
    display.drawCircle(dotX, 43, 3, WHITE);
    dotX ++;
    display.display();
  }
  display.clearDisplay();
  display.drawChar(11, 5, 'C', WHITE, BLACK, 1);
  display.drawChar(21, 5, 'o', WHITE, BLACK, 1);
  display.drawChar(31, 5, 'n', WHITE, BLACK, 1);
  display.drawChar(41, 5, 'n', WHITE, BLACK, 1);
  display.drawChar(51, 5, 'e', WHITE, BLACK, 1);
  display.drawChar(61, 5, 'c', WHITE, BLACK, 1);
  display.drawChar(71, 5, 't', WHITE, BLACK, 1);
  display.drawChar(81, 5, 't', WHITE, BLACK, 1);
  display.drawChar(91, 5, 'i', WHITE, BLACK, 1);
  display.drawChar(101, 5, 'n', WHITE, BLACK, 1);
  display.drawChar(111, 5, 'g', WHITE, BLACK, 1);
  display.drawChar(5, 20, 'T', WHITE, BLACK, 2);
  display.drawChar(20, 20, 'o', WHITE, BLACK, 2);
  display.drawChar(49, 20, 'R', WHITE, BLACK, 2);
  display.drawChar(64, 20, 'o', WHITE, BLACK, 2);
  display.drawChar(79, 20, 'b', WHITE, BLACK, 2);
  display.drawChar(94, 20, 'o', WHITE, BLACK, 2);
  display.drawChar(109, 20, 't', WHITE, BLACK, 2);
  display.display();
  dotX = 1;
  for (int i = 0; i < 64; i++) {
    display.drawCircle(dotX, 49, 7, WHITE);
    dotX += 2;
    delay(70);
    display.display();
  }
  dotX = 1;
  for (int i = 0; i < 128; i++) {
    display.drawCircle(dotX, 49, 7, WHITE);
    dotX ++;
    display.display();
  }
  display.clearDisplay();
  display.drawChar(1, 5, 'C', WHITE, BLACK, 2);
  display.drawChar(14, 5, 'O', WHITE, BLACK, 2);
  display.drawChar(27, 5, 'N', WHITE, BLACK, 2);
  display.drawChar(40, 5, 'N', WHITE, BLACK, 2);
  display.drawChar(53, 5, 'E', WHITE, BLACK, 2);
  display.drawChar(66, 5, 'C', WHITE, BLACK, 2);
  display.drawChar(79, 5, 'T', WHITE, BLACK, 2);
  display.drawChar(92, 5, 'E', WHITE, BLACK, 2);
  display.drawChar(106, 5, 'D', WHITE, BLACK, 2);
  
  display.display();
}

void loop() {
  sendKey();
  delay(50);

}

void sendKey() {
  myData.btnA = !digitalRead(btnA);
  myData.btnB = !digitalRead(btnB);
  myData.btnC = !digitalRead(btnC);
  myData.btnD = !digitalRead(btnD);
  myData._micros = micros();
  radio.write(&myData, sizeof(myData));
}

void btnSetup() {
  pinMode(btnA, INPUT_PULLUP);
  pinMode(btnB, INPUT_PULLUP);
  pinMode(btnC, INPUT_PULLUP);
  pinMode(btnD, INPUT_PULLUP);
}
void radioSetup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

