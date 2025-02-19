
#include <stdio.h>

#include "forward_list.h"

int main()
{
    int n, val;

    ForwardList *l = forward_list_construct();

    // fill the list by adding values to the end
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        forward_list_push_front(l, val);
    }

    // uses the back iterator to double the values
    ListIterator *it = list_iterator_construct(l);

    while (!list_iterator_is_over(it))
    {
        data_type *value = list_iterator_next(it);
        //fazer o cast, pois data_type está tipo void*
        *value *= 2;
        printf("%d\n", *value);
    }

    list_iterator_destroy(it);

    // test the destroy function
    forward_list_destroy(l);

    return 0;
}
