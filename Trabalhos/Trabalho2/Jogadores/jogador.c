#include "jogador.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Jogador{
    char nickname[MAX_NICKNAME_LENGTH];
    char nome[MAX_NOME_LENGTH];
    int disputadas; //partidas disputadas;
    int vencidas;   //partidas vencidas;
    float percentual; //percentual de vitórias;
};

Jogador* jogador_construct(char *nickname, char* nome, int disputadas, int vencidas){
    Jogador *j = (Jogador*)malloc(sizeof(Jogador));

    strncpy(j->nickname, nickname, MAX_NICKNAME_LENGTH);
    j->nickname[MAX_NICKNAME_LENGTH - 1] = '\0';

    strncpy(j->nome, nome, MAX_NOME_LENGTH);
    j->nome[MAX_NOME_LENGTH - 1] = '\0';

    j->disputadas = disputadas;
    j->vencidas = vencidas;

    if(j->disputadas == 0){
        j->percentual = 0;
    }else{
        j->percentual = (float)j->vencidas / j->disputadas;
    }

    return j;
}

char* get_nickname_jogador(Jogador* j){
    return j->nickname;
}

int compara_string(void *key1, void *key2) {
    char *str1 = (char *)key1;
    char *str2 = (char *)key2;
   
    return strcmp(str1, str2);
}

int hash_jogador(HashTable *h, void *key) {
    char *str = (char*)key;
    int size = hash_table_size(h);
    int base = 31;
    long hash_val = 0;
    int len = strlen(str);

    for (int i = len - 1; i >= 0; i--) {
        hash_val = (hash_val * base + str[i]) % size;
    }

    hash_val = hash_val % size;
    if (hash_val < 0) {
        hash_val += size;
    }

    return hash_val;
}

int compara_jogadores(void *jogador_1, void *jogador_2) {
    Jogador *j1 = (Jogador*)jogador_1;
    Jogador *j2 = (Jogador*)jogador_2;

    if (j1->percentual == j2->percentual) {
        return strcmp(j1->nickname, j2->nickname);
    }

    if(j1->percentual < j2->percentual){
        return -1;
    }else{
        return 1;
    }
}

void print_jogador(void *j){
    Jogador *jogador = (Jogador*) j;

    printf("%s %s %d %d\n", jogador->nickname, jogador->nome, jogador->disputadas, jogador->vencidas);
}

void jogador_destroy(void* j){
    Jogador *jogador = (Jogador*)j;

    free(jogador);
}