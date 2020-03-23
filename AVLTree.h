// An AVL tree node

#include <string.h>
#include "RecordsParsing.h"

// A utility function to get maximum of two integers

int max(int a, int b);


// A utility function to get the height of the tree

int height(Node* N);


/* Helper function that allocates a new node with the given key and

    NULL left and right pointers. */

Node* newNode(record* key);


// A utility function to right rotate subtree rooted with y

Node* rightRotate(Node* y);


// A utility function to left rotate subtree rooted with x

Node* leftRotate(Node* N);


// Get Balance factor of node N

int getBalance(Node* N);


// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.

Node* insert(Node* node, record* key);


// Function to search for a Record ID inside the tree.
// If no such tree is found, then NULL is returned.

Node* search(Node* node, char* recordID);