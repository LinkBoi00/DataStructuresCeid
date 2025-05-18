#include "include/hashing.h"

HashTable* create_hash_table(void);
void insert_hash_table(HashTable* table, char* date, double temp);
unsigned int hash(char* key);
HashNode* search_in_hash_table(HashTable* table);
void print_hash_table(HashTable* table);
void free_hash_table(HashTable* table);

HashList* create_list(void);
HashNode* create_hash_node(char* date, double average_temp);
void insert_at_end(HashList* list, char* date, double average_temp);
void free_list_nodes(HashList* list);

// Hash Table functions
HashTable* create_hash_table(void) {
    HashTable* table = malloc(sizeof(HashTable));
    if (table == NULL) { 
        printf("create_hash_table: Memory allocation failed for table.\n");
        return NULL;
    }

    // Initialize buckets
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }

    return table;
}

void insert_hash_table(HashTable* table, char* date, double temp) {
    // Calculate date's hash
    unsigned int index = hash(date);

    // Create a list at the bucket if it doesn't exist
    if (!table->buckets[index]) {
        table->buckets[index] = create_list();
    }

    // Insert the node to the bucket's list
    insert_at_end(table->buckets[index], date, temp);
}

unsigned int hash(char* key) {
    unsigned int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += (unsigned char)key[i];
    }
    return sum % HASH_TABLE_SIZE;
}

HashNode* search_in_hash_table(HashTable* table) {
    char date[MAX_DATE_LEN] = { 0 };

    if (table == NULL) return NULL;

    // Get the user's date and compute its hash
    scanf("%19s", date);
    unsigned int index = hash(date);

    // Search for the node with the previous hash
    HashNode* curr = table->buckets[index]->head;
    while (curr) {
        if (strcmp(curr->date, date) == 0) {
            printf("Η αναζήτηση ήταν επιτυχής.\n");
            printf("Η ΜΕΣΗ ΘΕΡΜΟΚΡΑΣΙΑ είναι: %.2lf.\n", curr->average_temp);
            return curr;
        }
        curr = curr->next;
    }

    printf("Η αναζήτηση ήταν ανεπιτυχής.\n");
    printf("Δεν βρέθηκαν δεδομένα για τη δοσμένη ΗΜΕΡΑ.\n");
    return NULL;
}

void edit_hash_table_temperature(HashTable* table) {
    if (table == NULL) return;

    // Perform a search to check if the entry exists
    HashNode* node = search_in_hash_table(table);
    if (node == NULL) return;

    // If it exists, prompt the user to enter the new average temperature
    printf("Εισάγετε νέα τιμή για τη ΜΕΣΗ ΘΕΡΜΟΚΡΑΣΙΑ: ");
    double new_temp = 0.0;
    scanf("%lf", &new_temp);

    node->average_temp = new_temp;
}

void delete_hash_table_entry(HashTable* table) {

    // Get the date from the user
    char date[MAX_DATE_LEN] = {0};
    scanf("%19s", date);
    unsigned int index = hash(date);

    // Traverse through the hash table
    HashNode* curr = table->buckets[index]->head;
    HashNode* prev = NULL;  // Keep this pointer because we have a singly linked list
    while (curr) {
        if (strcmp(curr->date, date) == 0) {
            if (prev) 
                prev->next = curr->next;
            else 
                table->buckets[index]->head = curr->next;

            free(curr);
            printf("H εγγραφη διαγράφηκε επιτυχώς.\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("Δεν βρέθηκε εγγραφή στον πίνακα κατακερματισμού για τη δοσμένη ΗΜΕΡΑ.\n");
}


void print_hash_table(HashTable* table) {
    printf("----- Hash Table Contents -----\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        printf("Bucket %d:\n", i);
        if (!table->buckets[i]) {
            printf("  (empty)\n");
            continue;
        }
        HashNode* curr = table->buckets[i]->head;
        while (curr) {
            printf("  %s -> %.2f°C\n", curr->date, curr->average_temp);
            curr = curr->next;
        }
    }
}

void free_hash_table(HashTable* table) {
    if (table == NULL) return;

    // Free each bucket
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        free_list_nodes(table->buckets[i]);
        free(table->buckets[i]);
    }

    // Free the table
    free(table);
}

// Linked List functions
HashList* create_list(void) {
    HashList* list = (HashList*)malloc(sizeof(HashList));
    if (list == NULL) {
        printf("create_list: Memory allocation failed in create_list");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    return list;
}

HashNode* create_hash_node(char* date, double average_temp) {
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    if (node == NULL) {
        printf("create_hash_node: Memory allocation failed in create_hash_node.\n");
        return NULL;
    }

    strcpy(node->date, date);
    node->average_temp = average_temp;
    node->next = NULL;
    return node;
}

void insert_at_end(HashList* list, char* date, double average_temp) {
    if (list == NULL) {
        printf("insert_at_end: List is NULL\n");
        return;
    }

    // Create new node
    HashNode* new_node = create_hash_node(date, average_temp);
    if (new_node == NULL) {
        printf("insert_at_end: Failed to create new node\n");
        return;
    }

    if (list->head == NULL) {
        // If the list is empty: Make the new node
        // both the head and the tail of the list
        list->head = new_node;
        list->tail = new_node;
    } else {
        // If list is not empty: Insert the new node after the current tail
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

void free_list_nodes(HashList* list) {
    if (list == NULL) return;

    // Free the nodes
    HashNode* current = list->head;
    while (current != NULL) {
        HashNode* next = current->next;
        free(current);
        current = next;
    }
}