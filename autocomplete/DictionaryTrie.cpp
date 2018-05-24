#include "util.h"
#include "DictionaryTrie.h"
#include <queue>
/*Default constructor for the Trie Node object*/
TrieNode::TrieNode(char c) : data(c) {
  left = right = mid = NULL;
  end = false;
  freq = 0;
}
/*Default destructor for trie, calls helper method*/
Trie::~Trie() {
  deleteAll(root);
}
/*Helper method to recurisvely delete nodes in trie*/
void Trie::deleteAll(TrieNode* t) {
  if(!t)
    return;
  //traverse left subtree
  if(t->left)
    deleteAll(t->left);
  //traverse middle subtree
  if(t->mid)
    deleteAll(t->mid);
  //traverse right subtree
  if(t->right)
    deleteAll(t->right);
  //delete current node
  delete(t);
}

/*overloaded method to compare the frequencies of two nodes
 * this will allow us to utilize a priority queue in order
 * to find which is the highest priority word for autocomplete*/
struct Trie::comp_pair{
  bool operator()(const std::pair<TrieNode*,std::string> pair1,
    const std::pair<TrieNode*,std::string> pair2) const{
    //Compare the two nodes frequencies
    return pair1.first->freq < pair2.first->freq;
  }
};

/*Inserts a word node by node into the current trie
 * If it already exists, we update frequency if greater
 * If not we return false*/
bool Trie::insert(std::string word, unsigned int freq) {
  TrieNode* curr;
  //If we insert a string of length 0 return false
  if(word.length() == 0)
    return false;

  //If we find the word, update frequency if greater, false if otherwise
  std::pair<TrieNode*, bool> findPair = find(word);
  if(findPair.second == true){
   if(findPair.first->freq < freq){
      findPair.first->freq = freq;
      return false;
    }
    return false;
  }

  //If root does not exist, we create root
  if(!root){
    root = new TrieNode(word[0]);
    curr = root;
    if(word.length()-1 == 0){
      curr->end = true;
      curr->freq = freq;
    }
    //Iterate through and add middle nodes until word terminates
    for(unsigned int i = 1; i < word.length(); i++){
      curr->mid = new TrieNode(word[i]);
      curr = curr->mid;
      //If we are at last char, update freq and end flag
      if(i == word.length()-1){
        curr->end = true;
        curr->freq = freq;
      }
    }
    return true;
  }

  //Start at the root
  curr = root;
  unsigned int i = 0;
  while(i < word.length()){
    //Check if our word is current node
    if(word[i] == curr->data){
      //If we have middle child and are not at the end of word
      //iterate to next middle and increment i
      if(curr->mid && i < word.length()-1){
        curr = curr->mid;
        i++;
      }
      //If those conditions aren't met, check if we
      //are at the end of the word, if we are update
      //boolean flag and frequency + return true
      else{
       if(i == word.length()-1){
          curr->freq = freq;
          curr->end = true;
          return true;
        }
        //Otherwise, we add a new node and iterate to this new node
        curr->mid = new TrieNode(word[i+1]);
        curr = curr->mid;
        i++;
      }
    }
    //Case where we need to traverse left subtree (char < current data)
    else if(word[i] < curr->data){
      //Traverse if we can
      if(curr->left)
        curr = curr->left;
      //Otherwise, insert new left node and iterate to this new node
      else{
        curr->left = new TrieNode(word[i]);
        curr = curr->left;
      }
    }
    //Final case, need to traverse right subtree (char > current data)
    else{
      //Traverse if we can
      if(curr->right)
        curr = curr->right;
      //Otherwise, insert new right node and iterate to this new node
      else{
        curr->right = new TrieNode(word[i]);
        curr = curr->right;
      }
    }
  }
//Emergency return statement, call 911
return false;
}

/*This will search for the word existing in the current trie
 * It returns a pointer to the node and a boolean value
 * the boolean value is true if found, false if not
 * We return a pointer to node in order to manipulate values
 * such as in the case where frequency is changed*/
std::pair<TrieNode*, bool> Trie::find(std::string word) const {
  TrieNode* curr = root;
  //If we have no root, we have no tree, return false
  if(!root)
    return std::pair<TrieNode*, bool>(NULL,false);

  unsigned int i = 0;
  //Execute following code while we still have chars to check
  while(i < word.length()){
    //If we have a data match execute this block
    if(word[i] == curr->data){
      //Check if we have mid child and if we are not at end of word
      if(curr->mid && i < word.length()-1){
        //Traverse to middle child and increment i
        curr = curr->mid;
        i++;
      }
      else{
        //We have no node to traverse, but are at end of word
        //so we return NULL ptr and false boolean (word not in trie)
        if(i < word.length()-1)
          return std::pair<TrieNode*, bool>(NULL, false);
        //Return current node and its boolean flag
        return std::pair<TrieNode*, bool>(curr, curr->end);
      }
    }
    //Case where char < current data, traverse the left subtree
    else if(word[i] < curr->data){
      //If we have left child, traverse left
      if(curr->left)
        curr = curr->left;
      else{
        //We have no node to traverse, but are at the end of word
        //return Null ptr and false boolean (word is not in trie)
        if(i < word.length()-1)
          return std::pair<TrieNode*, bool>(NULL, false);
        //return current node and its boolean flag
        return std::pair<TrieNode*, bool>(curr, false);
      }
    }
    //Final case, char > current data, traverse right subtree
    else{
      //If we have right child, traverse right
      if(curr->right)
        curr = curr->right;
      else{
        //We have no node to traverse, and we are at end of the word
        //return NULL ptr and false boolean (word is not in trie)
        if(i < word.length()-1)
          return std::pair<TrieNode*, bool>(NULL, false);
        //return current node and its boolean flag
        return std::pair<TrieNode*, bool>(curr, false);
      }
    }
  }
//fail safe return value
return std::pair<TrieNode*, bool>(NULL,false);
}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
  trieDict = new Trie();
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  //Acts as a wrapper for the trieDict function insert
  return trieDict->insert(word, freq);
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  //Acts as a wrapper for the trieDict function find
  return trieDict->find(word).second;
}

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
std::vector<std::string> DictionaryTrie::predictCompletions
  (std::string prefix, unsigned int num_completions)
{
  //Declarations of members that will be used, word and pair vectors
  std::vector<std::string> words;

  std::vector<std::pair<TrieNode*, std::string>> pairVec;

  //This will create a pair that is equal to the return of find function
  //called for the prefix (creates a boolean node correlation)
  std::pair<TrieNode*, bool> thisPair = trieDict->find(prefix);

  //Declaration of priority queue of pairs (node pointer, word)
  std::priority_queue<std::pair<TrieNode*, std::string>,std::vector
    <std::pair<TrieNode*, std::string>>,Trie::comp_pair> pq;


  /*This block of code is to check for various errors, including empty strings,
   *prefix not being found in the trie, or 0 number of completions requested
   *at this point, words is an empty vector, so we will return words*/
  //Empty string cannot be searched for, bad input
  if(prefix == ""){
    std::cout << "Invalid input. Please retry with correct input" << std::endl;
    return words;
  }
  //If the node returned is null we do not have the prefix in our trie
  if(thisPair.first == NULL){
    std::cout << "Invalid input. Please retry with correct input" << std::endl;
    return words;
  }
  //Wrong input (trivial) we cannot predict 0 completions
  if(num_completions == 0){
    std::cout << "Invalid input. Please retry with correct input" << std::endl;
    return words;
  }

  //If prefix pair has true boolean value, push the prefix onto priority queue
  if(thisPair.second){
    pq.push(std::make_pair(thisPair.first, prefix));
  }

  //Call recursive function for the middle child of last char in prefix
  trieDict->prefixBFS(thisPair.first->mid, prefix, pairVec);


  for(unsigned int i = 0; i < pairVec.size(); i++){
    pq.push(pairVec[i]);
  }

  //Pops the first num_completions items from the priority queue
  //which will be the highest frequency suggestions for autocomplete
  std::pair<TrieNode*, std::string> pqPair;
  for(unsigned int i = 0; i < num_completions; i++){
    //Check if the pq is empty, break if so
    if(pq.empty())
      break;
    //Push the popped value onto word vector
    pqPair = pq.top();
    std::cout << "WORD: " << pqPair.second << " FREQ: " << pqPair.first->freq << std::endl;
    pq.pop();
    words.push_back(pqPair.second);
  }

  return words;
}

/*This is a recursive function that will check if we have words in our trie structure*/
void Trie::prefixBFS(TrieNode* curr, std::string prefix,
  std::vector<std::pair<TrieNode*, std::string>> &pairVec){

  //Base case, if we don't have a current node, return
  if(curr == NULL)
    return;

  //Traverse down the left subtree
  prefixBFS(curr->left, prefix, pairVec);
  //Traverse down the right subtree
  prefixBFS(curr->right, prefix, pairVec);

  //if current node is the end of a word, push onto Priority Queue
  if(curr->end)
    //We push the prefix and currentdata to pair vector
    pairVec.push_back(std::make_pair(curr, prefix + curr->data));

  //Recurse middle, note prefix + curr->data
  //prefix + curr data will allow us to build the word and logically progress
  prefixBFS(curr->mid, prefix + curr->data, pairVec);

}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  delete(trieDict);
}
