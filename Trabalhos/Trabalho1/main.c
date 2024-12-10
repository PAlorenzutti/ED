#include "heap.h"
#include "process.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void perform_read(Heap *heap){
    char name[32];
    char category[32];
    int id;
    int priority;

    scanf("%s %s %d %d\n", name, category, &id, &priority);
    
    Process *p = process_constructor(name, category, id, priority);

    heap_push(heap, p);
}

void perform_processes(Heap *heap, int n){
    for(int i = 0; i < n; i++){
        data_type data = heap_get(heap, i);
        
        Process *p = (Process*) data;

        printf("%s %s %d %d\n", process_get_name(p), process_get_category(p), process_get_id(p), process_get_priority(p));
    }
}

int main(){
    Heap* heap = heap_constructor(process_compare_priority);

    int n;
    scanf("%d\n", &n);

    for(int i = 0; i < n; i++){
        perform_read(heap);
    }

    perform_processes(heap, n);

    heap_destroy(heap);
}