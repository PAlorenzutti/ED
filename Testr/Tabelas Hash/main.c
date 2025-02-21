
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "vector.h"

int hash_str(HashTable *h, void *data)
{
    char *str = (char *)data;

    long hash_val = 0;
    int base = 127;

    for (size_t i = 0; i < strlen(str); i++)
        hash_val = (base * hash_val + str[i]) % hash_table_size(h);

    return hash_val;
}

int cmp_str(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

int cmp_vector(const void *a, const void *b){
    HashTableItem *A = (HashTableItem*) a;
    HashTableItem *B = (HashTableItem*) b;

    return (-1) * strcmp((char*)A->key, (char*)B->key);
}

int main()
{
    HashTable *h = hash_table_construct(11, hash_str, cmp_str);

    //lê a quantidade de nomes;
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        //lê o nome (chave)
        char *name = malloc(sizeof(char) * 100);
        scanf("%s", name);

        //procura pra ver se o nome já existe na tabela;
        int *atual_count = (int*)hash_table_get(h, name);

        if(atual_count != NULL){
            //aumenta a quantidade de aparições;
            (*atual_count)++;
            free(name);
        }else{
            int *count = malloc(sizeof(int));
            (*count) = 1;
            hash_table_set(h, name, count);
        }
    }

    //transforma a tabela hash em vector;
    Vector *v = hash_to_vector(h);

    //ordena o vector;
    vector_sort(v, cmp_vector);

    int size = vector_size(v);
    for(int i = 0; i < size; i++) {
        void *pair = vector_pop_back(v);
        printf("%s %d\n", (char *)((HashTableItem *)pair)->key, *(int *)((HashTableItem *)pair)->val);
    }

    vector_destroy(v);
    hash_table_destroy(h);

    return 0;
}
