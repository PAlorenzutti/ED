#include "vector.h"
#include "priority_queue_vector.h"
#include "process.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void perform_read(PriorityQueue *pq){
    char *name = (char*)malloc(sizeof(char) * MAX_NAME_LENGTH);
    char *category = (char*)malloc(sizeof(char) * MAX_NAME_LENGTH);
    int id;
    int priority;

    scanf("%s %s %d %d\n", name, category, &id, &priority);
    
    Process *p = process_constructor(name, category, id, priority);

    pq_push(pq, p);
}

void perform_processes(PriorityQueue *pq, int n){
    for(int i = 0; i < n; i++){
        data_type data = pq_pop(pq);
        
        Process *p = (Process*) data;

        printf("%s %s %d %d\n", process_get_name(p), process_get_category(p), process_get_id(p), process_get_priority(p));

        process_destructor(p);
    }
}

int main(){
    PriorityQueue *pq = pq_constructor(process_compare_priority);

    int n;
    scanf("%d\n", &n);

    for(int i = 0; i < n; i++){
        perform_read(pq);
    }

    perform_processes(pq, n);

    pq_destroy(pq);
}