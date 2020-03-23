typedef struct record_struct {

    char* recordID;
    char* patientFirstName;
    char* patientLastName;
    char* diseaseID;
    char* country;
    char* entryDate;
    char* exitDate;

} record;

int diseaseHashTableNumOfEntries, countryHashTableNumOfEntries, bucketSize;


typedef struct AVL_tree_node
{
    record* key;

    struct AVL_tree_node *left;

    struct AVL_tree_node *right;

} Node;

typedef struct bucket_item_struct {

    char key[20];
    Node* value;

} bucket_item;

typedef struct bucket_struct {

    bucket_item** items;
    int items_amount;
    struct bucket_struct* next;

} bucket;

bucket** diseaseHashTable;
bucket** countryHashTable;

void parseArguments(char** argv, char** patientRecordsFile);

int hashFunction(char* string, int max);

void globalStructsInitialization();

bucket* initializeBucket();

int errorCode;
int available_space;
int available_items;

int getTotalDiseases();
int getTotalCountries();