#ifndef _PROCESS_H_
#define _PROCESS_H_

#define MAX_NAME_LENGTH 32

typedef struct Process Process;

Process *process_constructor(char *nome, char *tipo, int prioridade, int carga, int iteracao_inicio);

char* process_get_nome(Process *p);

char* process_get_tipo(Process *p);

int process_get_prioridade(Process *p);

int process_get_carga(Process *p);

int process_get_iteracao(Process *p);

int process_get_ultimo_uso(Process *p);

void process_run(Process *p, int iteracao);

int process_compare_SO(const void *process1, const void *process2);

int process_compare_USER(const void *process1, const void *process2);

void process_print(Process *p);

void process_destructor(Process *p);

#endif