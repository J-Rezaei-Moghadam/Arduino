/* 

  Arduino uno Tutorial

  Project name: Robot Receiver

  author: jalal rezaee moghadam

*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

/////////////L298 PinOut////////////////
int ENA=3,IN1=2,IN2=4; //Motors left
int ENB=5,IN3=6,IN4=9; //Motors right
////////////////////////////////////////

int speedval ; 
int distance ;

int received_payload[2]; // Variable for Storing Received Value
int transmitting_payload[2]; // Variable for Storing Transmitting Value

// Hardware configuration
// Set up nRF24L01 radio on SPI bus plus pins 7 & 8 
RF24 radio(7,8);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

// Role management
// The various roles supported by this sketch
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
role_e role = role_pong_back;

/////////////////// End of NRF ///////////////////////

void setup(void){
   
    Serial.begin(57600);

  //////////////NRF Print preamble////////////////////    
    Serial.println("NRF24L01 Default Mode is:");
    Serial.println(role_friendly_name[role]);

  // Setup and configure rf radio
     radio.begin();

  // optionally, increase the delay between retries
     radio.setRetries(15,15);

     radio.openWritingPipe(pipes[1]);
     radio.openReadingPipe(1,pipes[0]);

  // NRF Change roles
     NRF_ChangeRole();
     
  // Start listening
     radio.startListening();

  // Dump the configuration of the rf unit for debugging
     radio.printDetails();
/////////////////////End of NRF////////////////////////////

  //////L298////////
     pinMode(ENA,OUTPUT);
     pinMode(IN1,OUTPUT);
     pinMode(IN2,OUTPUT);
 
     pinMode(ENB,OUTPUT);
     pinMode(IN3,OUTPUT);
     pinMode(IN4,OUTPUT);
  //////////////////
}

void loop(void){
  
  //
    Distance();
     
  // NRF Receiving Mode (Default)
     NRF_Receiving();

  //NRF Transmitting
     NRF_Transmitting();
     
  //Printing Data Enable this line only for Debugguing
  //print_data();

 //Move Robot
   
    if(speedval==10){
         TurnRight();
         //Serial.println("right");
    }
  
    if(speedval==20){
         TurnLeft();
        // Serial.println("left");
    }  

    if(speedval==30){
         MoveForward();
         //Serial.println("forward");
    }

     if(speedval==40){
         MoveBackward();
         //Serial.println("backward");
    }    

     if(speedval==50){
         stoping();
         //Serial.println("stop");
    } 

}

int NRF_Transmitting(){
  
    bool ok = radio.write( transmitting_payload, sizeof(transmitting_payload) );

    if(ok){
      Serial.println("Successfuly Sending Sensor Data");
    }
    // Now, continue listening
    radio.startListening();

    // Try again 1s later
    delay(50);
}

int NRF_Receiving(){

    if ( role == role_pong_back ){

    // if there is data ready
    if ( radio.available() ){

      // Dump the payloads until we've gotten everything
      bool done = false;
      while (!done){
        
        // Fetch the payload, and see if this was the last one.
        done = radio.read( received_payload, sizeof(received_payload) );

  // Delay just a little bit to let the other unit
  // make the transition to receiver
  delay(20);
      }
      
  //Extract Receiving Data
  speedval = received_payload[0];

      // First, stop listening so we can talk
      radio.stopListening();

    }
  }
}

void NRF_ChangeRole(){
  
      Serial.println("You Are in Receiving Mode (Default)");
      // Become the primary receiver (pong back)
      role = role_pong_back;
      radio.openWritingPipe(pipes[1]);
      radio.openReadingPipe(1,pipes[0]);
} 

int Distance(){

  distance = 30 ;
  transmitting_payload[0] = distance ;    
  return(transmitting_payload[0]);  
}

void MoveForward(){
  //Serial.println("forward");
 digitalWrite(IN1,HIGH);
 digitalWrite(IN2,LOW);
 
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
 
 analogWrite(ENA,255);
 analogWrite(ENB,255);   
}

void MoveBackward(){
  //Serial.println("backward");
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,HIGH);
 
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
 
 analogWrite(ENA,128);
 analogWrite(ENB,128);    
}

void TurnRight(){
  //Serial.println("right");
 digitalWrite(IN1,HIGH);
 digitalWrite(IN2,LOW);
 
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,LOW);
 
 analogWrite(ENA,200);
 analogWrite(ENB,0);  
}

void TurnLeft(){
  //Serial.println("left");
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);
 
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
 
 analogWrite(ENA,0);
 analogWrite(ENB,200); 
}

void stoping(){
  //Serial.println("stop");
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);
 
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,LOW);
 
 analogWrite(ENA,0);
 analogWrite(ENB,0);  
}

