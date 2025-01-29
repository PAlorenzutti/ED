#include <stdio.h>
#include <stdlib.h>

void heapify_up(float *array, int i){
    //garante sempre que o índice é válido;
    while(i > 0){
        //pega o índice do pai (inverso do filho da esquerda);
        int pai = (i - 1) / 2;

        //assume o elemento passado como maior;
        float maior = array[i];

        //se o filho for maior do que o pai, troca;
        if(maior > array[pai]){
            float temp = array[pai];
            array[pai] = array[i];
            array[i] = temp;

            i = pai;
        }else{
            break;
        }
    }
}

void heapify_down(float *array, int tamanho, int i){
    while(i < tamanho){
        int maior = i; 

        //pega o índice do filho da esquerda e do filho da direita (direita é sempre maior);
        int esquerda = 2 * i + 1;
        int direita = 2 * i + 2;

        //verifica se o índice é válido e se o filho da esquerda é maior;
        if(esquerda < tamanho && array[esquerda] > array[maior]){
            maior = esquerda;
        }

        //verifica se o índice é válido e se o filho da direita é maior;
        if(direita < tamanho && array[direita] > array[maior]){
            maior = direita;
        }

        //se o maior continuar sendo o atual, o array está heapificado;
        if(maior == i){
            break;
        }else{
            //troca o pai por um dos filhos (esquerda ou direita, dependendo de quem for maior);
            float temp = array[i];
            array[i] = array[maior];
            array[maior] = temp;

            //recebe o antigo índice de um dos antigos filhos e continua a heapify_down;
            i = maior;
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);

    float *arr = (float *)malloc(n * sizeof(float));

    //lê o array
    for (int i = 0; i < n; i++){
        scanf("%f", &arr[i]);
    }

    //organiza o array como um heap
    for (int i = 0; i < n; i++){
        heapify_up(arr, i);
    }

    //ordena o array
    for (int i = 0; i < n; i++){
        //troca ultimo com a raiz
        float temp = arr[0];
        arr[0] = arr[n - i - 1];
        arr[n - i - 1] = temp;

        //heapify a partir da raiz
        heapify_down(arr, n - i - 1, 0);
    }

    //mostra o array "heapificado" na tela
    for (int i = 0; i < n; i++){
        printf("%.2f\n", arr[i]);
    }


    free(arr);
    
    return 0;
}