
#ifndef ScancodeSender_h
#define ScancodeSender_h

#include "Arduino.h"

class ScancodeSender {
  private:
    int data_pin;
    int rdy_pin;
    int ack_pin;
    int word_pin;

    int rdy_val;
    int ack_val;
    int word_val;

    void send_bit(uint8_t c);
    void wait_for_ack();

  public:
    ScancodeSender(int datapin, int rdypin, int ackpin, int wordpin);
    
    void begin();
    void send(uint8_t c);
};

#endif
