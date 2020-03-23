#include "AVLTree.h"

#include<stdio.h>
#include<stdlib.h>

////////////////////////////////////////////////////////////////////////////
//////////////////////////////// CODE FROM  ////////////////////////////////
/// /////////// AVL Tree _ Set 1 (Insertion) - GeeksforGeeks ///////////////
////////////////////////////////////////////////////////////////////////////


int height(Node *N)
{

    if (N == NULL)

        return 0;

    return N->height;
}


int max(int a, int b)
{

    return (a > b)? a : b;
}


Node* newNode(record* key)
{

    Node* node = (Node*)

            malloc(sizeof(Node));

    node->key = key;

    node->left = NULL;

    node->right = NULL;

    node->height = 1;  // new node is initially added at leaf

    return(node);
}


Node *rightRotate(Node *y)
{

    Node *x = y->left;

    Node *T2 = x->right;



    // Perform rotation

    x->right = y;

    y->left = T2;



    // Update heights

    y->height = max(height(y->left), height(y->right))+1;

    x->height = max(height(x->left), height(x->right))+1;



    // Return new root

    return x;
}


Node *leftRotate(Node *x)
{

    Node *y = x->right;

    Node *T2 = y->left;



    // Perform rotation

    y->left = x;

    x->right = T2;



    //  Update heights

    x->height = max(height(x->left), height(x->right))+1;

    y->height = max(height(y->left), height(y->right))+1;



    // Return new root

    return y;
}


int getBalance(Node *N)
{

    if (N == NULL)

        return 0;

    return height(N->left) - height(N->right);
}


Node* insert(Node* node, record* key)
{
    /* 1.  Perform the normal BST insertion */

    if (node == NULL)

        return(newNode(key));


    // Two records with equal dates create duplicates within the tree. As seen below, the duplicates go in the left child.

    if (compareDates(key->entryDate, node->key->entryDate)==1)

        node->left  = insert(node->left, key);

    else

        node->right = insert(node->right, key);




    /* 2. Update height of this ancestor node */

    node->height = 1 + max(height(node->left),

                           height(node->right));



    /* 3. Get the balance factor of this ancestor

          node to check whether this node became

          unbalanced */

    int balance = getBalance(node);



    // If this node becomes unbalanced, then

    // there are 4 cases



    // Left Left Case

    if (balance > 1 && compareDates(key->entryDate, node->left->key->entryDate)==1)

        return rightRotate(node);



    // Right Right Case

    if (balance < -1 && compareDates(key->entryDate, node->right->key->entryDate)==0)

        return leftRotate(node);



    // Left Right Case

    if (balance > 1 && compareDates(key->entryDate, node->left->key->entryDate)==0)

    {

        node->left =  leftRotate(node->left);

        return rightRotate(node);

    }



    // Right Left Case

    if (balance < -1 && compareDates(key->entryDate, node->right->key->entryDate)==1)

    {

        node->right = rightRotate(node->right);

        return leftRotate(node);

    }



    /* return the (unchanged) node pointer */

    return node;
}

Node *search(Node *node, char *recordID) {

    if(node == NULL)
        return NULL;

    if(strcmp(node->key->recordID, recordID)==0)
        return node;
    else{
        if(search(node->left, recordID) == NULL)
            return search(node->right, recordID);
        else
            return node;
    }
}

