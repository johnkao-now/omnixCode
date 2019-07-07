#define trig A1 
#define echo A0
void setup() {
  Serial.begin(115200);

}

void loop() {

 Serial.println(getDistance());
 delay(100);
}
int getDistance(){
  long duration, distance;
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  digitalWrite(trig,0);
  delayMicroseconds(2);
  digitalWrite(trig,1);
  delayMicroseconds(10);
  digitalWrite(trig,0);
  duration =pulseIn(echo,1);
  distance = duration/29/2; //Distance is measured in Centimeters
  return distance;
//  return duration;
}

