#define one 2
#define two 3
#define three 4
#define four 5

void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);

}

void loop() {
  Serial.print(digitalRead(one));
  Serial.print(digitalRead(two));
  Serial.print(digitalRead(three));
  Serial.println(digitalRead(four));
}
