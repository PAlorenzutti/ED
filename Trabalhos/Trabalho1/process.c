#include "process.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Process{
    char nome[MAX_NAME_LENGTH];
    char tipo[MAX_NAME_LENGTH];
    int prioridade;
    int carga;
    int iteracao_inicio;
    int ultimo_uso;
};

Process *process_constructor(char *nome, char *tipo, int prioridade, int carga, int iteracao_inicio){
    Process *p = (Process*)malloc(sizeof(Process));
    
    strncpy(p->nome, nome, MAX_NAME_LENGTH);
    p->nome[MAX_NAME_LENGTH - 1] = '\0';

    strncpy(p->tipo, tipo, MAX_NAME_LENGTH);
    p->tipo[MAX_NAME_LENGTH - 1] = '\0';

    p->prioridade = prioridade;
    p->carga = carga;
    p->iteracao_inicio = iteracao_inicio;
    p->ultimo_uso = -1;

    return p;
}

char* process_get_nome(Process *p){
    return p->nome;
}

char* process_get_tipo(Process *p){
    return p->tipo;
}

int process_get_prioridade(Process *p){
    return p->prioridade;
}

int process_get_carga(Process *p){
    return p->carga;
}

int process_get_iteracao(Process *p){
    return p->iteracao_inicio;
}

int process_get_ultimo_uso(Process *p){
    return p->ultimo_uso;
}

void process_run(Process *p, int iteracao){
    p->carga--;
    p->ultimo_uso = iteracao;

    // printf("Processo executado: %s %d %d\n\n", p->nome, p->carga, p->ultimo_uso);
}

int process_compare_SO(const void *process1, const void *process2){
    Process *p1 = (Process*) process1;
    Process *p2 = (Process*) process2;

    //em primeiro lugar, por ordem de prioridade (maior);
    if(p1->prioridade < p2->prioridade){
        return -1;
    }

    if(p1->prioridade > p2->prioridade){
        return 1;
    }

    //em segundo lugar, por ordem de carga (menor);
    if(p1->carga > p2->carga){
        return -1;
    }

    if(p1->carga < p2->carga){
        return 1;
    }

    //em terceiro lugar, por ordem alfabética (menor);
    return (-1) * strcmp(p1->nome, p2->nome);

    return 0;
}

int process_compare_USER(const void *process1, const void *process2){
    Process *p1 = (Process*) process1;
    Process *p2 = (Process*) process2;

    //em primeiro lugar, por ordem de prioridade (maior);
    if(p1->prioridade < p2->prioridade){
        return -1;
    }

    if(p1->prioridade > p2->prioridade){
        return 1;
    }

    //em segundo lugar, por ordem de último uso (menor = mais tempo sem usar);
    if(p1->ultimo_uso > p2->ultimo_uso){
        return -1;
    }

    if(p1->ultimo_uso < p2->ultimo_uso){
        return 1;
    }

    //em terceiro lugar, por ordem alfabética (menor);
    return (-1) * strcmp(p1->nome, p2->nome);

    return 0;
}

int process_compare_RT(const void *process1, const void *process2){
    Process *p1 = (Process*) process1;
    Process *p2 = (Process*) process2;

    //compara somente a carga do processo;
    if(p1->carga < p2->carga){
        return -1;
    }

    if(p1->carga > p2->carga){
        return 1;
    }

    return 0;
}

void process_destructor(Process *p){
    // printf("Processo destruído: %s %d\n\n", p->nome, p->ultimo_uso);
    free(p);
}