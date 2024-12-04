#ifndef _PROCESS_H_
#define _PROCESS_H_

#define MAX_NAME_LENGTH 32

typedef struct Process Process;

Process *process_constructor(char *name, char *category, int id, int priority);

int process_compare_priority(const void *process1, const void *process2);

char* process_get_name(Process *p);

char* process_get_category(Process *p);

int process_get_id(Process *p);

int process_get_priority(Process *p);

void process_destructor(Process *p);

#endif