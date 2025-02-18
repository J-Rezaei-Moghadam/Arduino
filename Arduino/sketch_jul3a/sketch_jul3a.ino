int echo = 3;
int trig = 2;
int led1 = 5 ;
int led2 = 6 ;

long zaman;
float fasele;

void setup() {
Serial.begin(9600);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
}

void loop() {
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  zaman = pulseIn(echo,HIGH);
  fasele = zaman * 0.034 / 2;
  Serial.println(fasele);
  delay(50);
  if(fasele<15 && fasele!=0){
    Serial.println("Play/Pause");
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
  }
  else if (fasele>15 && fasele<25){
    Serial.println("Forward");
    digitalWrite(led2,HIGH);
    digitalWrite(led1,LOW);
  }
  else{
    digitalWrite(led2,LOW);
    digitalWrite(led1,LOW);
  }
delay(350);
}