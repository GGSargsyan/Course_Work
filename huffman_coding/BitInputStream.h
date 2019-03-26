/**Austin Crinklaw
  *Grigor Sargsyan
  *BitInputStream.h*/
#include <iostream>

class BitInputStream {
private:
  char buf; //one byte buffer of bits
  int nbits; //number of bits that have been read from buf
  std::istream & in; //the input stream to use

public:
  /**Initialize a BitInputStream that will use
    *the given istream for input
    */
  BitInputStream(std::istream & is) : in(is){
    buf = 0; //clear buffer
    nbits = 8; //initializes bit index
  }

  /**Fill the buffer from the input*/
  void fill();

  /**Read the next bit from the bit buffer
    *Fill the buffer from the input stream first if needed
    *Return 1 if the bit read is 1
    *Return 0 if the bit read is 0
    */
  int readBit();
};
