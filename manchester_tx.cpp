#include "manchester_tx.h"

Sender::Sender()
{
  pinMode(RF_PIN,OUTPUT);
  digitalWrite(RF_PIN,LOW);
}

void Sender::send_sync()
/*send 32 HIGH LOW edges to synchronize with the receptor*/
{
  //sending a sync signal
  for (byte i=0;i<32;i++)
  {
    digitalWrite(RF_PIN,HIGH);
    delayMicroseconds(T);
    digitalWrite(RF_PIN,LOW);
    delayMicroseconds(T);
  }
  digitalWrite(RF_PIN,HIGH);
}

void Sender::send_load(byte start[],boolean state)
//send a byte but without sync
//start must be an array of 8 bytes, no more no less !
//state is the current state of the ouput line
{
      for (byte i=0;i<8;i++)
  {
    if (start[i]==1)
    {
        if (state==LOW)
        {
          delayMicroseconds(T);
          digitalWrite(RF_PIN,HIGH);
          state=HIGH;
        }
        else //state==HIGH
        {
          delayMicroseconds(T/2);
          digitalWrite(RF_PIN,LOW);
          delayMicroseconds(T/2);
          digitalWrite(RF_PIN,HIGH);
        }
      }
    else //start[i]==0
    {
        if (state==LOW)
        {
          delayMicroseconds(T/2);
          digitalWrite(RF_PIN,HIGH);
          delayMicroseconds(T/2);
          digitalWrite(RF_PIN,LOW);
        }
        else //state==HIGH
        {
          delayMicroseconds(T);
          digitalWrite(RF_PIN,LOW);
          state=LOW;
        }
    }
  }
}

void Sender::send_byte(byte car)
//send a sync signal + a start byte + load
//load is an array of 8 bit, no more no less !!
{
  boolean state; //state of the line
  byte load[8];

  this->ascii_to_array(car,load); //change ascii code to bits array
  
  send_sync();
  state = HIGH; //line must be high after sync
  
  //send the start message
  send_load(start,state);
  //send the payload
  send_load(load,state);
  return;
}

void Sender::ascii_to_array(byte s,byte arr[])
//utility to convert a character to an equivalent array of bits
{
    byte mask = 0b00000001;
  for (int i=0;i<8;i++)
  {
    arr[i] = s & mask;
    arr[i]=arr[i]>>i;
    mask = mask<<1;
  }
}
