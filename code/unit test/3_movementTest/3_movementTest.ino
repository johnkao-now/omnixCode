void setup() {
  for(int i=2;i<10;i++)
  
  pinMode(i,OUTPUT);

}
void AMove(int mode)// 0 is no action, 1 is foward, 2, is backward (movement)
{
  if(mode==0){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  }
  else if(mode==1){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  }
  else if(mode==2){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  }
}
void BMove(int mode)// 0 is no action, 1 is foward, 2, is backward (movement)
{
  if(mode==0){
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  }
  else if(mode==1){
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  }
  else if(mode==2){
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  }
}
void CMove(int mode)// 0 is no action, 1 is foward, 2, is backward (movement)
{
  if(mode==0){
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  }
  else if(mode==1){
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  }
  else if(mode==2){
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  }
}
void DMove(int mode)// 0 is no action, 1 is foward, 2, is backward (movement)
{
  if(mode==0){
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  }
  else if(mode==1){
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  }
  else if(mode==2){
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
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





void loop() {
  for(int DirNum=1;DirNum<5;DirNum++){
    robotMove(DirNum);
    delay(2000);
    robotMove(0);
    delay(100);
  }
}

