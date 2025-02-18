int LEDRED = 2 , LEDBLUE = 3 , LEDGREEN = 4 ;

void setup() {
pinMode(LEDRED,OUTPUT);
pinMode(LEDBLUE,OUTPUT);
pinMode(LEDGREEN,OUTPUT);
}

void loop() {
digitalWrite(LEDRED,HIGH);
delay(1000);
digitalWrite(LEDRED,LOW);
digitalWrite(LEDBLUE,HIGH);
delay(1000);
digitalWrite(LEDBLUE,LOW);
digitalWrite(LEDGREEN,HIGH);
delay(1000);
digitalWrite(LEDGREEN,LOW);
}
