
#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "vector.h"

typedef struct HashTable HashTable;

typedef struct
{
    void *key;
    void *val;
} HashTableItem;

typedef struct HashTableIterator HashTableIterator;

typedef int (*HashFunction)(HashTable *, void *);
typedef int (*CmpFunction)(void *k1, void *k2);

// HashTableItem functions
HashTableItem *hash_pair_construct(void *key, void *val);
void hash_pair_destroy(HashTableItem *p);

// HashTable functions
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn);
void hash_table_destroy(HashTable *h);

int hash_table_size(HashTable *h);
int hash_table_n_elems(HashTable *h);

void *hash_table_set(HashTable *h, void *key, void *val);
int *hash_table_count_collisions(HashTable *hash_table);
Vector *hash_table_items(HashTable *hash_table);

#endif