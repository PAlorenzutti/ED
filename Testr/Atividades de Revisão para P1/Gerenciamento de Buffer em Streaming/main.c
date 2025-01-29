#include <stdio.h>
#include <string.h>

#define TAM_BUFFER 20

typedef struct{
    char link[50];
    int id;
    float timestamp;
}Frame;

void adiciona_buffer(Frame *buffer, Frame f, int *size, int *final_buffer){
    if(*size < TAM_BUFFER){
        //adiciona o frame ao final do buffer;
        buffer[*final_buffer] = f;

        //aumenta o tamanho do buffer;
        (*size)++;

        //atualiza o final do buffer;
        (*final_buffer) = (*final_buffer + 1) % TAM_BUFFER;
    }else{
        printf("FILA CHEIA\n");
    }
}

void play_buffer(Frame *buffer, int *size, int *inicio_buffer){
    if(*size < 5){
        printf("AGUARDE\n");
    }else{
        //retira 5 frames do buffer
        for(int i = 0; i < 5; i++){
            //retira o frame do início do buffer;
            printf("ID: %d, Timestamp: %.2f\n", buffer[*inicio_buffer].id, buffer[*inicio_buffer].timestamp);

            //diminui o tamanho do buffer;
            (*size)--;

            //atualiza o início do buffer;
            (*inicio_buffer) = (*inicio_buffer + 1) % TAM_BUFFER;
        }
    }
}

void perform_buffer(Frame *buffer, int *size, int *inicio_buffer, int *final_buffer){
    char opcao[32];
    scanf("%s", opcao);

    if(strcmp(opcao, "ADICIONAR") == 0){
        //leitura do buffer;
        Frame f;
        scanf(" %s %d %f\n", f.link, &f.id, &f.timestamp);
    
        adiciona_buffer(buffer, f, size, final_buffer);
    }

    if(!strcmp(opcao, "PLAY")){
        play_buffer(buffer, size, inicio_buffer);
    }
}

int main(){
    int N;
    scanf("%d\n", &N);

    Frame buffer[TAM_BUFFER];
    int size = 0;
    int inicio_buffer = 0;
    int final_buffer = 0;

    for(int i = 0; i < N; i++){
        perform_buffer(buffer, &size, &inicio_buffer, &final_buffer);
    }

    return 0;
}