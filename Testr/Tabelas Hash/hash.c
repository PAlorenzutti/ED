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

void *hash_table_get(HashTable *h, void *key){
    //pega a chave (índice) do balde onde vai ser pesquisado o item com a respectiva chave;
    int key_val = h->hash_fn(h, key);

    //pega o nó que é a cabeça do balde;
    Node *n = h->buckets[key_val]->head;

    while(n != NULL){
        //pega o par chave-valor armazenado na valor do nó;
        HashTableItem *item  = (HashTableItem*)n->value;
        
        //compara a chave do item com a chave buscada;
        if(!h->cmp_fn(item->key, key)){
            return item;
        }

        //caso não tenha encontrado ainda, atualiza o nó para o próximo;
        n = n->next;
    }

    //caso não tenha encontrado
    return NULL;
}

void *hash_table_set(HashTable *h, void *key, void *val){
    //pega a chave (índice) do balde que vai receber o item;
    int key_val = h->hash_fn(h, key);

    //se o balde estiver vazio, crie a lista e insere ele na cabeça da lista;
    if(h->buckets[key_val] == NULL){
        h->buckets[key_val] = forward_list_construct();

        //cria um item da tabela com chave e valor dados;   
        HashTableItem *item = hash_table_item_construct(key, val);

        forward_list_push_back(h->buckets[key_val], item);
    }

    //caso contrário, busca o item no balde
    HashTableItem *item = hash_table_get(h, key);

    //se o item já existir;
    if(item != NULL){
        //atualiza o valor do par e retorna o valor anterior;
        void *val_prev = item->val;
        item->val = val;

        return val_prev;
    }else{
        //insere o novo par ao final da lista do balde;
        HashTableItem *new = hash_table_item_construct(key, val);

        forward_list_push_back(h->buckets[key_val], new);
    }

    return NULL;
}

int hash_table_size(HashTable *h){
    return h->table_size;
}

void hash_table_destroy(HashTable *h){
    for(int i = 0; i < h->table_size; i++){
        if(h->buckets[i] != NULL){
            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}

