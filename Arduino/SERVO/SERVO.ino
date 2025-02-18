#include <Servo.h>
Servo servo1;

void setup() {
servo1.attach(0);
}

void loop() {
  for(int angle = 0; angle<180;angle+=40){
    servo1.write(angle);
    delay(1000);
  }
  for (int angle = 180;angle>0;angle-=40){
    servo1.write(angle);
    delay(1000);
  }
}