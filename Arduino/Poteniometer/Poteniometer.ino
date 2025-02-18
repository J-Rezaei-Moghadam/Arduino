int LED = 5;
int pot = A0;

void setup() {
  pinMode(LED,OUTPUT);
}

void loop() {
  int value = analogRead(pot);
  int duty = map(value,0,1023,0,255);
  analogWrite(LED,duty);
  delay(100);
}