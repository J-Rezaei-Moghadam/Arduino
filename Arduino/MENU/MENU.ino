int led = 9;

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  Serial.println("1= LED ON 2= LED Blink 3=LED OFF");
}

void loop() {
  switch (sread()){
    case 1:
      digitalWrite(led,HIGH);
      Serial.println("LED is ON");
      Serial.println("ENTER 8 or 9:");
      switch (s2read()){
        case 9:
          Serial.println("Shoma 9 ra vared Konid");
          Serial.println("1= LED ON 2= LED Blink 3=LED OFF");
        break;

        case 8:
          Serial.println("irenx.ir Mohammad Rahimi");
          Serial.println("1= LED ON 2= LED Blink 3=LED OFF");
        break;
      }
    break;
    case 2:
      Serial.println("LES is Blinking");
      for (int i = 0; i<=20;i++){
        digitalWrite(led,HIGH);
        delay(300);
        digitalWrite(led,LOW);
        delay(300);
      }
    break;

    case 3:
    Serial.println("LED is OFF");
      digitalWrite(led,LOW);
    break;
  }
}

int sread(){
  char c = Serial.read();
  if (c == '1'){
    return 1;
  }
  else if (c == '2'){
    return 2;
  }
  else if(c == '3'){
    return 3;
  }
  else{
    return 0;
  }
}

int s2read(){
  again:
  char c = Serial.read();
  if (c == '8'){
    return 8;
  }
  else if (c == '9'){
    return 9;
  }
  else{
    goto again;
  }
}