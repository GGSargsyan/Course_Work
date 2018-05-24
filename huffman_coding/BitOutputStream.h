#include <iostream>

class BitOutputStream {
private:
  char buf; //one byte buffer of bits
  int nbits; //how many bits have been written to buf
  std::ostream & out; //reference to output stream to use

public:
  /**Initializes a BitOutPutStream that will use
   *the given ostream for output*/
  BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {
    //clear buf and bit counter
  }
  /**Send the buffer to the output and clear it */
  void flush();
  
  /**Write the least significant bit of the argument to
    *the bit buffer and increment the bit buffer index.
    *But flush the buffer first, if it is full*/
  void writeBit(int i);

  void padZero();
};
