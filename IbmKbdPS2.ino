#include "debug.h"
#include "PS2Keyboard.h"
#include "ScancodeSender.h"

// **********************************************************************
// THIS SKETCH IS MEANT FOR A SPARKFUN PRO MICRO 5v at 16 mhz
//
// It is the PS/2 decoding half of the problem. The Bluetooth sending part
// is in the IbmKbdBle sketch.
// **********************************************************************

// Pins for PS/2 Interface
static const int DATA_PIN = 3;
static const int CLOCK_PIN = 2;

// Pins for the ScancodeSender
static const int SS_DATA_PIN = 6;
static const int SEM_RDY_PIN = 7;
static const int SEM_ACK_PIN = 8;
static const int SEM_WORD_PIN = 9;

PS2Keyboard kbd(DATA_PIN, CLOCK_PIN);
ScancodeSender sender(SS_DATA_PIN, SEM_RDY_PIN, SEM_ACK_PIN, SEM_WORD_PIN);

void setup() {

#if DEBUG_ENABLE    
//  while (!Serial);  // required for Flora & Micro
//    delay(500);
#endif
delay(3000);

    Serial.begin(115200);
    dprint("IBM Model M BLE Keyboard scancode capturer\n");
    dprint("------------------------------------------\n");

    kbd.begin();
    sender.begin();
}

void loop() {
  while(kbd.available()){

    uint8_t scancode = kbd.read();
//    dprint8("Scancode", scancode);
    sender.send(scancode);
  }
}

