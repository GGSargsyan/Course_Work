#include "BSTInt.h"

/* Function definitions for a int-based BST class */


/** Default destructor.
    Delete every node in this BST.
*/
BSTInt::~BSTInt() {
  deleteAll(root);
}

/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return  true if the item was added to this BST
 *  as a result of this call to insert,
 *  false if an item equal to this one was already in this BST.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  For the reasoning
 *  behind this, see the assignment writeup.
 */

bool BSTInt::insert(int item)
{
  //Check if BST is empty, if true make root
  if (!root) {
    root = new BSTNodeInt(item);
    ++isize;
    return true;
  }
  //Check to make sure item is not duplicate
  if(find(item))
    return false;

  BSTNodeInt* curr = root;
  //Traverse through tree to find proper place for insert
  while (curr->left || curr->right) {
    if (item < curr->data) {
      if(!curr->left) break;
      else
        curr = curr->left;
    }
    else if (curr->data < item) {
      if(!curr->right) break;
      else  
        curr = curr->right;
    }
    else {
      return false;
    }
  }

  // Ready to insert
  BSTNodeInt* newNode = new BSTNodeInt(item);
  if (item < curr->data) {
    curr->left = newNode;
    newNode->parent = curr;
  }
  else {
    curr->right = newNode;
    newNode->parent = curr;
  }

  ++isize;
  return true;

}


/** Find a Data item in the BST.
 *  Return true if the item is in the BST or false otherwise
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
bool BSTInt::find(int item) const
{
  BSTNodeInt* curr = root;
  //Start at root, traverse until null or find value
  while (curr) {
    if (curr->data < item) {
      curr = curr->right;
    }
    else if (item < curr->data) {
      curr = curr->left;
    }
    else {
      return true;
    }
  }
  return false;
}

  
/** Return the number of items currently in the BST.
 */
unsigned int BSTInt::size() const 
{
  return isize;
}

  
/** Return the height of the BST.
    Height of tree with just root node is 0
 */
int BSTInt::height() const
{
 return heightHelper(root);
}

/** Helper method used to recursively find height of the BST*/
int BSTInt::heightHelper(BSTNodeInt* n) const 
{
  if(n == NULL)
    return 0;

  if(!n->left && !n->right)
    return 0;
  //Recursive calls 1+ max of left subtree and right subtree height
  return 1 + std::max(heightHelper(n->left),heightHelper(n->right));
}


/** Return true if the BST is empty, else false. 
 */
bool BSTInt::empty() const 
{
 if(root != NULL)
  return false;

 else
  return true; 
}




/** do a postorder traversal, deleting nodes
 * This is a helper for the destructor
 * This method is static because it acts on BSTNodeInts
 *   and not on the BSTInt object directly.
 */
void BSTInt::deleteAll(BSTNodeInt* n)
{
  if(!n)
    return;
  
  if(n->left)
    deleteAll(n->left);

  if(n->right)
    deleteAll(n->right);

  delete(n);
}
