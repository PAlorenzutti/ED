#include "process.h"

#include <string.h>
#include <stdlib.h>

struct Process{
    char name[MAX_NAME_LENGTH];
    char category[MAX_NAME_LENGTH];
    int id;
    int priority;
};

Process *process_constructor(char *name, char *category, int id, int priority){
    Process *p = (Process*)malloc(sizeof(Process));
    
    strncpy(p->name, name, MAX_NAME_LENGTH);
    p->name[MAX_NAME_LENGTH - 1] = '\0';

    strncpy(p->category, category, MAX_NAME_LENGTH);
    p->category[MAX_NAME_LENGTH - 1] = '\0';

    p->id = id;
    p->priority = priority;

    return p;
}

char* process_get_name(Process *p){
    return p->name;
}

char* process_get_category(Process *p){
    return p->category;
}

int process_get_id(Process *p){
    return p->id;
}

int process_get_priority(Process *p){
    return p->priority;
}

int process_compare_priority(const void *process1, const void *process2){
    Process *p1 = (Process*) process1;
    Process *p2 = (Process*) process2;

    if(p1->priority < p2->priority){
        return -1;
    }

    if(p1->priority > p2->priority){
        return 1;
    }

    return 0;
}

void process_destructor(Process *p){
    free(p);
}