#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
  return hashDict.insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
  if(hashDict.find(word) != hashDict.end())
    return true;
  else return false;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
