int x = A0;
int y = A1;
int SW = 2;

int up = 3;
int right = 4;
int left = 5;
int down = 6;

int xpos;
int ypos;
int swstate;

void setup() {
pinMode(x,INPUT);
pinMode(y,INPUT);
pinMode(SW,INPUT_PULLUP);

pinMode(up,OUTPUT);
pinMode(right,OUTPUT);
pinMode(left,OUTPUT);
pinMode(down,OUTPUT);
}

void loop() {
xpos = analogRead(x);
ypos = analogRead(y);
  
if (xpos == 1023){
digitalWrite(right,HIGH);
}
else{
digitalWrite(right,LOW);
}

if (xpos == 0){
digitalWrite(left,HIGH);
}
else{
digitalWrite(left,LOW);
}

if (ypos == 1023){
digitalWrite(up,HIGH);
}
else{
digitalWrite(up,LOW);
}

if(ypos == 0){
digitalWrite(down,HIGH);
}
else{
digitalWrite(down,LOW);
}

swstate = digitalRead(SW);
if (swstate == LOW){
digitalWrite(up,HIGH);
digitalWrite(right,HIGH);
digitalWrite(left,HIGH);
digitalWrite(down,HIGH);
}

}