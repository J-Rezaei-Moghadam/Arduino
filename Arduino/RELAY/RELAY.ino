int RELAY = 4 ;
int BUTTON = 5 ;

void setup() {
pinMode(RELAY,OUTPUT);
pinMode(BUTTON,INPUT_PULLUP);
}

void loop() {
int state = digitalRead(BUTTON); 
if(state == HIGH){
digitalWrite(RELAY,HIGH);
}   
else{
digitalWrite(RELAY,LOW);
}

}
