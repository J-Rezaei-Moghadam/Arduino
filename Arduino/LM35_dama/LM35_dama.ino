int sensordama = A0;
int damaadc;
float dama;

void setup() {  
pinMode(sensordama,INPUT);
}

void loop() {
damaadc = analogRead(sensordama);
dama = damaadc * 4.88;
dama = dama/10;
}