/*Austin Crinklaw
 *Grigor Sargsyan
 *Provides bitwise reading for filestream*/
#include <iostream>
#include "BitInputStream.h"

/*Fills the buffer with a byte of data*/
void BitInputStream::fill(){
  buf = in.get();
  nbits = 0;
}

/*Reads the next bit from the buffer*/
int BitInputStream::readBit(){
  //If all the bits in the buffer are read, fill the buffer first
  if(nbits == 8)
    fill();

  //Gets the most significant bit from buffer
  int returnVal = ((buf >> (8 - (nbits + 1))) & 1);

  nbits++;

  return returnVal;
}
