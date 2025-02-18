
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"

int main()
{
    int n;
    scanf("%d\n", &n);

    Queue *q = queue_construct();

    for(int i = 0; i < n; i++){
        char comando[32];
        scanf("%s", comando);

        if(!strcmp(comando, "ENQUEUE")){
            char *string = (char*)malloc(sizeof(char) * 32);
            scanf(" %s\n", string);

            queue_enqueue(q, string);
        }

        if(!strcmp(comando, "DEQUEUE")){
            char *string = (char*)queue_dequeue(q);

            printf("%s\n", string);

            free(string);
        }
    }

    if(queue_size(q) > 0){
        while(queue_empty(q) < 1){
            char *string = (char*)queue_dequeue(q);
            free(string);
        }
    }

    queue_destroy(q);

    return 0;
}