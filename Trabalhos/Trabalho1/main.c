#include "vector.h"
#include "deque.h"
#include "heap.h"
#include "process.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void perform_read(Vector *programas){
    char nome[MAX_NAME_LENGTH];
    char tipo[MAX_NAME_LENGTH];
    int prioridade;
    int carga;
    int iteracao_inicio;

    scanf("%s %s %d %d %d\n", nome, tipo, &prioridade, &carga, &iteracao_inicio);
    
    Process *p = process_constructor(nome, tipo, prioridade, carga, iteracao_inicio);

    vector_push_back(programas, p);
}

void search_programs(Vector *programas, Deque *RT, Heap *SO, Heap *USER, int iteracao){
    for(int i = 0; i < vector_size(programas); i++){
        //pega o programa;
        Process *p = (Process*)vector_get(programas, i);

        //se o tipo do programa for igual a RT, verifica se a iteração dele é a atual;
        if(!strcmp(process_get_tipo(p), "RT")){
            //se for, sai do vetor de programas e entra no deque RT;
            if(process_get_iteracao(p) == iteracao){
                //insere na última posição, sem ordenar;
                deque_push_back(RT, vector_remove(programas, i));
                i--;
            }
        }

        //se o tipo do programa for igual a SO, verifica se a iteração dele é a atual;
        if(!strcmp(process_get_tipo(p), "SO")){
            //se for, sai do vetor de programas e entra na heap SO;
            if(process_get_iteracao(p) == iteracao){
                //insere na última posição e ordena de acordo com a prioridade;
                heap_push(SO, vector_remove(programas, i));
                i--;
            }
        }

        //se o tipo de programa for igual a USER, verifica se a iteração dele é a atual;
        if(!strcmp(process_get_tipo(p), "USER")){
            //se for, sai do vetor de programas e entra na heap
            if(process_get_iteracao(p) == iteracao){
                //insere na última e ordena de acordo com a prioridade;
                heap_push(USER, vector_remove(programas, i));
                i--;
            }
        }
    }

    //printa programas restantes dentro de vector;
    printf("-------------------------------------------------------\n");
    printf("Programas restantes no vector depois do search:\n\n");

    for(int i = 0; i < vector_size(programas); i++){
        Process *p = (Process*)vector_get(programas, i);

        printf("%s %s %d %d %d | %d\n", process_get_nome(p), process_get_tipo(p), process_get_prioridade(p), process_get_carga(p), process_get_iteracao(p), process_get_ultimo_uso(p));
    }

    printf("-------------------------------------------------------\n");

    //printa programas da fila de RT;
    printf("-------------------------------------------------------\n");
    printf("Programas no RT atualizado:\n\n");

    for(int i = 0; i < deque_size(RT); i++){
        Process *p = (Process*)deque_get(RT, i);

        printf("%s %s %d %d %d | %d\n", process_get_nome(p), process_get_tipo(p), process_get_prioridade(p), process_get_carga(p), process_get_iteracao(p), process_get_ultimo_uso(p));    }

    printf("-------------------------------------------------------\n");

    //printa programas da fila de SO;
    printf("-------------------------------------------------------\n");
    printf("Programas no SO atualizado:\n\n");

    for(int i = 0; i < heap_size(SO); i++){
        Process *p = (Process*)heap_get(SO, i);

        printf("%s %s %d %d %d | %d\n", process_get_nome(p), process_get_tipo(p), process_get_prioridade(p), process_get_carga(p), process_get_iteracao(p), process_get_ultimo_uso(p));    }

    printf("-------------------------------------------------------\n");

    //printa programas da fila de USER;
    printf("-------------------------------------------------------\n");
    printf("Programas no USER atualizado:\n\n");

    for(int i = 0; i < heap_size(USER); i++){
        Process *p = (Process*)heap_get(USER, i);

        printf("%s %s %d %d %d | %d\n", process_get_nome(p), process_get_tipo(p), process_get_prioridade(p), process_get_carga(p), process_get_iteracao(p), process_get_ultimo_uso(p));    }

    printf("-------------------------------------------------------\n");
}

void run_RT(Deque *RT, int iteracao){
    //retira o primeiro processo da fila;
    Process *p = (Process*) deque_pop_front(RT);

    //decrementa a carga do processo e atualiza último uso;
    process_run(p, iteracao);

    //se a carga for igual a 0, printa o programa e destrói ele;
    if(!process_get_carga(p)){
        //printa o programa e a iteração atual;
        printf("%s %d\n", process_get_nome(p), iteracao);

        //libera o processo;
        process_destructor(p);
    }else{
        //insere novamente na fila, na primeira posição;
        deque_push_back(RT, p);
    }
}

//roda tanto programa de SO, quanto de USER, pois são ambos heap;
void run_SO_USER(Heap *heap, int iteracao){
    //retira o processo com maior prioridade;
    Process *p = (Process*) heap_pop(heap);

    //decrementa a carga do processo e atualiza último uso;
    process_run(p, iteracao);

    //se a carga for igual a 0, printa o programa e destrói ele;
    if(!process_get_carga(p)){
        //printa o programa e a iteração atual;
        printf("%s %d\n", process_get_nome(p), iteracao);

        //libera o processo;
        process_destructor(p);
    }else{
        //insere o programa novamente na heap;
        heap_push(heap, p);
    }
}

void perform_processes(Vector *programas){
    //filas para cada tipo de programa;
    Deque *RT = deque_construct();
    Heap *SO = heap_constructor(process_compare_SO);
    Heap *USER = heap_constructor(process_compare_USER);

    //printa o vetor de programas antes de iniciar o processador;
    printf("-------------------------------------------------------\n");
    printf("Programas inseridos no vector:\n\n");

    for(int i = 0; i < vector_size(programas); i++){
        Process *p = (Process*)vector_get(programas, i);

        printf("%s %s %d %d %d | %d\n", process_get_nome(p), process_get_tipo(p), process_get_prioridade(p), process_get_carga(p), process_get_iteracao(p), process_get_ultimo_uso(p));    }

    printf("-------------------------------------------------------\n");

    //inicia prioridade de programa como SO, caso RT esteja vazio;
    char flag[MAX_NAME_LENGTH] = "SO";

    //inicia iteração do processador como 0;
    int iteracao = 0;
    
    while(true){
        printf("\n\nIteração %d\n\n", iteracao);
        
        //se o tamanho do vetor de programas for diferente de 0, busca programas que se iniciam na iteracao atual e os colocam nas respectivas filas (atualiza filas);
        if(vector_size(programas) > 0){
            search_programs(programas, RT, SO, USER, iteracao);
        }


        //se todas as filas estiverem vazias, sai;
        if(deque_size(RT) == 0 && heap_size(SO) == 0 && heap_size(USER) == 0){
            break;
        }

        //flag de programa executado ou não;
        int execute = 0;

        //se ainda tiver programas de RT, executa;
        if(deque_size(RT) > 0){
            //executa o processo de RT;
            run_RT(RT, iteracao);

            execute = 1;
        }

        //se for a vez de SO e tiver algum programa;
        if(strcmp(flag, "SO") == 0 && heap_size(SO) > 0 && execute == 0){
            //executa o processo de SO;
            run_SO_USER(SO, iteracao);

            //troca a flag para USER ser executado na próxima iteração
            strcpy(flag, "USER");

            execute = 1;
        }

        if(execute == 0){
            strcpy(flag, "USER");
        }

        //se for a vez de USER e tiver algum programa;
        if(strcmp(flag, "USER") == 0 && heap_size(USER) > 0 && execute == 0){
            //executa o processo de USER;
            run_SO_USER(USER, iteracao);

            //troca a flag para SO ser executado na próxima iteração
            strcpy(flag, "SO");

            execute = 1;
        }

        iteracao++;
    }

    //desaloca todas as filas;
    deque_destroy(RT);
    heap_destroy(SO);
    heap_destroy(USER);
}

int main(){
    //vetor de programas;
    Vector *programas = vector_construct();

    int N;
    scanf("%d\n", &N);

    for(int i = 0; i < N; i++){
        perform_read(programas);
    }

    perform_processes(programas);

    vector_destroy(programas);
}