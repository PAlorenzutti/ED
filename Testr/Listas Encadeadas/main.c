
#include <stdio.h>

#include "forward_list.h"

void print_int(int data)
{
    printf("%d", data);
}

int main()
{
    int n, m, val;

    ForwardList *l = forward_list_construct();

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        forward_list_push_front(l, val);
    }

    scanf("%d", &m);

    for(int i = 0; i < m; i++){
        scanf("%d", &val);
        forward_list_remove(l, val);
    }

    //printa a lista
    forward_list_print(l, print_int);

    // test the destroy function
    forward_list_destroy(l);

    return 0;
}