#include "manchester_rx.h"

Receiver::Receiver()
{
    pinMode(RF_PIN,INPUT);  
}

void Receiver::read_byte(byte load[])
{
  for (int i=0;i<8;i++)
  {
  load[i]=read_signal();
  }
}

void Receiver::seek_start()
/*seek for the start signal*/
/*this is a blocking funtion*/
{
  int i=0;
  do
  { 
    if (read_signal()==start[i]) {i++;}
    else i=0;
  }
  while (i<8);
  return;  
}

byte Receiver::read_signal()
/*detect an edge in the signal and determine if it is a synchrone rising/falling edge*/
/*return the corresponding bit*/
/*this is a blocking function*/
{
  boolean state = digitalRead(RF_PIN);
  long start=micros();
  long delta; 
  long time_out = T+D; //if we do not detect 2 valids edges in this interval someting's wrong
  
  do
  {  
      do
      {
        //looking for a next edge
        //analyse the period to check if it can be a sync bit
        delta = micros()-start;
      }
      while ( (state==digitalRead(RF_PIN))); //  && delta<time_out );
      if (delta>=time_out) 
      {
        //something's wrong
        return 3;
      }   
      else
      {
        state=!state; //it is not a time out so the state of the ligne has changed
      }
      if ( (delta<=T+D) && (delta>=T-D) ) 
      {
      return (byte)state;
      }
      else
      {
        //it is not a sync edge
        //could be a transiant edge at T/2 or a noise
        //we do nothing
        //if the next edge is not sync the function will throw a time out
      }
      //let restart it for the next edge
  }
  while (true);
}

byte Receiver::array_to_ascii(byte arr[])
/*utility to convert an array of 8 bits to ascii code*/
{
  byte ascii=0;
  for (int i=7;i>=0;i--)
  {
    ascii = ascii << 1;
    ascii = arr[i] | ascii; 
  }
  return ascii;
}
