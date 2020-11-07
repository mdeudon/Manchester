/* A simple library to send a byte through the air using Manchester code */
/* M DEUDON, april 2020 */

#include "Arduino.h"

#define RF_PIN 9  //plug wireless module input pin
#define T 1000    //period in us i.e. transfer rate = 1kHz

class Sender
{
  public:
  Sender();
  void send_byte(byte car);
  private:
  void ascii_to_array(byte s,byte arr[]);
  void send_sync();
  void send_load(byte start[],boolean state);   
  const byte start[8]={0,1,1,0,0,1,0,1}; //the start byte
};
