int LED = 4 ;
int BUTTON = 5 ;

void setup() {
pinMode(LED,OUTPUT);
pinMode(BUTTON,INPUT_PULLUP);
}

void loop() {
int state = digitalRead(BUTTON); 
if(state == LOW){
digitalWrite(LED,HIGH);
}   
else{
digitalWrite(LED,LOW);
}

}
