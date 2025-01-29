#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_FILA 10

typedef struct{
    char nome[64];
    char cpf[64];
}Atendimento;

void chama_fila(Atendimento *fila, int *size, int *inicio_fila){
    if(*size > 0){
        //printa a primeira pessoa da fila;
        printf("%s\n", fila[*inicio_fila].nome);

        //incrementa o início da fila, de acordo com o array circular;
        *inicio_fila = (*inicio_fila + 1) % TAM_FILA;

        //diminui o tamanho do vetor;
        (*size)--;
    }else{
        printf("FILA VAZIA\n");
    }
}

void adiciona_fila(Atendimento *fila, Atendimento pessoa, int *size, int *final_fila){
    if(*size == TAM_FILA){
        printf("FILA CHEIA\n");
    }else{
        //insere a pessoa no final da fila;
        fila[*final_fila] = pessoa;

        //incrementa a posição final;
        (*final_fila) = (*final_fila + 1) % TAM_FILA;

        //aumenta o tamanho do vetor;
        (*size)++;
    }
}

void perform_fila(Atendimento *fila, int *size, int *inicio_fila, int *final_fila){
    char opcao[16];
    scanf("%s ", opcao);

    if(strcmp(opcao, "CHAMAR") == 0){
        chama_fila(fila, size, inicio_fila);
    }

    if(strcmp(opcao, "ADICIONAR") == 0){
        Atendimento pessoa;
        scanf("%s %s\n", pessoa.nome, pessoa.cpf);

        adiciona_fila(fila, pessoa, size, final_fila);
    }
}

int main(){
    int N;
    scanf("%d\n", &N);

    //estrutura do deque;
    Atendimento fila[TAM_FILA];
    int size = 0;
    int inicio_fila = 0;
    int final_fila = 0;

    for(int i = 0; i < N; i++){
        perform_fila(fila, &size, &inicio_fila, &final_fila);
    }
}