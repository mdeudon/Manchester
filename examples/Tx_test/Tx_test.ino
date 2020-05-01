#include "manchester_tx.h"

byte payload[8];

Sender TxD;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0)
  {
    TxD.ascii_to_array(Serial.read(),payload);
    TxD.send_byte(payload);
    Serial.println("sent");
  }
  TxD.ascii_to_array('s',payload);
  TxD.send_byte(payload);
  Serial.println("sent");
  delay(500);
}
