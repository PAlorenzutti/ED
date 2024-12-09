#include "heap.h"
#include "vector.h"

#include <stdlib.h>

struct Heap
{
    Vector *nodes;
    CmpFn cmp_fn;
};

Heap *heap_constructor(CmpFn cmp_fn){
    Heap *heap = (Heap*)malloc(sizeof(Heap));

    heap->nodes = vector_construct();  
    heap->cmp_fn = cmp_fn;

    return heap;
}

void heap_push(Heap *heap, data_type data){
    //insere ao final do vetor;
    vector_push_back(heap->nodes, data);

    //heapify up para ordenar;
    heap_heapify_up(heap->nodes, heap_size(heap) - 1, heap->cmp_fn);
}

void heap_heapify_up(Vector *nodes, int idx, CmpFn cmp_fn){
    while(idx > 0){
        int pai = (idx - 1) / 2;

        //se o filho for menor ou igual ao pai, o tronco está ordenado;
        if(cmp_fn(vector_get(nodes, idx), vector_get(nodes, pai)) < 0){
            break;
        }

        //caso contrário, troca o filho com o pai;
        vector_swap(nodes, idx, pai);
        idx = pai;
    }
}

int heap_empty(Heap *heap){
    if(!heap_size(heap)){
        return 1;
    }else{
        return 0;
    }
}

int heap_size(Heap *heap){
    return vector_size(heap->nodes);
}

data_type heap_max(Heap *heap){
    //retorna o primeiro elemento do vetor, ou seja, a raiz (para caso de heap max);
    return vector_get(heap->nodes, 0);
}

data_type heap_pop(Heap *heap){
    //troca a raiz (max) com o último elemento do vetor;
    vector_swap(heap->nodes, 0, heap_size(heap) - 1);

    //remove o último elemento do vetor, a antiga raiz;
    data_type data = vector_remove(heap->nodes, heap_size(heap) - 1);

    //faz o heapify down com o primeiro elemento do vetor;
    heap_heapify_down(heap->nodes, heap_size(heap), 0, heap->cmp_fn);

    //retorna data que foi retirado;
    return data;
}

void heap_heapify_down(Vector *nodes, int size, int idx, CmpFn cmp_fn){
    while(idx < size){
        //descobre os filhos do atual;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        //assume que o maior é atual;
        int maior = idx; 

        //verifica se o idx do filho da esquerda é válido;
        if(left < size){
            //verifica se o filho da esquerda é maior do que o pai;
            if(cmp_fn(vector_get(nodes, maior), vector_get(nodes, left)) < 0){
                maior = left;
            }
        }

        //verifica se o idx do filho da direita é válido;
        if(right < size){
            //verifica se o filho da direita é maior do que o pai;
            if(cmp_fn(vector_get(nodes, maior), vector_get(nodes, right)) < 0){ 
                maior = right;
            }
        }

        //se o maior continua sendo o index do pai, sai;
        if(maior == idx){
            break;
        }

        //se não saiu, troca o pai com o maior filho;
        vector_swap(nodes, idx, maior);
        idx = maior;
    }
}

void heap_destroy(Heap *heap){
    vector_destroy(heap->nodes);
    free(heap);
}

data_type heap_get(Heap *heap, int idx){
    return vector_get(heap->nodes, idx);
}

//heapificar vetor não ordenado com qualquer função de comparação
void heap_sort(Vector *v, int cmp_fn(const void *, const void *)){
    //algoritmo heapify vector
    for(int i = (vector_size(v) / 2) - 1; i >= 0; i--){
        heap_heapify_down(v, vector_size(v), i, cmp_fn);
    }

    //ordenar o vetor heapificando ele
    for(int i = vector_size(v) - 1; i > 0; i--){
        //troca a raiz (maior elemento) com o último elemento;
        vector_swap(v, 0, i);

        //reduz o tamanho da heap, pois o último já está no lugar certo;
        heap_heapify_down(v, i, 0, cmp_fn);
    }
}