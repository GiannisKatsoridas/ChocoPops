#include <stdlib.h>
#include <stdio.h>
#include "InstructionsHelpers.h"

int getTreeSize(Node *node) {

    if (node->right == NULL && node->left == NULL)
        return 1;
    else if (node->right == NULL)
        return getTreeSize(node->left) + 1;
    else if (node->left == NULL)
        return getTreeSize(node->right) + 1;
    else
        return getTreeSize(node->right) + getTreeSize(node->left) + 1;


}

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

int getTreeSizeBetweenDates(Node *node, char *date1, char *date2) {

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

int getTreeSizeBetweenDatesForCountry(Node *node, char *date1, char *date2, char *country) {

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

HeapNode *getTotalInfectedByCountry(Node *node, char *date1, char *date2) {

    int totalDiseases = getTotalDiseases();

    Pair **infected = malloc(sizeof(Pair *) * totalDiseases);
    for (int i = 0; i < totalDiseases; i++)
        infected[i] = NULL;

    infected = getInfectedFromNode(node, infected, date1, date2);

//    for (int i = 0; i < totalDiseases; i++) {
//        if (infected[i] == NULL)
//            continue;
//        printf("Country: %s, Disease: %s, Number: %d\n", node->key->country, infected[i]->name, infected[i]->number);
//    }

    HeapNode *h = NULL;

    for (int i = 0; i < totalDiseases; i++) {

        if (infected[i] == NULL)
            continue;

        h = insertToHeap(h, 0, i, infected[i]->name, infected[i]->number);

    }

    for (int i = 0; i < totalDiseases; i++)
        if (infected[i] != NULL) {
            free(infected[i]->name);
            free(infected[i]);
        }

    free(infected);

    return h;
}

HeapNode *getTotalInfectedByDisease(Node *node, char *date1, char *date2) {

    int totalCountries = getTotalCountries();

    Pair **infected = malloc(sizeof(Pair *) * totalCountries);
    for (int i = 0; i < totalCountries; i++)
        infected[i] = NULL;

    infected = getInfectedFromNodeForCountry(node, infected, date1, date2);

    HeapNode *h = NULL;

    for (int i = 0; i < totalCountries; i++) {

        if (infected[i] == NULL)
            continue;

        h = insertToHeap(h, 0, i, infected[i]->name, infected[i]->number);

    }

    for (int i = 0; i < totalCountries; i++)
        if (infected[i] != NULL) {
            free(infected[i]->name);
            free(infected[i]);
        }

    free(infected);

    return h;
}

Pair **getInfectedFromNode(Node *node, Pair **infected, char *date1, char *date2) {

    if (node->left != NULL)
        infected = getInfectedFromNode(node->left, infected, date1, date2);
    if (node->right != NULL)
        infected = getInfectedFromNode(node->right, infected, date1, date2);

    int counter = 0;

    while (infected[counter] != NULL) {

        if (strcmp(infected[counter]->name, node->key->diseaseID) == 0) {

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

record *searchForRecordInTree(Node *node, char *recordID) {

    if (node == NULL)
        return NULL;

    if (strcmp(node->key->recordID, recordID) == 0)
        return node->key;

    record *r = searchForRecordInTree(node->left, recordID);

    if (r != NULL)
        return r;

    return searchForRecordInTree(node->right, recordID);

}

int countCurrentPatientsInTree(Node *node) {

    if (node == NULL)
        return 0;

    int a = countCurrentPatientsInTree(node->left);
    int b = countCurrentPatientsInTree(node->right);

    if (strcmp(node->key->exitDate, "-") == 0 || strcmp(node->key->exitDate, "-\r") == 0)
        return a + b + 1;
    else
        return a + b;
}
