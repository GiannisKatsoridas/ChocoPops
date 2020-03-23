#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

int getBalance(Node *node) {

    if (node == NULL)
        return 0;

    int rightBalance = getBalance(node->right);
    int leftBalance = getBalance(node->left);

    return rightBalance > leftBalance ? 1 + rightBalance : 1 + leftBalance;

}

Node *insert(Node *node, record *rec) {

    if (node == NULL) {

        node = malloc(sizeof(Node));
        node->left = NULL;
        node->right = NULL;
        node->key = rec;
        return node;

    }

    if (compareDates(rec->entryDate, node->key->entryDate) == 0)
        node->right = insert(node->right, rec);
    else
        node->left = insert(node->left, rec);


    int rightHeight = getBalance(node->right);
    int leftHeight = getBalance(node->left);
    if(rightHeight - leftHeight >= -1 && rightHeight - leftHeight <= 1)
        return node;

    if(leftHeight > rightHeight && compareDates(rec->entryDate, node->left->key->entryDate)==1)
        return leftLeft(node);
    else if(leftHeight > rightHeight && compareDates(rec->entryDate, node->left->key->entryDate)==0)
        return leftRight(node);
    else if(leftHeight < rightHeight && compareDates(rec->entryDate, node->right->key->entryDate)==1)
        return rightLeft(node);
    else
        return rightRight(node);
}

Node* leftLeft(Node* node){

    Node* head = node;
    Node* child = node->left;

    head->left = child->right;
    child->right = head;

    return child;
}

Node* rightRight(Node* node){

    Node* head = node;
    Node* child = node->right;

    head->right = child->left;
    child->left = head;

    return child;
}

Node* leftRight(Node* node){

//    Node* head = node;
//    Node* child = node->left;
//
//    head->left = child->right;
//    child->right = head->left->left;
//    head->left->left = child;

    node->left = rightRight(node->left);

    return leftLeft(node);
}

Node* rightLeft(Node* node){

//    Node* head = node;
//    Node* child = node->right;
//
//    head->right = child->left;
//    child->left = head->right->right;
//    head->right->right = child;

    node->right = leftLeft(node->right);

    return rightRight(node);
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

void deleteTree(Node *node) {

    if (node->left != NULL)
        deleteTree(node->left);

    if (node->right != NULL)
        deleteTree(node->right);

    free(node);
}

void deleteTreeAndRecords(Node *node) {

    if (node->left != NULL)
        deleteTreeAndRecords(node->left);

    if (node->right != NULL)
        deleteTreeAndRecords(node->right);


    free(node->key->recordID);
    free(node->key->patientFirstName);
    free(node->key->patientLastName);
    free(node->key->country);
    free(node->key->diseaseID);
    free(node->key->entryDate);
    free(node->key->exitDate);

    free(node->key);

    free(node);
}
