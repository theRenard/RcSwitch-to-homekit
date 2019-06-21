/*

  Example for sending code from Arduino to Chacon & Zap power outlet

  | Transmitter | Arduino   | Wemos D1
  |-------------|-----------|----------
  | VCC         | 5V        | 5V
  | GND         | GND       | GND
  | DATA        | D10       | D1

*/

#include <RCSwitch.h>
#include "output.h"
RCSwitch sender = RCSwitch();
RCSwitch receiver = RCSwitch();

int sleep = 1000;
int transmit_pin = D1;
int receiver_pin = D3;
int pulseLength = 185;
int repeatTransmit = 5;

const char* ON[] = {
  "0FF00FFF0101",
  "0FF00FFF1001",
  "0FF00FF10001",
  "0FF00F1F0001",
  "0FF001FF0001"
};

const char* OFF[] = {
  "0FF00FFF0110",
  "0FF00FFF1010",
  "0FF00FF10010",
  "0FF00F1F0010",
  "0FF001FF0010"
};

void setup() {

  Serial.begin(115200);
  sender.enableTransmit(transmit_pin);
  sender.setPulseLength(pulseLength);
  sender.setRepeatTransmit(repeatTransmit);

  receiver.enableReceive(receiver_pin);
  receiver.setPulseLength(pulseLength);
  receiver.setRepeatTransmit(repeatTransmit);

}

void loop() {

  //-- Zap power outlet --

  // //ON 1
  // sender.sendTriState(ON[0]); Serial.println("Zap #1: ON"); delay(sleep);
  // //ON 2
  // sender.sendTriState(ON[1]); Serial.println("Zap #2: ON"); delay(sleep);
  // //ON 3
  // sender.sendTriState(ON[2]); Serial.println("Zap #3: ON"); delay(sleep);
  // //ON 4
  // sender.sendTriState(ON[3]); Serial.println("Zap #4: ON"); delay(sleep);
  // //ON 5
  // sender.sendTriState(ON[4]); Serial.println("Zap #4: ON"); delay(sleep);

  // //OFF 1
  // sender.sendTriState(OFF[0]); Serial.println("Zap #1: OFF"); delay(sleep);
  // //OFF 2
  // sender.sendTriState(OFF[1]); Serial.println("Zap #2: OFF"); delay(sleep);
  // //OFF 3
  // sender.sendTriState(OFF[2]); Serial.println("Zap #3: OFF"); delay(sleep);
  // //OFF 4
  // sender.sendTriState(OFF[3]); Serial.println("Zap #4: OFF"); delay(sleep);
  // //OFF 5
  // sender.sendTriState(OFF[4]); Serial.println("Zap #4: OFF"); delay(sleep);

  if (receiver.available()) {

    for (size_t i = 0; i < 4; i++) {
      bool test = testTristate(receiver.getReceivedValue(), receiver.getReceivedBitlength(), ON[i]);
      Serial.print(i);
      Serial.print(test);
    }

    for (size_t i = 0; i < 4; i++) {
      bool test = testTristate(receiver.getReceivedValue(), receiver.getReceivedBitlength(), OFF[i]);
      Serial.print(i);
      Serial.print(test);
    }

    receiver.resetAvailable();

  }
}
