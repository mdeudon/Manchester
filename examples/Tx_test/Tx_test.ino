//the RF pin must be on 9

#include "manchester_tx.h"

char car;

Sender TxD;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()>0)
  {
    car=Serial.read();
    TxD.send_byte(car);
    Serial.print("sent "); Serial.println((byte)car);
  }
}
