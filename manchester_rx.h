/* A simple library to receive a byte through the air coded with Manchester code */
/* M DEUDON, april 2020 */

#include "Arduino.h"

#define RF_PIN 11
#define T 1000 //period in micro seconds
#define D 200 //tolerance in micro seconds

class Receiver
{
  public:
  Receiver();
  void seek_start();
  void read_byte(byte load[]);
  byte array_to_ascii(byte arr[]);
  private:
  const byte start[8]={0,1,1,0,0,1,0,1}; //start byte
  byte read_signal();
};
