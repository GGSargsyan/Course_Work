#include "util.h"
#include<iostream>
#include<fstream>
#include<array>

/*Method declarations*/

/*Takes a string and returns an integer based on the djb2
 * hashing function. The integer returned correlates to
 * what slot the word should be inserted into hashtable*/
unsigned int djb2Hash(std::string word, int tableSize);
/*Takes a string and returns an integer based on the sdbm
 * hashing function. The integer returned correlates to
 * what slot the word should be inserted into hashtable*/
unsigned int sdbmHash(std::string word, int tableSize);

/*Method implementations*/

/*Main method, will take in command line argument
 * (dictionary and number of words)
 * and return relevant statistics about the two hashing
 * functions used. The two hashing functions chosen were
 * djb2 and sdbm, relatively well known hashing functions.*/
int main(int argc,char* argv[]){
  //Checks to make sure the number of arguments passed is correct
  if(argc != 3){
    std::cout << "Incorrect number of arguments "
              << " proper usage is ./benchhash dictfile num_words" << std::endl;
    return -1;
  }

  //Here we are opening a file stream
  //and placing a file (of strings) into a vector
  unsigned int numberWords = std::atoi(argv[2]);
  std::vector<std::string> wordVec;
  std::ifstream fin;
  fin.open(argv[1]);
  //load_vector populates the vector with words from filestream
  Utils::load_vector(wordVec, fin, numberWords);
  fin.close();

  //Initialize our hashtable backing arrays to 2 * # words
  std::string hashTable1[2*numberWords];
  std::string hashTable2[2*numberWords];
  unsigned int hashHits1[2*numberWords];
  unsigned int hashHits2[2*numberWords];

  //Initialize every slot in hashHits to 0 for easier incrementing
  for(unsigned int i = 0; i < 2*numberWords; i++){
    hashHits1[i] = 0;
    hashHits2[i] = 0;
  }

  //Hash our string using djb2 hashing, record when a slot is filled
  //by incrementing our hashHits array at the same slot
  unsigned int hashVal;
  for(unsigned int i = 0; i < wordVec.size(); i++){
   hashVal = djb2Hash(wordVec[i], 2*numberWords);
   //now that we have hash value,
   //place into hashtable and increment counter array
   hashTable1[hashVal] = wordVec[i];
   hashHits1[hashVal]++;

   //repeat the process for sdbm hashing
   hashVal = sdbmHash(wordVec[i], 2*numberWords);
   hashTable2[hashVal] = wordVec[i];
   hashHits2[hashVal]++;
  }

  //Use this while loop to determine the max number of hits
  //Which will be the size necessary for its array
  //This will simplify our ability to count how many slots have each hit
  unsigned int cellCounter = 0;
  unsigned int maxHits1 = 0;
  while(cellCounter < 2*numberWords){
    if(maxHits1 < hashHits1[cellCounter])
      maxHits1 = hashHits1[cellCounter];
    cellCounter++;
  }

  cellCounter = 0;
  unsigned int maxHits2 = 0;
  while(cellCounter < 2*numberWords){
    if(maxHits2 < hashHits2[cellCounter])
      maxHits2 = hashHits2[cellCounter];
    cellCounter++;
  }

  //Initialize the maxHitsArray, which counts how many slots
  //have a specific # of collisions
  int maxHitsArray1[maxHits1];
  int maxHitsArray2[maxHits2];
  //Set each slot to 0 to simplify incrementing
  for(unsigned int i = 0; i < maxHits1; i++){
    maxHitsArray1[i] = 0;
  }
  for(unsigned int i = 0; i < maxHits2; i++){
    maxHitsArray2[i] = 0;
  }

  for(unsigned int i = 0; i < maxHits1; i++){
    //for counting the number of slot hits
    for(unsigned int j = 0; j < 2*numberWords; j++){
      if(hashHits1[j] == i)
        maxHitsArray1[i]++;
    }
  }

  for(unsigned int i = 0; i < maxHits2; i++){
    for(unsigned int j = 0; j < 2*numberWords; j++){
      if(hashHits2[j] == i)
        maxHitsArray2[i]++;
    }
  }

  //Prints out the values from maxHitsArray, which correlates
  //to the number of slots with specific # of collisions
  std::cout << "Printing stats for hash function 1 (djb2 hash)" << std::endl;
  std::cout << "#hits" << "\t" << "#slots" << std::endl;
  for(unsigned int i = 0; i < maxHits1; i++){
    std::cout << i << "\t" << maxHitsArray1[i] << std::endl;
  }
  long average1 = 0;
  for(unsigned int i = 0; i < maxHits1; i++){
    average1 += (maxHitsArray1[i]*i);
  }
  average1 = average1 / numberWords;
  std::cout << "Average: " << average1 << std::endl;
  std::cout << "Worst case: " << numberWords << std::endl;

  std::cout << "Printing stats for hash function 2 (sdbm hash)" << std::endl;
  std::cout << "#hits" << "\t" << "#slots" << std::endl;
  for(unsigned int i = 0; i < maxHits2; i++){
    std::cout << i << "\t" << maxHitsArray2[i] << std::endl;
  }
  long average2 = 0;
  for(unsigned int i = 0; i < maxHits2; i++){
    average2 += (maxHitsArray2[i]*i);
  }
  average2 = average2 / numberWords;
  std::cout << "Average: " << average2 << std::endl;
  std::cout << "Worst case: " << numberWords << std::endl;
}

/*Takes a string and returns an integer based on the djb2
 * hashing function. The integer returned correlates to
 * what slot the word should be inserted into hashtable
 *found via yorku's website on hashing*/
unsigned int djb2Hash(std::string word, int tableSize){
  unsigned int len = word.length();
  unsigned int hash = 5381;

  for(unsigned int i = 0; i < len; i++)
    hash = ((hash << 5) + hash) + (word[i]);

  return hash % tableSize;
}

/*Takes a string and returns an integer based on the sdbm
 * hashing function. The integer returned correlates to
 * what slot the word should be inserted into hashtable
 * found via yorkus website on hashing*/
unsigned int sdbmHash(std::string word, int tableSize){
  unsigned int hash = 0;
  unsigned int len = word.length();

  for(unsigned int i = 0; i < len; i++)
    hash = (word[i]) + (hash << 6) + (hash << 16) - hash;

  return hash % tableSize;
}
