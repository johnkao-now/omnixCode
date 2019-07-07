#include <SPI.h>
#include <RF24.h>
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
//RF24L01配置
RF24 radio(5, 4); // CE, CSN
const byte address[6] = "00010";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
int dotX = 1;
//定义输入按键引脚
int btnA = 2;
int btnB = 3;
int joystickA = A0;
int joystickB = A1;
int joystickC = A2;
int joystickD = A3;

//发送的数据结构
struct dataStruct {
  unsigned long _micros;
  bool btnA;
  bool btnB;
  int joyStick_A_X;
  int joyStick_A_Y;
  int joyStick_B_X;
  int joyStick_B_Y;
} myData;

/*-----初始化函数-----*/
void setup() {
  Serial.begin(9600);
  btnSetup();
  radioSetup();
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  delay(1000);
  display.clearDisplay();
  display.drawChar(15, 5, 'O', WHITE, BLACK, 2);
  display.drawChar(35, 5, 'm', WHITE, BLACK, 2);
  display.drawChar(55, 5, 'n', WHITE, BLACK, 2);
  display.drawChar(75, 5, 'i', WHITE, BLACK, 2);
  display.drawChar(95, 5, 'x', WHITE, BLACK, 2);
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
    delay(120);
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
}

/*-----自定义函数-----*/

void sendKey() { //读取并发送按键电平信号
  myData.btnA = !digitalRead(btnA);
  myData.btnB = !digitalRead(btnB);
  myData.joyStick_A_X = analogRead(joystickA);
  myData.joyStick_A_Y = analogRead(joystickB);
  myData.joyStick_B_X = analogRead(joystickC);
  myData.joyStick_B_Y = analogRead(joystickD);
  myData._micros = micros();
  radio.write(&myData, sizeof(myData));
}

void btnSetup() { //设置按键为输入并内部上拉
  pinMode(btnA, INPUT_PULLUP);
  pinMode(btnB, INPUT_PULLUP);
  pinMode(joystickA, INPUT);
  pinMode(joystickB, INPUT);
  pinMode(joystickC, INPUT);
  pinMode(joystickD, INPUT);

}

void radioSetup() { //RF24L01发射端初始化
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}
