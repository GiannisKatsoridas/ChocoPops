#include <stdlib.h>
#include <stdio.h>
#include "InstructionsHelpers.h"


// Recursive function to get the total size of a tree (meaning all the nodes in contains)
int getTreeSize(Node *node) {

    if (node->right == NULL && node->left == NULL)
        return 1;       // both children are NULL. just return the size of this node (1)
    else if (node->right == NULL)
        return getTreeSize(node->left) + 1;     // calculate the size of left subtree
    else if (node->left == NULL)
        return getTreeSize(node->right) + 1;    // calculate the size of right subtree
    else
        return getTreeSize(node->right) + getTreeSize(node->left) + 1;  // add both sizes


}


// Recursive function to get the size of a heap (meaning all the nodes it contains)
int getHeapSize(HeapNode *node) {

    if (node->right == NULL && node->left == NULL)
        return 1;
    else if (node->right == NULL)
        return getHeapSize(node->left) + 1;
    else if (node->left == NULL)
        return getHeapSize(node->right) + 1;
    else
        return getHeapSize(node->right) + getHeapSize(node->left) + 1;

}


// Recursive function to get the size of a tree by counting only the nodes that are inside given dates
int getTreeSizeBetweenDates(Node *node, char *date1, char *date2) {

    // if date is inside limits, then counted will be 1, else 0
    int counted =
            (compareDates(date1, node->key->entryDate) == 1) && (compareDates(node->key->entryDate, date2) == 1) ? 1
                                                                                                                 : 0;

    if (node->right == NULL && node->left == NULL)
        return counted;
    else if (node->right == NULL)
        return getTreeSizeBetweenDates(node->left, date1, date2) + counted;
    else if (node->left == NULL)
        return getTreeSizeBetweenDates(node->right, date1, date2) + counted;
    else
        return getTreeSizeBetweenDates(node->right, date1, date2) + getTreeSizeBetweenDates(node->left, date1, date2) +
               counted;

}

// Recursive function to get the size of a tree by counting only the nodes that are inside given dates and in given country
int getTreeSizeBetweenDatesForCountry(Node *node, char *date1, char *date2, char *country) {

    // if date is inside limits and in given country, then counted will be 1, else 0
    int counted =
            (compareDates(date1, node->key->entryDate) == 1) && (compareDates(node->key->entryDate, date2) == 1) &&
            (strcmp(country, node->key->country) == 0) ? 1 : 0;

    if (node->right == NULL && node->left == NULL)
        return counted;
    else if (node->right == NULL)
        return getTreeSizeBetweenDatesForCountry(node->left, date1, date2, country) + counted;
    else if (node->left == NULL)
        return getTreeSizeBetweenDatesForCountry(node->right, date1, date2, country) + counted;
    else
        return getTreeSizeBetweenDatesForCountry(node->right, date1, date2, country) +
               getTreeSizeBetweenDatesForCountry(node->left, date1, date2, country) + counted;


}


// Creates a max heap with total infections by disease in a country. Firstly creates an array
// of type Pair* to hold the total patients per disease and then inserts them in a heap.
HeapNode *getTotalInfectedByCountry(Node *node, char *date1, char *date2) {

    int totalDiseases = getTotalDiseases();

    Pair **infected = malloc(sizeof(Pair *) * totalDiseases);
    for (int i = 0; i < totalDiseases; i++)
        infected[i] = NULL;

    infected = getInfectedFromNode(node, infected, date1, date2);   // get all the patients from each disease

    HeapNode *h = NULL;

    int heap_size = 0;

    for (int i = 0; i < totalDiseases; i++) {

        if (infected[i] == NULL)
            continue;

        h = insertToHeap(h, 0, heap_size, infected[i]->name, infected[i]->number);  // insert each pair in the heap
        heap_size++;

    }

    for (int i = 0; i < totalDiseases; i++)
        if (infected[i] != NULL) {
            free(infected[i]->name);
            free(infected[i]);
        }

    free(infected);

    return h;
}


// Same as above with only difference the string it compares (here the country, before the disease)
HeapNode *getTotalInfectedByDisease(Node *node, char *date1, char *date2) {

    int totalCountries = getTotalCountries();

    Pair **infected = malloc(sizeof(Pair *) * totalCountries);
    for (int i = 0; i < totalCountries; i++)
        infected[i] = NULL;

    infected = getInfectedFromNodeForCountry(node, infected, date1, date2);

    HeapNode *h = NULL;

    int heap_size = 0;

    for (int i = 0; i < totalCountries; i++) {

        if (infected[i] == NULL)
            continue;

        h = insertToHeap(h, 0, heap_size, infected[i]->name, infected[i]->number);
        heap_size++;

    }

    for (int i = 0; i < totalCountries; i++)
        if (infected[i] != NULL) {
            free(infected[i]->name);
            free(infected[i]);
        }

    free(infected);

    return h;
}

// Recursive function that get the total amount of patients from a tree.
Pair **getInfectedFromNode(Node *node, Pair **infected, char *date1, char *date2) {

    if (node->left != NULL)
        infected = getInfectedFromNode(node->left, infected, date1, date2);     // Get all patients from left subtree
    if (node->right != NULL)
        infected = getInfectedFromNode(node->right, infected, date1, date2);    // Get all patients from right subtree

    // add current node in the array

    int counter = 0;

    // search for the given disease in the already created infected array
    while (infected[counter] != NULL) {

        if (strcmp(infected[counter]->name, node->key->diseaseID) == 0) {       // disease found

            if (date1 != NULL) {

                // if date inside limits, increase the counter
                if (compareDates(date1, node->key->entryDate) == 1 && compareDates(node->key->entryDate, date2) == 1)
                    infected[counter]->number++;

            } else {

                infected[counter]->number++;        // increase the counter

            }
            break;
        }


        counter++;
    }

    if (infected[counter] == NULL) {        // disease not found, create a new pair in the array and set the size to 1

        if (date1 != NULL) {

            if (compareDates(date1, node->key->entryDate) == 1 && compareDates(node->key->entryDate, date2) == 1) {
                infected[counter] = malloc(sizeof(Pair));
                infected[counter]->number = 1;
                infected[counter]->name = malloc((strlen(node->key->diseaseID) + 1) * sizeof(char));
                strcpy(infected[counter]->name, node->key->diseaseID);
            }

        } else {

            infected[counter] = malloc(sizeof(Pair));
            infected[counter]->number = 1;
            infected[counter]->name = malloc((strlen(node->key->diseaseID) + 1) * sizeof(char));
            strcpy(infected[counter]->name, node->key->diseaseID);

        }

    }

    return infected;

}

///////////////////////////////////////////////////
// Same as above only with country in comparison //
///////////////////////////////////////////////////
Pair **getInfectedFromNodeForCountry(Node *node, Pair **infected, char *date1, char *date2) {

    if (node->left != NULL)
        infected = getInfectedFromNodeForCountry(node->left, infected, date1, date2);
    if (node->right != NULL)
        infected = getInfectedFromNodeForCountry(node->right, infected, date1, date2);

    int counter = 0;

    while (infected[counter] != NULL) {

        if (strcmp(infected[counter]->name, node->key->country) == 0) {

            if (date1 != NULL) {

                if (compareDates(date1, node->key->entryDate) == 1 && compareDates(node->key->entryDate, date2) == 1)
                    infected[counter]->number++;

            } else {

                infected[counter]->number++;

            }
            break;
        }


        counter++;
    }

    if (infected[counter] == NULL) {

        if (date1 != NULL) {

            if (compareDates(date1, node->key->entryDate) == 1 && compareDates(node->key->entryDate, date2) == 1) {
                infected[counter] = malloc(sizeof(Pair));
                infected[counter]->number = 1;
                infected[counter]->name = malloc((strlen(node->key->country) + 1) * sizeof(char));
                strcpy(infected[counter]->name, node->key->country);
            }

        } else {

            infected[counter] = malloc(sizeof(Pair));
            infected[counter]->number = 1;
            infected[counter]->name = malloc((strlen(node->key->country) + 1) * sizeof(char));
            strcpy(infected[counter]->name, node->key->country);

        }

    }

    return infected;

}

// Search every record in tree for the given record id. If found return the record. If not, returns NULL
record *searchForRecord(char *recordID) {

    for (int i = 0; i < diseaseHashTableNumOfEntries; i++) {

        bucket *ptr = diseaseHashTable[i];

        while (ptr != NULL) {

            for (int j = 0; j < available_items; j++) {

                if (ptr->items[j] == NULL)
                    break;

                record *rec = searchForRecordInTree(ptr->items[j]->value, recordID);

                if (rec != NULL)
                    return rec;

            }

            ptr = ptr->next;
        }

    }

    return NULL;
}

// Recursive function to search for a record. If not found in left subtree, search the right. Else return the node found.
record *searchForRecordInTree(Node *node, char *recordID) {

    if (node == NULL)
        return NULL;

    if (strcmp(node->key->recordID, recordID) == 0)         // record found
        return node->key;

    record *r = searchForRecordInTree(node->left, recordID);    // search the left subtree for the record

    if (r != NULL)
        return r;

    return searchForRecordInTree(node->right, recordID);        // search the right subtree for the record

}

// Recursive function to find all the patients whose exitDate is '-'
int countCurrentPatientsInTree(Node *node) {

    if (node == NULL)
        return 0;

    int a = countCurrentPatientsInTree(node->left);     // search the left subtree for the patients
    int b = countCurrentPatientsInTree(node->right);    // search the right subtree for the patients

    if (strcmp(node->key->exitDate, "-") == 0 || strcmp(node->key->exitDate, "-\r") == 0)
        return a + b + 1;
    else
        return a + b;
}
