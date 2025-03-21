#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "forward_list.h"

struct HashTable
{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

struct HashTableIterator
{
    HashTable *hash_tbl;
    int bucket_idx;
    int current_element;
    ListIterator *list_it;
};

HashTableItem *hash_pair_construct(void *key, void *val)
{
    HashTableItem *p = calloc(1, sizeof(HashTableItem));

    p->key = key;
    p->val = val;

    return p;
}

void hash_pair_destroy(HashTableItem *p)
{
    free(p);
}

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable *hash_tbl = calloc(1, sizeof(HashTable));

    hash_tbl->table_size = table_size;
    hash_tbl->hash_fn = hash_fn;
    hash_tbl->cmp_fn = cmp_fn;
    hash_tbl->buckets = calloc(table_size, sizeof(ForwardList *));
    hash_tbl->n_elements = 0;

    return hash_tbl;
}

int hash_table_size(HashTable *h)
{
    return h->table_size;
}

int hash_table_n_elems(HashTable *h)
{
    return h->n_elements;
}

void hash_table_destroy(HashTable *h)
{
    for (int i = 0; i < h->table_size; i++)
        if (h->buckets[i] != NULL)
            forward_list_destroy(h->buckets[i]);

    free(h->buckets);
    free(h);
}

void *hash_table_set(HashTable *h, void *key, void *val)
{
    //pega a chave do item = índice do balde;
    int balde = h->hash_fn(h, key);

    //se o balde em questão tiver vazio;
    if (h->buckets[balde] == NULL){
        h->buckets[balde] = forward_list_construct(h->cmp_fn);
    }

    //começa pela cabeça;
    FlNode *node = h->buckets[balde]->head;

    while(node != NULL){
        HashTableItem *item = (HashTableItem *)node->value;

        if(h->cmp_fn(item->key, key) == 0){
            //atualiza o valor e retorna o valor antigo;
            void *old_val = item->val;
            item->val = val;

            return old_val;
        }

        //se não encontrou, continua percorrendo na lista;
        node = node->next;
    }

    //se não encontru, cria um novo item e insere na lista;
    HashTableItem *new = hash_pair_construct(key, val);

    forward_list_push_front(h->buckets[balde], new);

    h->n_elements++;

    return NULL;
}

Vector *hash_table_items(HashTable *hash_table)
{
    Vector *items = vector_construct();

    ForwardList *bucket = NULL;
    FlNode *node = NULL;

    //algoritmo para percorrer a hash table e retirar cada nó
    for(int i = 0; i < hash_table_size(hash_table); i++){
        bucket = hash_table->buckets[i];

        if(bucket != NULL){
            node = bucket->head;

            while(node != NULL){
                HashTableItem *item = (HashTableItem *)node->value;
                vector_push_back(items, item);

                node = node->next;
            }
        }
    }

    return items;
}

int *hash_table_count_collisions(HashTable * hash_table)
{
    int *counts = (int *) calloc (hash_table_size(hash_table), sizeof(int));

    for(int i = 0; i < hash_table_size(hash_table); i++){
        if(hash_table->buckets[i] != NULL){
           FlNode *node = hash_table->buckets[i]->head;

           while(node != NULL){
                counts[i] = counts[i] + 1;
                node = node->next;
           }
        }
    }

    return counts;
}
