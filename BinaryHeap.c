#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryHeap.h"

HeapNode *createHeap(char* name, int number) {

    HeapNode *node = malloc(sizeof(HeapNode));

    node->name = malloc((strlen(name)+1)*sizeof(char));
    strcpy(node->name, name);
    node->number = number;

    node->left = NULL;
    node->right = NULL;

    return node;
}


HeapNode* insertToHeap(HeapNode* node, int cur, int goal, char* name, int number){

    if(node == NULL)
        return createHeap(name, number);

    int addedLeft;          // Flag to show whether the left child was altered or the right. 0 == left, 1 == right.

    if(goal == 2*cur + 1) {
        node->left = malloc(sizeof(HeapNode));
        node->left->name = malloc((strlen(name)+1)*sizeof(char));
        strcpy(node->left->name, name);
        node->left->number = number;
        node->left->left = NULL;
        node->left->right = NULL;
        addedLeft = 0;
    }
    else if(goal == 2*cur + 2){
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

        while((temp_goal-1)/2 != cur)
            temp_goal = (temp_goal-1)/2;

        if(temp_goal == 2*cur + 1) {
            node->left = insertToHeap(node->left, 2 * cur + 1, goal, name, number);
            addedLeft = 0;
        } else {
            node->right = insertToHeap(node->right, 2 * cur + 2, goal, name, number);
            addedLeft = 1;
        }
    }

    if(addedLeft == 0){

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
    else{

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

HeapNode* heapify(HeapNode* node){

    if(node->right == NULL && node->left == NULL)
        return node;

    if(node->right == NULL){

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

    if(node->left == NULL){

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

    if(node->right->number > node->left->number){

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
    else{

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

        return node;
    }

}


HeapNode* popFromHeap(HeapNode* node, int size){

    if(size == 1)
        return node;

    size--;

    HeapNode* ptr = node;

    int counter = 0;
    int temp_size = size;

    while(counter != (temp_size-1)/2) {

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

    if(counter*2+1 == size) {

        HeapNode* head = ptr->left;

        if(node->left != head)
            head->left = node->left;
        else
            head->left = NULL;
        head->right = node->right;
        ptr->left = NULL;

        head = heapify(head);

        return head;
    }
    else{

        HeapNode* head = ptr->right;

        head->left = node->left;
        if(node->right != head)
            head->right = node->right;
        else
            head->right = NULL;
        ptr->right = NULL;

        head = heapify(head);

        return head;
    }
}

void printHeap(HeapNode* node){

    if(node == NULL)
        return;

    printf("Node: %d\nLeft: %d\tRight: %d\n", node->number, node->left == NULL ? -1 : node->left->number, node->right == NULL ? -1 : node->right->number);

    printHeap(node->left);
    printHeap(node->right);

}

void deleteHeap(HeapNode *h) {

    if(h->right != NULL)
        deleteHeap(h->right);

    if(h->left != NULL)
        deleteHeap(h->left);

    free(h->name);
    free(h);
}
