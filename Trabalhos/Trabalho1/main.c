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
}

void run_RT(Deque *RT, int iteracao){
    //retira o primeiro processo da fila;
    Process *p = (Process*) deque_pop_back(RT);

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
        deque_push_front(RT, p);
    }
}

void perform_processes(Vector *programas){
    //filas para cada tipo de programa;
    Deque *RT = deque_construct();
    Heap *SO = heap_constructor(process_compare_SO);
    Heap *USER = heap_constructor(process_compare_USER);

    //inicia prioridade de programa como SO, caso RT esteja vazio;
    char flag[MAX_NAME_LENGTH] = "SO";

    //inicia iteração do processador como 0;
    int iteracao = 0;
    
    while(true){
        //se o tamanho do vetor de programas for diferente de 0, busca programas que se iniciam na iteracao atual e os colocam nas respectivas filas (atualiza filas);
        if(!vector_size(programas)){
            search_programs(programas, RT, SO, USER, iteracao);
        }

        //se todas as filas estiverem vazias, sai;
        if(!deque_size(RT) && !heap_size(SO) && !heap_size(USER)){
            break;
        }

        //se ainda tiver programas de RT, executa;
        if(!deque_size(RT)){
            //executa o processo de RT;
            run_RT(RT, iteracao);

            iteracao++;
            continue;
        }

        //muda a flag de acordo com o último programa executado;

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