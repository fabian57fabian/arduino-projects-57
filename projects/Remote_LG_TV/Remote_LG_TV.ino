/*  Infrared Remote Controller for LG TV's
 *  Created by Fabian Greavu (github: fabian57fabian)
 *  For Arduino nano and uno.
 *  Copy right Fabian Greavu
 *  see [insert link] for more info
*/
#include <IRremote.h>
const unsigned long LG_POWER = 0x20DF10EF;
const unsigned long LG_VOLUP = 0x20DF40BF;
const unsigned long LG_VOLDOWN = 0x20DFC03F;
const unsigned long LG_OK = 0x20DF22DD;
const unsigned long LG_INPUT = 0x20DFD02F;
const unsigned long LG_UP = 0x20DF02FD;
const unsigned long LG_DOWN = 0x20DF827D;


IRsend irsend;
int btn_POWER = 7;
int btn_VOLUP = 6;
int btn_VOLDOWN = 5;
int btn_INPUT =8;
int btn_CHUP = 2;
int btn_CHDOWN = 4;
void setup() {
  Serial.begin(9600);
  pinMode(btn_POWER, INPUT);
  pinMode(btn_VOLUP, INPUT);
  pinMode(btn_VOLDOWN, INPUT);
  pinMode(btn_INPUT, INPUT);
  pinMode(btn_CHUP, INPUT);
  pinMode(btn_CHDOWN, INPUT);
}

void loop() {
  if (digitalRead(btn_POWER) == HIGH) {
    irsend.sendNEC(LG_POWER, 32);
  }
  if (digitalRead(btn_VOLUP) == HIGH) {
    irsend.sendNEC(LG_VOLUP, 32);
  }
  if (digitalRead(btn_VOLDOWN) == HIGH) {
    irsend.sendNEC(LG_VOLDOWN, 32);
  }
  if (digitalRead(btn_INPUT) == HIGH) {
    irsend.sendNEC(LG_INPUT, 32);
  }
  if (digitalRead(btn_CHUP) == HIGH) {
    irsend.sendNEC(LG_UP, 32);
  }
  if (digitalRead(btn_INPUT) == HIGH) {
    irsend.sendNEC(LG_DOWN, 32);
  }
  delay(50);
}
