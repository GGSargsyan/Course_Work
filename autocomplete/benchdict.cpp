#include "util.h"
#include<iostream>
#include<fstream>

/*Method declarations*/

/*Calculates the average time it takes to find a specified number of words
 *in a dictionary assembled using a BST back end.*/
void bstBench(int minSize, int stepSize, int iterations, std::string dictfile);

/*Calculates the average time it takes to find a specified number of words
 *in a dictionary assembled using a hash table back end.*/
void hashBench(int minSize, int stepSize, int iterations, std::string dictfile);

/*Calculates the average time it takes to find a specified number of words
 *in a dictionary assembled using a TST back end.*/
void trieBench(int minSize, int stepSize, int iterations, std::string dictfile);

/*Variables used throughout the code*/
std::vector<long long> timeVec;
long long timeTotal;
long long averageTime;
Timer stopWatch;

/*Main method, will take command line argument and call bench
 *marking functions*/
int main(int argc, char* argv[]){
  if(argc != 5){
    std::cout << "Wrong number of arguments" <<
    " proper usage is ./benchdict min_size step_size num_iterations dictfile"
    << std::endl;
    return -1;
  }

  //Method calls for each of the data structures being benchmarked
  bstBench(std::atoi(argv[1]), std::atoi(argv[2]), std::atoi(argv[3]), argv[4]);
  hashBench(std::atoi(argv[1]), std::atoi(argv[2]), std::atoi(argv[3]), argv[4]);
  trieBench(std::atoi(argv[1]), std::atoi(argv[2]), std::atoi(argv[3]), argv[4]);
}

/*Calculates the average time it takes to find a specified number of words
 *in a dictionary assembled using a BST back end.*/
void bstBench(int minSize, int stepSize, int iterations, std::string dictfile){
  //Open the file stream and dictionary file
  std::cout << "Benchmarking BST: " << std::endl;
  std::ifstream fin;
  fin.open(dictfile);
  std::vector<std::string> wordVec;

  //For loop for each iteration
  for(int i = 0; i < iterations; i++){
    //Reset the file stream and load the vector
    fin.clear();
    fin.seekg(0);
    Utils::load_vector(wordVec, fin, 100);
    //Create a new dictionary object from appropriate data structure
    DictionaryBST* myBST = new DictionaryBST();
    Utils::load_dict(*myBST, fin, (minSize+(i*stepSize)));

    //Start the timer
    stopWatch.begin_timer();
    //Iterate through the data structure using iterator
    for(auto it = wordVec.begin(); it != wordVec.end(); it++){
      myBST->find(*it);
    }
    //Push the value from end timer to time vector
    timeVec.push_back(stopWatch.end_timer());

    //Calculate the total time
    for(unsigned int j = 0; j < timeVec.size(); j++)
      timeTotal = timeTotal + timeVec[j];
    //Find the average and then print out statistics
    averageTime = (timeTotal / timeVec.size());
    std::cout << ((minSize)+(i*stepSize)) << "\t" << averageTime << std::endl;
    //Reset the vector and delete object on heap
    wordVec.clear();
    delete myBST;
  }
  //Reset the global variables used and close file stream
  timeVec.clear();
  averageTime = 0;
  timeTotal = 0;
  fin.close();
}

/*Calculates the average time it takes to find a specified number of words
 *in a dictionary assembled using a hash table back end.*/
void hashBench(int minSize, int stepSize, int iterations, std::string dictfile){
  //Open the file stream and load the dictionary file
  std::cout << "Benchmarking Hash Table: " << std::endl;
  std::ifstream fin;
  fin.open(dictfile);
  std::vector<std::string> wordVec;

  //For loop for the number of iterations
  for(int i = 0; i < iterations; i++){
    //Clear flags and reset the file stream pointer
    fin.clear();
    fin.seekg(0);
    //Load the vector and create a new dictionary object
    //for the appropriate data structure
    Utils::load_vector(wordVec, fin, 100);
    DictionaryHashtable* myHash = new DictionaryHashtable();
    Utils::load_dict(*myHash, fin, (minSize+(i*stepSize)));

    //Begin the timer for benchmarking
    stopWatch.begin_timer();
    //Iterate through and call find on data structure
    for(auto it = wordVec.begin(); it != wordVec.end(); it++){
      myHash->find(*it);
    }
    //Push the time onto the time vector
    timeVec.push_back(stopWatch.end_timer());

    //Calculate the total time from time vector
    for(unsigned int j = 0; j < timeVec.size(); j++)
      timeTotal = timeTotal + timeVec[j];

    //Calculate average time and print statistics
    averageTime = (timeTotal / timeVec.size());
    std::cout << ((minSize)+(i*stepSize)) << "\t" << averageTime << std::endl;

    //Clear the word vector and free heap memory
    wordVec.clear();
    delete myHash;
  }
  //Reset global variables for next benchmarking
  timeVec.clear();
  averageTime = 0;
  timeTotal = 0;
  fin.close();
}

/*Calculates the average time it takes to find a specified number of words
 *in a dictionary assembled using a TST back end.*/
void trieBench(int minSize, int stepSize, int iterations, std::string dictfile){
  //Open the file stream and load dictionary file into stream
  std::cout << "Benchmarking Trie: " << std::endl;
  std::ifstream fin;
  fin.open(dictfile);
  std::vector<std::string> wordVec;

  //For loop for the number of iterations
  for(int i = 0; i < iterations; i++){
    //Clear the flags and load the vector with words
    fin.clear();
    fin.seekg(0);
    Utils::load_vector(wordVec, fin, 100);
    //Create new dictionary object for appropriate data struct
    DictionaryTrie* myTrie = new DictionaryTrie();
    Utils::load_dict(*myTrie, fin, (minSize+(i*stepSize)));

    //Begin the timer
    stopWatch.begin_timer();

    //Iterate through the word vector and find in the data structure
    for(auto it = wordVec.begin(); it != wordVec.end(); it++){
      myTrie->find(*it);
    }
    //Push the time taken onto the time vector
    timeVec.push_back(stopWatch.end_timer());

    //this will caclulate the total time taken
    for(unsigned int j = 0; j < timeVec.size(); j++)
      timeTotal = timeTotal + timeVec[j];

    //Finds the average time and prints stats
    averageTime = (timeTotal / timeVec.size());
    std::cout << ((minSize)+(i*stepSize)) << "\t" << averageTime << std::endl;

    //Clear the word vector and free heap memory
    wordVec.clear();
    delete myTrie;
  }
  //Reset the global variables for next benchmarking
  timeVec.clear();
  averageTime = 0;
  timeTotal = 0;
  fin.close();
}
