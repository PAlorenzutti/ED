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

struct HashTableIterator{
    ForwardList **buckets;
    int table_size;
    int current;
    ListIterator *fl_it;
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
    int hash = h->hash_fn(h, key);

    //se o balde estiver vazio, retorna NULL;
    if (h->buckets[hash] == NULL){
        return NULL;
    }

    //pega a cabeça do balde;
    Node *n = h->buckets[hash]->head;

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
    //Obtém a hash da chave
    int hash = h->hash_fn(h, key);

    //Se o balde estiver vazio, cria a lista dele
    if (h->buckets[hash] == NULL) {
        h->buckets[hash] = forward_list_construct();
    }

    //Percorre a lista para verificar se a chave já existe
    Node *n = h->buckets[hash]->head;

    while (n != NULL) {
        HashTableItem *item = (HashTableItem *)n->value;

        if (h->cmp_fn(item->key, key) == 0) {
            // A chave já existe, então atualiza o valor e retorna o valor antigo
            void *old_val = item->val;
            item->val = val;

            return old_val;
        }

        n = n->next;
    }

    // Se a chave não existe, adiciona um novo item
    HashTableItem *new_item = hash_table_item_construct(key, val);

    forward_list_push_back(h->buckets[hash], new_item);

    h->n_elements++;

    return NULL;
}

void *hash_table_pop(HashTable *h, void *key){
    //calcula o hash da chave;
    int hash = h->hash_fn(h, key);

    //pega a cabeça do balde em questão
    Node *n = h->buckets[hash]->head;
    int i = 0;

    while (n != NULL) {
        HashTableItem *atual = (HashTableItem *)n->value;

        //se for igual, tira o nó da lista e retorna o valor;
        if (h->cmp_fn(atual->key, key) == 0) {
            //popa o item da lista do balde;
            HashTableItem *old = (HashTableItem*)forward_list_pop_index(h->buckets[hash], i);

            //pega o valor do item antigo;
            void *old_val = old->val;

            //destrói o item antigo;
            free(old->key);
            free(old);

            //diminui o número de elementos na tabela;
            h->n_elements--;

            //retorna o valor antigo;
            return old_val;
        }
        
        //se não achou, atualiza o nó atual com o próximo;
        n = n->next;

        //aumenta o índice;
        i++;
    }

    //se não achar nada com essa chave, retorna NULL;
    return NULL;
}

int hash_table_size(HashTable *h){
    return h->table_size;
}

int hash_table_num_elems(HashTable *h){
    return h->n_elements;
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

            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}

HashTableIterator *hash_table_iterator(HashTable *h){
    HashTableIterator *it = (HashTableIterator*)malloc(sizeof(HashTableIterator));

    //passa a bucket list pro iterador;
    it->buckets = h->buckets;

    //passa o tamanho da tabela hash;
    it->table_size = h->table_size;

    it->current = 0;
    
    return it;
}

int hash_table_iterator_is_over(HashTableIterator *it){
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it){
    //ideia geral: se tiver próximo elemento, ele retorna o hash item do atual e atualiza o atual com o próximo;
}


void hash_table_iterator_destroy(HashTableIterator *it){
    free(it);
}

