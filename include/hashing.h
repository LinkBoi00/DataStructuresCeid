#ifndef HASHING_H
#define HASHING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATE_LEN 11         // YYYY-MM-DD plus NULL string terminator
#define HASH_TABLE_SIZE 11      // Buckets number for the hash table: m=12 (Arbitrary choice)s

typedef struct HashNode {
    char date[MAX_DATE_LEN];
    double average_temp;
    struct HashNode* next;
} HashNode;

typedef struct List {
    HashNode* head;
    HashNode* tail;
} HashList;

typedef struct {
    HashList* buckets[HASH_TABLE_SIZE];
} HashTable;

HashTable* create_hash_table(void);
void insert_hash_table(HashTable* table, char* date, double average_temp);
HashNode* search_in_hash_table(HashTable* table);
void edit_hash_table_temperature(HashTable* table);
void delete_hash_table_entry(HashTable* table);
void print_hash_table(HashTable* table);
void free_hash_table(HashTable* table);

#endif
