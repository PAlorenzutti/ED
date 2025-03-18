#ifndef _JOGADOR_H_
#define _JOGADOR_H_

#include "hash.h"

#define MAX_NICKNAME_LENGTH 100
#define MAX_NOME_LENGTH 100

typedef struct Jogador Jogador;

Jogador* jogador_construct(char *nickname, char* nome, int disputadas, int vencidas);

char* get_nickname_jogador(Jogador* j);

int hash_jogador(HashTable *h, void *key);

int compara_string(void *key1, void *key2);

int compara_jogadores(void *jogador_1, void *jogador_2);

void print_jogador(void *j);

void jogador_destroy(void* j);

#endif