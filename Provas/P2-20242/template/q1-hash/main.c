#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "vector.h"

const int HASH_TABLE_SIZE = 13;


int hash_function(HashTable *table, void *key)
{
    char *str = key;
    int table_size = hash_table_size(table);

    unsigned long hash_val = 0, base = 27183;
    unsigned long random_val = 31415;
    int size = strlen(str);

    for (int i = 0; i < size; i++)
    {
        hash_val = (hash_val * random_val + str[i]) % table_size;
        random_val = (random_val * base) % (table_size - 1);
    }

    return hash_val;
}


int cmp_strings(void *k1, void *k2)
{
    return strcmp((char *)k1, (char *)k2);
}


int cmp_items(void *k1, void *k2)
{
    return strcmp(
        (char*) ((HashTableItem*) k1)->key,
        (char*) ((HashTableItem*) k2)->key
    );
}


int main()
{
    int n;
    char nome[100], telefone[100];

    HashTable *hash_table = hash_table_construct(HASH_TABLE_SIZE, hash_function, cmp_strings);

    scanf("%d", &n);

    // le dados de entrada e adiciona na hash
    for (int i = 0; i < n; i++)
    {
        scanf("\n%s %s", nome, telefone);
        char *new_key = strdup(nome);
        char *new_val = strdup(telefone);

        void *old_value = hash_table_set(hash_table, new_key, new_val);

        // operation was an update
        if (old_value)
        {
            free(new_key); // the old key is maintained in the hash
            free(old_value); // the replaced value should be removed
        }
    }

    // mostra itens da hash
    Vector *items = hash_table_items(hash_table);
    vector_sort(items, cmp_items);

    for (int i = 0; i < vector_size(items); i++)
    {
        HashTableItem *item = vector_get(items, i);
        printf("%s %s\n", (char *) item->key, (char *)item->val);
    }

    // mostra colisoes
    int *counts = hash_table_count_collisions(hash_table);

    for (int i = 0; i < hash_table_size(hash_table); i++)
        printf("%d ", counts[i]);
    printf("\n");

    // desalocacoes
    for (int i = 0; i < vector_size(items); i++)
    {
        HashTableItem *item = vector_get(items, i);
        free(item->key);
        free(item->val);
        hash_pair_destroy(item);
    }

    free(counts);
    vector_destroy(items);
    hash_table_destroy(hash_table);

    return 0;
}
