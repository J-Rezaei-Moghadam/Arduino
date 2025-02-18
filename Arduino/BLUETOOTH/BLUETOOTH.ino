#include <LiquidCrystal.h>
int rs = 10 , en = 9 , d4 = 4 , d5 = 5 , d6 = 6 , d7 = 7 ; 
// VSS=GND,VDD=vcc,VO=pot,RW=GND,A=vcc,K=GND
LiquidCrystal lcd (rs,en,d4,d5,d6,d7);

#include "SoftwareSerial.h"
int RXD = 13 , TXD = 12 ;
SoftwareSerial bluetooth(RXD,TXD);

int RELAY = 1;

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  bluetooth.begin(9600);
  Serial.begin(9600);
  pinMode(RELAY,OUTPUT);
}

void loop() {
  if (bluetooth.available()>0){
    char data = bluetooth.read();
    if(data == '1' ){
    digitalWrite(RELAY,HIGH);        
    Serial.println("relay is on");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("relay is on");    
    bluetooth.write("relay on");
    }    
    else if(data=='2'){
    digitalWrite(RELAY,LOW);        
    Serial.println("relay is off");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("relay is off"); 
    bluetooth.write("relay off");
    }
    else{
    Serial.println("relay");
    bluetooth.write("relay");      
    }        
    delay(500);      
   }
}