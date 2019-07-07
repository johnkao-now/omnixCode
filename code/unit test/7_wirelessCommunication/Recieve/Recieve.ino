#include <SPI.h>
#include <RF24.h>

//RF24L01配置
RF24 radio(9, 8); // CE, CSN
const byte address[6] = "00010";

int ledA = 5;
int ledB = 2;
int ledC = 3;
int ledD = 4;

//接收的数据结构
struct dataStruct {
  unsigned long _micros;
  bool btnA;
  bool btnB;
  bool btnC;
  bool btnD;
} myData;

void setup() {
  Serial.begin(9600);
  radioSetup();
  ledSetup();
}

void loop(){
  getData();
}

void getData(){//获取数据内容并打印在屏幕上
  if (radio.available()){
    radio.read( &myData, sizeof(myData) );
  
  //点亮对应LED
  if(myData.btnA){digitalWrite(ledA,HIGH);}else{digitalWrite(ledA,LOW);}
  if(myData.btnB){digitalWrite(ledB,HIGH);}else{digitalWrite(ledB,LOW);}
  if(myData.btnC){digitalWrite(ledC,HIGH);}else{digitalWrite(ledC,LOW);}
  if(myData.btnD){digitalWrite(ledD,HIGH);}else{digitalWrite(ledD,LOW);}
  
  //打印内容
  Serial.print("btnA: ");
    Serial.print(myData.btnA);
    Serial.print(" ||btnB: ");
    Serial.print(myData.btnB);
    Serial.print(" ||btnC: ");
    Serial.print(myData.btnC);
    Serial.print(" ||btnD: ");
    Serial.println(myData.btnD);
  
    delay(50);
    
  } 
}

void radioSetup(){//RF24L01接收端初始化
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
}

void ledSetup(){
  pinMode(ledA,OUTPUT);
  pinMode(ledB,OUTPUT);
  pinMode(ledC,OUTPUT);
  pinMode(ledD,OUTPUT);
}

