/*Austin Crinklaw
 *Grigor Sarsgsyan
 *BitOutputStream.cpp
 *Bitwise functions for filestream output*/
#include <iostream>
#include "BitOutputStream.h"

/*Flushes the buffer into output stream*/
void BitOutputStream::flush(){
  //Put the buffer into output stream
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

/*Writes a bit into the buffer*/
void BitOutputStream::writeBit(int i){
  //If buffer is full, flush
  if(nbits == 8)
    flush();

  //Write least significant bit to buffer
  buf = (buf << 1);
  i = (i & 1);
  buf = (buf | i);

  //Increment number of bits
  nbits++;

}

/*Pads the buffer with zeros if nbits != 8*/
void BitOutputStream::padZero(){
  buf = (buf << 8 - nbits);
}
