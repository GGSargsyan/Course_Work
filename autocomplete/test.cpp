/*Grigor Sargsyan, Austin Crinklaw
 * PA2
 * 5-5-2017
 * test.cpp*/
#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;


int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("harrys");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  
  
  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }
  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  
/*You are supposed to add more test cases in this file */
DictionaryTrie agTrie;
//Test for empty string
if(agTrie.insert("basketball", 212) != true){
  cout << "Invalid insert value for basketball" << endl;
  return -1;
}
else
  cout << "Passed first test" << endl;

if(agTrie.insert("basketbal", 100) != true){
  cout << "Invalid insert value for basket" << endl;
  return -1;
}
if(agTrie.find("basketba") != false){
  cout << "Invalid find value for basketba" << endl;
  return -1;
}
if(agTrie.find("basketball") != true){
  cout << "Invalid find value for basketball" << endl;
  return -1;
}

if(agTrie.insert("basketball", 500) != false){
  cout << "Invalid insert value for basketball " << endl;
  return -1;
}

if(agTrie.insert("MRGLRGLRGLRGL", 143) != true){
  cout << "Invalid insert value for basketball " << endl;
  return -1;
} 
ifstream fin;
fin.open("freq_dict.txt");
Utils::load_dict(agTrie, fin);
fin.close();

ifstream fin;
fin.open("freq1.txt");
Utils::load_dict(agTrie, fin);
fin.close();

vector<string> testVec = agTrie.predictCompletions("zymogens", 4);
if(testVec.size() == 0){
  cout << "Error!" << endl;
  return -1;
}
for(unsigned int i = 0; i < testVec.size(); i++)
  cout << i << " object is " << testVec[i] << endl;


return 0;
}
