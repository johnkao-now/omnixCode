#define Urx A0
#define Ury A1
int x;
void setup() {
  pinMode(Urx,INPUT);
  pinMode(Ury,INPUT);
  Serial.begin(115200);

}

void loop() {
  Serial.print(readX());
  Serial.print("    ");
  Serial.println(readY());

}
int readX () {
  int x = analogRead(Urx);
  return x;
}
int readY () {
  int y = analogRead(Ury);
  return y;
}
 unsigned int analyzeX() {
  if (readX() > 750) {
    return 1;
  } else if (readX() < 350) {
    return 2;
  }else {return 0;}
}
 unsigned int analyzeY() {
  if (readY() > 750) {
    return 1;
  } else if (readY() < 350) {
    return 2;
  }else {return 0;}
}
