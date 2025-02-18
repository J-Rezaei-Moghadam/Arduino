int led = 4;
bool ledstate = LOW;

void setup() {
pinMode(led,OUTPUT);
pinMode(2,INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(2),myled,LOW);
}

void loop() {
digitalWrite(led,ledstate);
}

void myled(){
ledstate = !ledstate;
}