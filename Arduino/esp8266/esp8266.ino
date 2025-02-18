#include "SoftwareSerial.h"
int RXD = 4 , TXD = 5;
SoftwareSerial esp(RXD,TXD);

int red = 6;
int green = 7;
int blue = 8;

void setup() {
  Serial.begin(9600);
  esp.begin(115200);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);

  sendData("AT+RST\r\n",2000); // RESET
  sendData("AT+CWMODE=1\r\n",1000); //Client
  sendData("AT+CWJAP=\"Aask\",\"12345678\"\r\n",2000); //USER & PASS
  while(!esp.find("OK")){}
  sendData("AT+CIFSR\r\n",1000); // Get IP
  sendData("AT+CIPMUX=1\r\n",1000); // Single 
  sendData("AT+CIPSERVER=1,80\r\n",1000); // Create Server
}

void loop() {
  if(esp.find("+IPD,")){
    String msg;
    esp.find("?");
    msg = esp.readStringUntil(' ');
    int value = msg.toInt();
    Serial.println(value);
    if(value == 1){
      digitalWrite(red,HIGH);
    }
    else if(value == 2){
      digitalWrite(green,HIGH);
    }
    else if(value == 3){
      digitalWrite(blue,HIGH);
    }
    else{
      digitalWrite(red,LOW);
      digitalWrite(green,LOW);
      digitalWrite(blue,LOW);
    }
  }
}

String sendData(String command,int timeout){
  String response;
  esp.print(command);
  long time = millis();
    while(time+timeout>millis()){
      while(esp.available()){
        char c = esp.read();
        response += c;
      }
    }
    Serial.print(response);
    return response;
}