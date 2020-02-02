#include "debug.h"
#include "PS2Keyboard.h"

// Pins for PS/2 Interface
static const int DATA_PIN = 36;  // was 3;
static const int CLOCK_PIN = 26; // was 2;

PS2Keyboard kbd(DATA_PIN, CLOCK_PIN);

void setup() {
    Serial.begin(115200);
    delay(5000);  // Wait a long time for esp32 to have Serial print statements work right.
    dprint("IBM Model M BLE Keyboard scancode capturer\n");
    dprint("------------------------------------------\n");

    kbd.begin();
}

void loop() {
   while(kbd.available()){
    uint8_t scancode = kbd.read();
    dprint8("Scancode", scancode);
  }
  dprint(".");
}
