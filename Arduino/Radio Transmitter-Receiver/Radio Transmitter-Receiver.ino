/* 

  Arduino nano Tutorial

  Project name: Radio Transmitter/Receiver

  author: jalal rezaee moghadam

*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

boolean ok ;
int speed ;
int distanceval ;

int transmiting_payload[2]; // Array for Storing Transmitting Variables
int received_payload[2]; // Array for Storing Receiving Variables

/////////////NRF Setting//////////

// Hardware configuration
// Set up nRF24L01 radio on SPI bus plus pins 7 & 8 
RF24 radio(7,8);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

// Role management
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
role_e role = role_pong_back;

/////////////////// End of NRF ///////////////////////

void setup() {
  
    Serial.begin(57600);
  
  //////////////NRF Print preamble////////////////////
    Serial.println("NRF24L01 Default Mode is:");
    Serial.println(role_friendly_name[role]);
  
  // Setup and configure rf radio
    radio.begin();

  // optionally, increase the delay between retries
    radio.setRetries(15,15);

    radio.openReadingPipe(1,pipes[1]);
  
  // Start listening
    radio.startListening();

  // Dump the configuration of the rf unit for debugging
    radio.printDetails();

  // NRF Change roles
    NRF_ChangeRole();
/////////////////////End of NRF////////////////////////////
}

void loop() {
    
    //
    Speed();
        
    //NRF Transmitting (Default Mode)
      NRF_Transmitting();

    //NRF Receiving
      NRF_Receiving();
      
    //Printing Data Enable this line only for Debugguing
    print_data(); 
}    


int NRF_Transmitting(){
  
    if (role == role_ping_out)
  {
    // First, stop listening so we can talk.
    radio.stopListening();
    
    ok = radio.write( transmiting_payload, sizeof(transmiting_payload) ); 

    // Now, continue listening
    radio.startListening();
    
    // Try again 1s later
    delay(50);
  }  
}

int NRF_Receiving(){

    // if there is data ready
    if ( radio.available())
    {
      // Dump the payloads until we've gotten everything
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( received_payload, sizeof(received_payload) );

      // Delay just a little bit to let the other unit
      // make the transition to receiver
       delay(20);
      }
      
      //Extract Receiving Data
       distanceval = received_payload[0];
       
      // First, stop listening for the next time we can talk
      radio.stopListening();
	      }
}

void NRF_ChangeRole(){
      Serial.println("You Are in Transmitting Mode (Default)");

      // Become the primary transmitter (ping out)
      role = role_ping_out;
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1,pipes[1]);
}  

int Speed(){
  
  speed = 40 ;
  transmiting_payload[0] = speed ; 
  return(transmiting_payload[0]); 

}

void print_data(){
  
      if (ok){

      Serial.println("Transmitting payload:");        
      Serial.print("speed is = ");
      Serial.print(speed);

      Serial.println("Receiving Payload");
      Serial.print("distance is = ");
      Serial.print(distanceval);

      ok = false;    
    }
      
    else{
      Serial.println("Failed to connect");
    }
}