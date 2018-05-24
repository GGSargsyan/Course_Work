/*Austin Crinklaw
 *compress.cpp
 *Compresses a file using huffman encoding*/
#include "HCTree.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char*argv[]){

  //Check if the number of arguments is valid
  if(argc != 3){
    cout << "Invalid number of arguments, proper usage is : "
              << "./compress infile outfile" << endl;
    return -1;
  }


  //Declarations of variables used (256 for ASCII values)
  vector<int> freqs = vector<int>(256, 0);
  HCTree huffTree;


  //Open the input stream from command line args
  ifstream input;
  input.open(argv[1], ios::binary);


  //This checks if the file is empty
  if(input.peek() == EOF){
    cout << "File is empty, please use nonempty file" << endl;
    return -1;
  }

  byte buffer;
  int slot;

  //Gets the input chars and create freq vector
  while(input.peek() != EOF){
    buffer = input.get();
    slot = (int)buffer;
    freqs[slot]++;
  }
  input.close();

  huffTree.build(freqs);

  ofstream output;
  output.open(argv[2], ios::binary);
  BitOutputStream bitOutput = BitOutputStream(output);

  //Writing raw data
  for(unsigned int i = 0; i < freqs.size(); i++){
    output.write((char*)&freqs.at(i), sizeof(freqs.at(i)));
  }

  //Prints the  to the output file
  input.open(argv[1]);
  while(input.peek() != EOF){
    unsigned char c = input.get();
    buffer = (byte) c;
    huffTree.encode(buffer, bitOutput);
  }
  bitOutput.padZero();
  bitOutput.flush();

  input.close();
  output.close();

  return 0;
}
