/*
  Blink LED

  Turns an LED on for one second, then off for one second, repeatedly.
  it is attached to digital pin 2 .

*/

int LedPin = 2 ;

// the setup function runs once when you press reset or power the board
void setup() {  
  // initialize digital pin LedPin as an output.
pinMode(LedPin,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LedPin, HIGH);  //turn the LED on by making the voltage HIGH
  delay(1000);                 //wait for a second
  digitalWrite(LedPin, LOW);   //turn the LED off by making the voltage LOW
  delay(1000);                 //wait for a second
}