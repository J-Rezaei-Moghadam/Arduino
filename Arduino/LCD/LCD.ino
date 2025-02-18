#include <LiquidCrystal.h>
int rs = 2 , en = 3 , d4 = 4 , d5 = 5 , d6 = 6 , d7 = 7 ; 
// VSS=GND,VDD=vcc,VO=pot,RW=GND,A=vcc,K=GND
LiquidCrystal lcd (rs,en,d4,d5,d6,d7);

void setup() {
lcd.begin(16,2);
lcd.clear();
}

void loop() {
lcd.setCursor(0,0);
lcd.print("Hello");
delay(1000);
lcd.clear();  
}
