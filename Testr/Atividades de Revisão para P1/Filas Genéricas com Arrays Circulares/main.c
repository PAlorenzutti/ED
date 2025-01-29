#include <stdio.h>
#include <string.h>

#include "queue.h"
#include "atendimento.h"
#include "frame.h"

void perform_senhas(Queue *queue){
    char nome[50];
    char cpf[12];

    char opcao[32];
    scanf("%s", opcao);

    if(strcmp(opcao, "ADICIONAR") == 0){
        //lê o nome e o cpf;
        scanf(" %s %s\n", nome, cpf);

        if(queue_is_full(queue) == 1){
            printf("FILA CHEIA\n");
        }else{
            //cria a pessoa no atendimento;
            Atendimento *pessoa = atendimento_constructor(nome, cpf);   

            //adiciona a pessoa na fila;
            queue_add(queue, pessoa);
        }
    }

    if(strcmp(opcao, "CHAMAR") == 0){
        if(queue_is_empty(queue)){
            printf("FILA VAZIA\n");
        }else{
            //remove a pessoa da fila;
            Atendimento *pessoa = (Atendimento*) queue_remove(queue);

            //printa o nome;
            printf("%s\n", atendimento_get_nome(pessoa));

            //desaloca o espaço que a pessoa ocupa;
            atendimento_destroy(pessoa);
        }
    }
}

void executa_senhas(int N){
    Queue *queue = queue_constructor(10);
    
    for(int i = 0; i < N; i++){
        perform_senhas(queue);
    }

    queue_destroy(queue);
}

void perform_streaming(Queue *queue){
    char video_id[50];
    int frame_id;
    float timestamp;

    char opcao[32]; 
    scanf("%s", opcao);

    if(strcmp(opcao, "ADICIONAR") == 0){
        //lê o vídeo;
        scanf("%s %d %f\n", video_id, &frame_id, &timestamp);

        if(queue_is_full(queue) == 1){
            printf("FILA CHEIA\n");
        }else{
            //cria o buffer;
            Frame *frame = frame_constructor(video_id, frame_id, timestamp);

            //adiciona o buffer na fila;
            queue_add(queue, frame);
        }
    }

    if(strcmp(opcao, "PLAY") == 0){
        if(queue_size(queue) < 5){
            printf("AGUARDE\n");
        }else{
            //remove 5 frames da lista;
            for(int i = 0; i < 5; i++){
                //remove o frame
                Frame *frame = (Frame*) queue_remove(queue);

                //printa o frame;
                printf("ID: %d, Timestamp: %.2f\n", frame_get_frame_id(frame), frame_get_timestamp(frame));

                //destrói o frame;
                frame_destroy(frame);
            }
        }
    }
}

void executa_streaming(int N){
    Queue *queue = queue_constructor(20);

    for(int i = 0; i < N; i++){
        perform_streaming(queue);
    }

    queue_destroy(queue);
}

int main(){
    char opcao[32];
    scanf("%s\n", opcao);

    int N;
    scanf("%d\n", &N);

    if(strcmp(opcao, "SENHAS") == 0){
        executa_senhas(N);
    }

    if(strcmp(opcao, "STREAMING") == 0){
        executa_streaming(N);
    }
    
    return 0;
}