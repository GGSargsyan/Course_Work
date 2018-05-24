#include "BSTInt.h"
#include "BST.hpp"
#include "BSTIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

/**
 * A test driver for the BST int class and class template.
 * PA1 CSE 100 2017
 * Author: Christine Alvarado, Grigor Sargsyan, Austin Crinklaw
 */
int main() {
    //Testing rather large tree
    /* Create an STL vector of some ints */
    /*test*/
    vector<int> v;
    v.push_back(3);
    v.push_back(4);
    v.push_back(1);
    v.push_back(100);
    v.push_back(-33);
    v.push_back(-44);
    v.push_back(500);
    v.push_back(3153);
    v.push_back(-3153);

    /* Create an instance of BST holding int */
    BSTInt b;

    // Could use: for(auto item : v) { instead of the line below
    for(int item : v) {
        bool pr = b.insert(item);
        if(! pr ) {
            cout << "Incorrect bool return value when inserting " << item 
                 << endl;
         return -1;  
        }
    }
    /*Test duplicate*/
    if(b.insert(500) != false){
      cout << "Incorrect bool return value when inserting duplicate" << endl;
      return -1;
    }

    /* Test size. */
    cout << "Size is: " << b.size() << endl;
    if(b.size() != v.size()) {
        cout << "... which is incorrect." << endl;
        return -1;
    }

    /* Test find return value. */
    // Test the items that are already in the tree
    for(int item : v) {
        if(!b.find(item)) {
            cout << "Incorrect return value when finding " << item << endl;
            return -1;
        }
    }
    //Checking insert and find for already built tree
    b.insert(-22);
    if(!b.find(-22)) {
       cout << "Incorrect return value when finding -22" << endl;
       return -1;
    }
    //Checking proper height for BST
    if(b.height() != 4) { 
      cout << "Incorrect height for BST, was " << b.height() << " should be 4" <<  endl;
      return -1;
    }



    //Here is the BST with only root (one node)
    BSTInt c;
    c.insert(123);

    if(c.height() != 0){
       cout << "Incorrect height for root BST, was " << c.height() << " should be 0" << endl;
       return -1;
    }
    
    if(c.empty() != false){
      cout << "Incorrect bool value for root BST" << endl;
      return -1;
    }
    
    c.insert(1);
    c.insert(200);
    
    if(!c.find(1) || !c.find(200) || !c.find(123))
    {
       cout << "Incorrect find values for nodes that were added" << endl;
       return -1;
    }
    
    if(c.find(16)){
        cout << "Found value that DNE in current BST" << endl;
        return -1;
    }
    
    if(c.size() != 3){
       cout << "Incorrect size post insert" << endl;
       return -1;
    }
    
    //Here is the empty BST
    BSTInt empty;
    if(empty.height() != 0){
       cout << "Incorrect height for empty BST, was " << empty.height() << " should be 0" << endl;
       return -1;
    }
   
    if(!empty.empty()) {
       cout << "Incorrect bool value for empty BST" << endl;
       return -1;
    }
    
    empty.insert(1);
    if(!empty.find(1)){
      cout << "Incorrect find value for 1" << endl;
      return -1;
    }
     
    if(empty.empty()){
      cout << "Incorrect bool value for BST, empty should contain 1 after insert" << endl;
      return -1;
    }

   
    /* UNCOMMENT THE LINES BELOW TO TEST THE TEMPLATE-BASED ITERATOR */

    // Test the template version of the BST  with ints 
    BST<int> btemp;
    for (int item : v) {
        // The auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST...";
        auto p = btemp.insert(item);
        if (*(p.first) != item) {
            cout << "Wrong iterator returned.  "
                 << "Expected " << item << " but got " << *(p.first) << endl;
            return -1;
        }
        if (!p.second) {
            cout << "Wrong boolean returned.  Expected true but got " 
                 << p.second << endl;
            return -1;
        }
        cout << "success!" << endl;
              
    }
    //Testing for item not in BST
    auto q = btemp.find(777);
    if(q != nullptr){
      cout << "Wrong iterator found "
           << "Expected NULLPTR but got something else" << endl;
      return -1;
    } 
    // Now test finding the elements we just put in
    for (int item: v) {
        cout << "Finding " << item << "...." << endl;
        BSTIterator<int> foundIt = btemp.find(item);
        if (*(foundIt) != item) {
            cout << "incorrect value returned.  Expected iterator pointing to "
                 << item << " but found iterator pointing to " << *(foundIt) 
                 << endl;
            return -1;
        }
        cout << "success!" << endl;
    }



    // Test the iterator: The iterator should give an in-order traversal
  
    // Sort the vector, to compare with inorder iteration on the BST
    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    auto vit = v.begin();
    auto ven = v.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    auto en = btemp.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    auto it = btemp.begin();
    for(; vit != ven; ++vit) {
        if(! (it != en) ) {
            cout << *it << "," << *vit 
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *it << endl;
        if(*it != *vit) {
            cout << *it << "," << *vit 
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++it;
    }

    cout << "success!" << endl;


    cout << "All tests passed!" << endl;
    return 0;
}
