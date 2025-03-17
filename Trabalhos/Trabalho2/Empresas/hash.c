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
    int n_elements;
};

struct HashTableIterator{
    ForwardList **buckets;
    int table_size;          // Tamanho total da tabela
    int current_bucket;      // Balde atual
    Node *current_node;      // Nó atual dentro do balde
    int current_element;     // Contador de elementos percorridos
    int total_elements;      // Total de elementos na tabela
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
    Node *n = forward_list_get_node(h->buckets[hash], 0);

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
    //obtém a hash da chave
    int hash = h->hash_fn(h, key);

    //se o balde estiver vazio, cria a lista dele
    if (h->buckets[hash] == NULL) {
        h->buckets[hash] = forward_list_construct();
    }

    //percorre a lista para verificar se a chave já existe
    Node *n = forward_list_get_node(h->buckets[hash], 0);

    while (n != NULL) {
        HashTableItem *item = (HashTableItem *)n->value;

        //comparando empresa com sigla, atualmente
        if (h->cmp_fn(item->key, key) == 0) {
            // A chave já existe, então atualiza o valor e retorna o valor antigo
            void *old_val = item->val;
            item->val = val;

            return old_val;
        }

        n = n->next;
    }

    //se a chave não existe, adiciona um novo item
    HashTableItem *new_item = hash_table_item_construct(key, val);

    forward_list_push_front(h->buckets[hash], new_item);

    h->n_elements++;

    return NULL;
}

void *hash_table_pop(HashTable *h, void *key){
    //calcula o hash da chave;
    int hash = h->hash_fn(h, key);

    //pega a cabeça do balde em questão
    Node *n = forward_list_get_node(h->buckets[hash], 0);
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
    it->total_elements = h->n_elements; // Captura o total de elementos

    return it;
}

int hash_table_iterator_is_over(HashTableIterator *it) {
    return (it->current_element >= it->total_elements);
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it) {
    if (it->current_element >= it->total_elements) {
        return NULL; // Todos os elementos já foram percorridos
    }

    while (it->current_bucket < it->table_size) {
        // Encontra o próximo balde não vazio
        if (it->current_node == NULL) {
            ForwardList *bucket = it->buckets[it->current_bucket];
            while (bucket == NULL || forward_list_get_node(bucket, 0) == NULL) {
                it->current_bucket++;
                if (it->current_bucket >= it->table_size) {
                    return NULL; // Fim da tabela
                }
                bucket = it->buckets[it->current_bucket];
            }
            it->current_node = forward_list_get_node(bucket, 0);
        }

        // Retorna o item atual e avança
        HashTableItem *item = (HashTableItem *)it->current_node->value;
        it->current_node = it->current_node->next;
        it->current_element++;

        // Se o balde terminou, avança para o próximo
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
    //constrói o iterator;
    HashTableIterator *it = hash_table_iterator(h);

    //constrói o vector;
    Vector *v = vector_construct();

    //enquanto o iterator não chegar ao fim, vai adicionando hash item no vector;
    while(!hash_table_iterator_is_over(it)){
        vector_push_back(v, hash_table_iterator_next(it));
    }

    //destrói o iterator;
    hash_table_iterator_destroy(it);

    return v;
}

void hash_table_print(HashTable *h, void (*print_fn)(void *)){
    //converte a tabela hash para um vetor;
    Vector *v = hash_to_vector(h);

    //itera sobre o vetor, printando cada item;
    for(int i = 0; i < vector_size(v); i++){
        HashTableItem *item = (HashTableItem *)vector_get(v, i);
        print_fn(item->val);
        printf("\n");
    }

    //destrói o vetor;
    vector_destroy(v);
}

