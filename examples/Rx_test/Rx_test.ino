#include "manchester_rx.h"

byte payload[8];
Receiver RxD;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("started");
}

void loop() {

  //seeking for the start byte
  RxD.seek_start();
  Serial.println("start byte found");
  //read payload
  RxD.read_byte(payload);

 Serial.print("ascii value= ");Serial.println(RxD.array_to_ascii(payload));
 Serial.println("done");
}
