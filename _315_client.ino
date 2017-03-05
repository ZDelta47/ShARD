// client.pde
//
// Simple example of how to use VirtualWire to send and receive messages
// with a DR3100 module.
// Send a message to another arduino running the 'server' example, which
// should send a reply, which we will check
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: client.pde,v 1.1 2008/04/20 09:24:17 mikem Exp $

#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;
const char *msg = "hello";
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;


void setup()
{
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  Serial.begin(9600);	// Debugging only
  Serial.println("setup,client");

  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
  vw_rx_start();       // Start the receiver PLL running


  digitalWrite(13, true); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); // Wait until the whole message is gone
  Serial.println("Sent");
  digitalWrite(13, false);
}
boolean flag = 0;

void loop()
{
  if (vw_wait_rx_max(200))
  {
    vw_wait_rx();
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      int i;

      // Message with a good checksum received, dump it.
      Serial.print("Got: ");

      for (i = 0; i < buflen; i++)
      {
        Serial.print(buf[i], HEX);
        Serial.print(" ");
      }
      Serial.println("");
      

    }
    delay(20);
  }
  
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); // Wait until the whole message is gone
  Serial.println("Sent");
  

}
//else
//Serial.println("Timout");



