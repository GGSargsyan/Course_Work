#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>

class TrieNode {
public:
  TrieNode* left;
  TrieNode* right;
  TrieNode* mid;
  const char data;
  unsigned int freq;
  bool end;

  /*Default constructor*/
  TrieNode(char c);
};

class Trie {
public:
  /*Default constructor*/
  Trie() : root(0) { }
  /*Default destructor*/
  ~Trie();

  /*Inserts a frequency and word into trie*/
  bool insert(std::string word, unsigned int freq);

  /*Searches for a word in trie, returns pair of TrieNode ptr and bool*/
  std::pair<TrieNode*, bool> find(std::string word) const;

  TrieNode* root;

  void prefixBFS(TrieNode* curr, std::string prefix, std::vector<std::pair<TrieNode*, std::string>> &pairVec);

  /*Helper method to recursively delete nodes*/
  static void deleteAll(TrieNode* t);

  /*Structure for priority queue comparator*/
  struct comp_pair;
};


/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:
  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
  // Add your own data members and methods here
  Trie* trieDict;
};

#endif // DICTIONARY_TRIE_H
