int BUTTON = 2;
int BUZZER = 8;

void setup() {
  pinMode(BUTTON,INPUT_PULLUP);
  pinMode(BUZZER,OUTPUT);
}

void loop() {
  int state1 = digitalRead(BUTTON);
  if(state1 == LOW){
    tone(BUZZER,196);
  }
  else{
    noTone(BUZZER);
  }
}