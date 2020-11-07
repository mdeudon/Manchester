//The receive pin must be 11

#include "manchester_rx.h"

byte payload[8];
Receiver RxD;

void setup() {
  Serial.begin(9600);
  Serial.println("started");
}

void loop() {
  //seeking for the start byte
  //this is a blocking function
  RxD.seek_start();
  Serial.println("start byte found");
  //read payload
  //payload is an array containing all the bits of the received byte
  RxD.read_byte(payload);

 Serial.print("ascii value= ");Serial.println(RxD.array_to_ascii(payload));
 Serial.println("done");
}