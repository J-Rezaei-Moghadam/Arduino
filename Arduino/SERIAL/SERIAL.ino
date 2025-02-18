int relay = 4;

void setup() {
  Serial.begin(9600);
  pinMode(relay,OUTPUT);
}

void loop() {
  while (Serial.available() > 0){
    int data = Serial.read();
    if (data == 'a'){
      digitalWrite(relay,HIGH);
      Serial.println("Relay is ON");
    }
    if (data == 'b'){
      digitalWrite(relay,LOW);
      Serial.println("Relay is OFF");
    }
  }
}