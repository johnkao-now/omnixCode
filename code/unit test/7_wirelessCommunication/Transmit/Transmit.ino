//// rEMEME BER TO INCLUDE KUUUUUUUUKUUKUKUKUKJ

#include <SPI.h>
#include <RF24.h>
const byte address[6] = "00010";
RF24 radio(A5, A6);
int btnA = 2;
int btnB = 3;
int btnC = 4;
int btnD = 5;

struct dataStruct {
  unsigned long _micros;
  bool btnA;
  bool btnB;
  bool btnC;
  bool btnD;
} myData;
void setup() {
  Serial.begin(9600);
  btnSetup();
  radioSetup();

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

