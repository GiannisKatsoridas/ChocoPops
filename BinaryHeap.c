#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryHeap.h"

// Create a simple heap node and return it
HeapNode *createHeap(char* name, int number) {

    HeapNode *node = malloc(sizeof(HeapNode));

    node->name = malloc((strlen(name)+1)*sizeof(char));
    strcpy(node->name, name);
    node->number = number;

    node->left = NULL;
    node->right = NULL;

    return node;
}

// The way the insert function works is it descends recursively the tree until it finds the position the new node
// must be entered at. Then enters the node and during the second part of the recursion makes the necessary swaps
// to ensure parent is always larger than children. Starts from the new node index (the position to be inserted if
// the heap was an array) and calculates the parent until the parent is the head of the tree. Then calculates whether
// the road is from the left or right child and performs the same function from the appropriate subtree, left or
// right.
HeapNode* insertToHeap(HeapNode* node, int cur, int goal, char* name, int number){

    if(node == NULL)
        return createHeap(name, number);

    int addedLeft;          // Flag to show whether the left child was altered or the right. 0 == left, 1 == right.

    if(goal == 2*cur + 1) {         // Goal node is the left child of the cur node. Add the new pair in the left child
        node->left = malloc(sizeof(HeapNode));
        node->left->name = malloc((strlen(name)+1)*sizeof(char));
        strcpy(node->left->name, name);
        node->left->number = number;
        node->left->left = NULL;
        node->left->right = NULL;
        addedLeft = 0;
    }
    else if(goal == 2*cur + 2){     // Goal node is the right child of the cur node. Add the new pair in the right child
        node->right = malloc(sizeof(HeapNode));
        node->right->name = malloc((strlen(name)+1)*sizeof(char));
        strcpy(node->right->name, name);
        node->right->number = number;
        node->right->left = NULL;
        node->right->right = NULL;
        addedLeft = 1;
    }
    else {

        int temp_goal = goal;

        while((temp_goal-1)/2 != cur)       // While the index of the temp_goal is not a child of the cur node
            temp_goal = (temp_goal-1)/2;    // make the temp_goal its parent

        if(temp_goal == 2*cur + 1) {        // if the temp_goal node is left child of the cur node
            node->left = insertToHeap(node->left, 2 * cur + 1, goal, name, number); // execute the same function with the left child as cur
            addedLeft = 0;
        } else {    // else execute the same function with the right child as the cur node
            node->right = insertToHeap(node->right, 2 * cur + 2, goal, name, number);
            addedLeft = 1;
        }
    }

    if(addedLeft == 0){     // if the new node is inserted in the left subtree then check the left subtree for violations of heap property

        if(node->left->number > node->number){

            HeapNode* left = node->left;
            HeapNode* right = node->right;
            node->left = left->left;
            node->right = left->right;
            left->left = node;
            left->right = right;

            return left;
        }

        return node;
    }
    else{       // else check the right tree

        if(node->right->number > node->number){

            HeapNode* left = node->left;
            HeapNode* right = node->right;
            node->left = right->left;
            node->right = right->right;
            right->right = node;
            right->left = left;

            return right;
        }

        return node;

    }
}

// Function to recursively force the heap property after a node has been popped. Start from the head of the heap
// and if any of the children have greater value than it, swap them and perform the same function in the recently
// swapped child.
HeapNode* heapify(HeapNode* node){

    if(node->right == NULL && node->left == NULL)   // Both children are NULL, no need to check anything
        return node;

    if(node->right == NULL){        // Right child is null, just check left child

        if(node->left->number > node->number){

            HeapNode* left = node->left;
            HeapNode* right = node->right;
            node->left = left->left;
            node->right = left->right;
            left->left = node;
            left->right = right;

            left->left = heapify(left->left);

            return left;

        }

        return node;        // No need to go further down as the heap is already correct.

    }

    if(node->left == NULL){     // Left child is null, just check right child

        if(node->right->number > node->number){

            HeapNode* left = node->left;
            HeapNode* right = node->right;
            node->left = right->left;
            node->right = right->right;
            right->right = node;
            right->left = left;

            right->right = heapify(right->right);

            return right;

        }

        return node;

    }

    if(node->right->number > node->left->number){       // No child is NULL so compare children and then compare with parent

        if(node->right->number > node->number){     // if Right > Left then check if Right > parent. If yes then swap.

            HeapNode* left = node->left;
            HeapNode* right = node->right;
            node->left = right->left;
            node->right = right->right;
            right->right = node;
            right->left = left;

            right->right = heapify(right->right);

            return right;

        }

        return node;

    }
    else{

        if(node->left->number > node->number){  // if Left > Right then check if Left > parent. If yes then swap.

            HeapNode* left = node->left;
            HeapNode* right = node->right;
            node->left = left->left;
            node->right = left->right;
            left->left = node;
            left->right = right;

            left->left = heapify(left->left);

            return left;

        }

        return node;
    }

}

// When popping the head of the heap, the last indexed item takes its place. Then heapify is called to ensure the heap property.
HeapNode* popFromHeap(HeapNode* node, int size){

    if(size == 1)
        return node;

    size--;

    HeapNode* ptr = node;

    int counter = 0;
    int temp_size = size;

    while(counter != (temp_size-1)/2) {     // Find the last indexed node (whose index is 'size')

        while ((temp_size - 1) / 2 != counter)
            temp_size = (temp_size - 1) / 2;

        if (counter * 2 + 1 == temp_size) {
            ptr = ptr->left;
            counter = counter * 2 + 1;
        } else {
            ptr = ptr->right;
            counter = counter * 2 + 2;
        }

        temp_size = size;
    }

    if(counter*2+1 == size) {       // if its the left child, then make the left child the head of the heap

        HeapNode* head = ptr->left;

        if(node->left != head)
            head->left = node->left;
        else
            head->left = NULL;
        head->right = node->right;
        ptr->left = NULL;

        head = heapify(head);       // Ensure the heap property

        return head;
    }
    else{                           // if its the right child, then make the right child the head of the heap

        HeapNode* head = ptr->right;

        head->left = node->left;
        if(node->right != head)
            head->right = node->right;
        else
            head->right = NULL;
        ptr->right = NULL;

        head = heapify(head);       // Ensure the heap property

        return head;
    }
}

// Helper function to print the heap.
void printHeap(HeapNode* node){

    if(node == NULL)
        return;

    printf("Node: %d\nLeft: %d\tRight: %d\n", node->number, node->left == NULL ? -1 : node->left->number, node->right == NULL ? -1 : node->right->number);

    printHeap(node->left);
    printHeap(node->right);

}

// Recursively delete the heap
void deleteHeap(HeapNode *h) {

    if(h->right != NULL)
        deleteHeap(h->right);

    if(h->left != NULL)
        deleteHeap(h->left);

    free(h->name);
    free(h);
}
