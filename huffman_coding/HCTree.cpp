/*Austin Crinklaw
 *Grigor Sargsyan
 *HCTree.cpp
 *5-17-2017
 *Creates a huffman coding tree from a vector of
 *frequencies, also performs encoding and decoding
 *based on said tree*/

#include "HCTree.h"
#include <stack>
#include <fstream>
#include <iostream>

/*Recursive method to delete heap memory
 *iterates through the tree and deletes nodes*/
void HCTree::deleteAll(HCNode* t){
  if(t == NULL)
    return;

  //Recursive children calls
  deleteAll(t->c0);
  deleteAll(t->c1);
  delete(t);
}

/*Default destructor*/
HCTree::~HCTree(){
  deleteAll(root);
}

/*Builds a huffman tree using a vector of
 *integers (frequencies of nodes)*/
void HCTree::build(const vector<int>& freqs){
  std::priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pQueue;

  //Iterates through frequencies and creates new nodes based on values
  for(unsigned int i = 0; i < freqs.size(); i++){
    if(freqs[i] > 0){
      leaves[i] = new HCNode(freqs[i], i);
      pQueue.push(leaves[i]);
    }

  }
  //Edge case when we have only one unique char
  if(pQueue.size() == 1){
    root = pQueue.top();
    pQueue.pop();
    return;
  }

  while(pQueue.size() > 1){
    HCNode* dummy = new HCNode(0,0);

    //Set the c0 child as smallest node from pQueue, establish relationship
    dummy->c0 = pQueue.top();
    dummy->c0->p = dummy;
    pQueue.pop();

    //Set the c1 child as the next smallest node, establish relationship
    dummy->c1 = pQueue.top();
    dummy->c1->p = dummy;
    pQueue.pop();

    dummy->count = (dummy->c0->count + dummy->c1->count);

    //Symbol is arbitratily chosen as the c0 symbol
    dummy->symbol = dummy->c0->symbol;
    pQueue.push(dummy);
  }

  root = pQueue.top();
}

/*Writes out encoding for huffman tree*/
void HCTree::encode(byte symbol, BitOutputStream& out) const{
  //Find the leaf containing symbol
  HCNode* node = leaves[symbol];
  std::stack<int> bitStack;


  while(node->p){
    if(node == node->p->c0)
      bitStack.push(0);

    else if(node == node->p->c1)
      bitStack.push(1);

    node = node->p;
  }


  //Write the bits from the stack
  while(!bitStack.empty()){
    out.writeBit(bitStack.top());
    bitStack.pop();
  }
}

/*Takes huffman encoding data and decodes it*/
int HCTree::decode(BitInputStream& in) const{
  HCNode* node = root;
  int bit;

  //Start at root and follow path from encoding pattern
  while(node->c0 || node->c1){
    bit = in.readBit();

    if(bit == 0)
      node = node->c0;
    else if(bit == 1)
      node = node->c1;
  }

  return node->symbol;
}
