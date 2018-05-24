/*Austin Crinklaw
 *HCNode.hpp
 *5-17-2017
 *Overloads the < operator in order to facilitate
 *easier logic for priority queue (return smallest nodes)
 *rather than the default return of largest*/

#include "HCNode.h"
/** Compare this HCNode and other for priority
 * ordering.
 * Smaller count means higher priority
 * Use node symbol for deterministic tiebreaking*/

bool HCNode::operator<(const HCNode& other) {
  //if counts are different, just compare counts
  if(count != other.count) return count > other.count;

  //counts are equal. use symbol value to break tie
  //for this to work, internal HCNodes must have symb
  //set
  return symbol < other.symbol;
};
