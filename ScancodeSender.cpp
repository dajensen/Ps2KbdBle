#include "ScancodeSender.h"
#include "debug.h"

ScancodeSender::ScancodeSender(int datapin, int rdypin, int ackpin, int wordpin) {
  data_pin = datapin;
  rdy_pin = rdypin;
  ack_pin = ackpin;
  word_pin = wordpin;

  rdy_val = 0;
  ack_val = 1;
  word_val = 0;
}

void ScancodeSender::begin() {

  digitalWrite(data_pin, LOW);
  digitalWrite(rdy_pin, LOW);
  digitalWrite(word_pin, LOW);

  pinMode(data_pin, OUTPUT);
  pinMode(rdy_pin, OUTPUT);
  pinMode(word_pin, OUTPUT);
    
  pinMode(ack_pin, INPUT_PULLUP);
  digitalWrite(ack_pin, HIGH);

  dprint("Initial Handshake Sent\n");

  uint8_t ackval = digitalRead(ack_pin);
  dprint8("Ack", ackval);
  
  // Because we've set it to INPUT_PULLUP, the value will read as 1 (which is how we initialized ack_val)
  // until the receiver sets the ack_pin to OUTPUT and drives the pin low.
  wait_for_ack();

  dprint("Got an ack\n");
}

void ScancodeSender::send(uint8_t c) {

  dprint8("Sending", c);
  
  // Change the word pin
  word_val = !word_val;
  digitalWrite(word_pin, word_val); 
   

  // Send out all of the bits
  for(int i = 0; i < 8; i++) {
    send_bit(c & 0x01);
    c >>= 1;
  }
//  dprint("Send complete\n");
}

void ScancodeSender::send_bit(uint8_t c) {

//  dprint8("bit", c);
  
  // Set the data pin to the right value
  digitalWrite(data_pin, c);

  // Set the rdy pin
  rdy_val = !rdy_val;
  digitalWrite(rdy_pin, rdy_val);

  // Wait for the ack pin to change
  wait_for_ack();
}

void ScancodeSender::wait_for_ack() {

  // When the ack_val and the value on ack_pin are the same,
  // the bit is not acknowledged.  We're waiting for the value on ack_pin to change.
  bool receiver_ready = false;
  while(!receiver_ready) {
    int val = digitalRead(ack_pin);
    if(val != ack_val) {
      ack_val = val;
      receiver_ready = true;      
    }
  }
}

