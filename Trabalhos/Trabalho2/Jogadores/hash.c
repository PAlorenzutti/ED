#include "hash.h"
#include "forward_list.h"

#include <stdio.h>
#include <stdlib.h>

struct HashTableItem
{
    void *key;
    void *val;
};

struct HashTable{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int num_elems;
};

struct HashTableIterator{
    ForwardList **buckets;
    int table_size;          
    int current_bucket;     
    Node *current_node;     
    int current_element;     
    int total_elements;     
};

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn){
    HashTable *h = (HashTable*)malloc(sizeof(HashTable));

    h->table_size = table_size;
    h->buckets = calloc(h->table_size, sizeof(ForwardList*));
    h->hash_fn = hash_fn;
    h->cmp_fn = cmp_fn;
    h->num_elems = 0;

    return h;
}

HashTableItem *hash_table_item_construct(void *key, void *val){
    HashTableItem *item = (HashTableItem*)malloc(sizeof(HashTableItem));

    item->key = key;
    item->val = val;

    return item;
}

void hash_table_item_destroy(HashTableItem *item){
    // free(item->key);
    // free(item->val);
    free(item);
}

void *hash_table_get(HashTable *h, void *key){
    int hash = h->hash_fn(h, key);

    if (h->buckets[hash] == NULL){
        return NULL;
    }

    Node *n = forward_list_get_node(h->buckets[hash], 0);

    while (n != NULL) {
        HashTableItem *item = (HashTableItem *)n->value;

        if (h->cmp_fn(item->key, key) == 0) {
            return item->val;
        }

        n = n->next;
    }
    
    return NULL;
}

void *hash_table_set(HashTable *h, void *key, void *val) {
    int hash = h->hash_fn(h, key);

    if (h->buckets[hash] == NULL) {
        h->buckets[hash] = forward_list_construct();
    }

    Node *n = forward_list_get_node(h->buckets[hash], 0);

    while (n != NULL) {
        HashTableItem *item = (HashTableItem *)n->value;

        if (h->cmp_fn(item->key, key) == 0) {
            void *old_val = item->val;
            item->val = val;

            return old_val;
        }

        n = n->next;
    }

    HashTableItem *newItem = hash_table_item_construct(key, val);

    forward_list_push_front(h->buckets[hash], newItem);

    h->num_elems++;

    return NULL;
}

void *hash_table_pop(HashTable *h, void *key){
    int hash = h->hash_fn(h, key);

    Node *n = forward_list_get_node(h->buckets[hash], 0);
    int i = 0;

    while (n != NULL) {
        HashTableItem *current = (HashTableItem *)n->value;

        if (h->cmp_fn(current->key, key) == 0) {
            HashTableItem *old_item = (HashTableItem*)forward_list_pop_index(h->buckets[hash], i);

            void *old_val = old_item->val;

            // destroy the old item;
            // free(old_item->key);
            free(old_item);

            h->num_elems--;

            return old_val;
        }
        
        n = n->next;

        i++;
    }

    return NULL;
}

int hash_table_size(HashTable *h){
    return h->table_size;
}

int hash_table_num_elems(HashTable *h){
    return h->num_elems;
}

void hash_table_destroy(HashTable *h)
{
    for (int i = 0; i < h->table_size; i++){
        if (h->buckets[i] != NULL){
            Node *n = forward_list_get_node(h->buckets[i], 0);

            while (n != NULL){
                HashTableItem *pair = n->value;
                hash_table_item_destroy(pair);
                n = n->next;
            }

            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}

HashTableIterator *hash_table_iterator(HashTable *h) {
    HashTableIterator *it = (HashTableIterator*)malloc(sizeof(HashTableIterator));

    it->buckets = h->buckets;
    it->table_size = h->table_size;
    it->current_bucket = 0;
    it->current_node = NULL;
    it->current_element = 0;
    it->total_elements = h->num_elems;

    return it;
}

int hash_table_iterator_is_over(HashTableIterator *it) {
    return (it->current_element >= it->total_elements);
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it) {
    if (it->current_element >= it->total_elements) {
        return NULL;
    }

    while (it->current_bucket < it->table_size) {
        if (it->current_node == NULL) {
            ForwardList *bucket = it->buckets[it->current_bucket];
            
            while (bucket == NULL || forward_list_get_node(bucket, 0) == NULL) {
                it->current_bucket++;

                if (it->current_bucket >= it->table_size) {
                    return NULL; 
                }
                
                bucket = it->buckets[it->current_bucket];
            }

            it->current_node = forward_list_get_node(bucket, 0);
        }

        HashTableItem *item = (HashTableItem *)it->current_node->value;
        it->current_node = it->current_node->next;
        it->current_element++;

        if (it->current_node == NULL) {
            it->current_bucket++;
        }

        return item;
    }

    return NULL;
}

void hash_table_iterator_destroy(HashTableIterator *it){
    free(it);
}

Vector *hash_to_vector(HashTable *h){
    HashTableIterator *it = hash_table_iterator(h);

    Vector *v = vector_construct();

    while(!hash_table_iterator_is_over(it)){
        vector_push_back(v, hash_table_iterator_next(it));
    }

    hash_table_iterator_destroy(it);

    return v;
}

void hash_table_print(HashTable *h, void (*print_fn)(void *)){
    Vector *v = hash_to_vector(h);

    for(int i = 0; i < vector_size(v); i++){
        HashTableItem *item = (HashTableItem *)vector_get(v, i);
        print_fn(item->val);
        // printf("\n");
    }

    vector_destroy(v);
}
