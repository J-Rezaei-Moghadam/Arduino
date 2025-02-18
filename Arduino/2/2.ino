#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 
RF24 radio(7,8);
// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
int payload[2];
// Role management
typedef enum { role_ping_out = 1, role_pong_back } role_e;
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};
role_e role = role_pong_back;

void setup(void){  
  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");
  // Setup and configure rf radio//
  radio.begin();
  radio.setRetries(15,15);
  radio.openReadingPipe(1,pipes[1]);
  // Start listening
  radio.startListening();
  radio.printDetails();
}

void loop(void){  
  // Ping out role.  Repeatedly send the current time
    jalal_read();    
  if (role == role_ping_out)
  {
    // First, stop listening so we can talk.
    radio.stopListening();
    // Take the time, and send it.  This will block until complete
    unsigned long time = millis();
    printf("Now sending %lu...",payload[0]);
    bool ok = radio.write( &payload, sizeof(payload) );
    if (ok)
      printf("ok...");
    else
      printf("failed.\n\r");
    // Now, continue listening
    radio.startListening();
    // Wait here until we get a response, or timeout (250ms)
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;
    // Describe the results
    if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      unsigned long got_time;
      radio.read( &got_time, sizeof(unsigned long) );
      // Spew it
      printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);
    }
    // Try again 1s later
    delay(1000);
  }
  // Pong back role.  Receive each packet, dump it out, and send it back
  if ( role == role_pong_back )
  {
    // if there is data ready
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      unsigned long got_time;
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &got_time, sizeof(got_time) );
        // Spew it
        printf("Got payload %lu...",got_time);
	// Delay just a little bit to let the other unit
	// make the transition to receiver
	delay(20);
      }
      // First, stop listening so we can talk
      radio.stopListening();
      // Send the final one back.
      radio.write( &got_time, sizeof(unsigned long) );
      printf("Sent response.\n\r");
      // Now, resume listening so we catch the next packets.
      radio.startListening();
    }
  }

  // Change roles
  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == role_pong_back )
    {
      printf("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK\n\r");
      // Become the primary transmitter (ping out)
      role = role_ping_out;
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1,pipes[1]);
    }
    else if ( c == 'R' && role == role_ping_out )
    {
      printf("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK\n\r");
      // Become the primary receiver (pong back)
      role = role_pong_back;
      radio.openWritingPipe(pipes[1]);
      radio.openReadingPipe(1,pipes[0]);
    }
  }
}

int jalal_read(){

payload[0] = 1375;
delay(50);
return(payload[0]);
}
