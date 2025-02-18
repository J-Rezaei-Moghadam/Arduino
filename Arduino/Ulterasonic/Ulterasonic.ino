int echo = 3;
int trig = 2;

long zaman;
int fasele;

void setup() {
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
}

void loop() {
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  zaman = pulseIn(echo,HIGH);
  fasele = zaman * 0.034 / 2;
  delay(500);
}