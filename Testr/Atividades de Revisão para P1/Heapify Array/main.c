#include <stdio.h>
#include <stdlib.h>

void heapify_up(float *array, int i){
    //garante sempre que o índice é válido;
    while(i > 0){
        //pega o índice do pai;
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

    //mostra o array "heapificado" na tela
    for (int i = 0; i < n; i++){
        printf("%.2f\n", arr[i]);
    }

    //libera o array;
    free(arr);

    return 0;
}