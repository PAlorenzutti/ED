#include "hash.h"
#include "forward_list.h"

#include <stdio.h>
#include <stdlib.h>

struct HashTable{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn){
    HashTable *h = (HashTable*)malloc(sizeof(HashTable));

    h->table_size = table_size;
    h->buckets = calloc(h->table_size, sizeof(ForwardList*));
    h->hash_fn = hash_fn;
    h->cmp_fn = cmp_fn;
    h->n_elements = 0;

    return h;
}

HashTableItem *hash_table_item_construct(void *key, void *val){
    HashTableItem *item = (HashTableItem*)malloc(sizeof(HashTableItem));

    item->key = key;
    item->val = val;

    return item;

}

void hash_table_item_destroy(HashTableItem *item){
    free(item->key);
    free(item->val);
    free(item);
}

void *hash_table_get(HashTable *h, void *key){
    int key_val = h->hash_fn(h, key);

    //se o balde estiver vazio, retorna NULL;
    if (h->buckets[key_val] == NULL){
        return NULL;
    }

    //pega a cabeça do balde;
    Node *n = h->buckets[key_val]->head;

    //itera sobre o balde;
    while (n != NULL) {
        HashTableItem *item = (HashTableItem *)n->value;

        //se encontrar a chave, retorna o valor associado a ela;
        if (h->cmp_fn(item->key, key) == 0) {
            return item->val; // Retorna o valor em vez do item
        }

        n = n->next;
    }
    
    //se não encontrou nada, retorna NULL;
    return NULL;
}

void *hash_table_set(HashTable *h, void *key, void *val) {
    //pega a hash da chave;
    int key_val = h->hash_fn(h, key);

    //verifica se o item existe;
    HashTableItem *existing_item = hash_table_get(h, key);

    //se o item existe, apenas atualiza;
    if(existing_item != NULL){
        //atualiza o item e retorna o item antigo;
        void *old_val = existing_item->val;
        existing_item->val = val;

        return old_val;
    }else{
        //se o balde estiver vazio, cria a lista dele;
        if(h->buckets[key_val] == NULL){
            h->buckets[key_val] = forward_list_construct();
        }

        //adiciona o novo item ao final da lista do balde;
        HashTableItem *new_item = hash_table_item_construct(key, val);

        forward_list_push_back(h->buckets[key_val], new_item);

        h->n_elements++;

        return NULL;
    }
}

int hash_table_size(HashTable *h){
    return h->table_size;
}

void hash_table_destroy(HashTable *h)
{
    for (int i = 0; i < h->table_size; i++){
        if (h->buckets[i] != NULL){
            Node *n = h->buckets[i]->head;

            while (n != NULL){
                HashTableItem *pair = n->value;
                hash_table_item_destroy(pair);
                n = n->next;
            }

            free(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}

