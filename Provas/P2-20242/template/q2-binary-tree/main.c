#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"


int main()
{
    int n, value, x, k, min, max;

    BinaryTree *bt = binary_tree_construct();

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &value);
        binary_tree_add(bt, value);
    }

    scanf("%d %d %d %d", &x, &k, &min, &max);

    int out_size;
    int *out_array;

    out_array = binary_tree_knn(bt, x, k, min, max, &out_size);

    for (int i = 0; i < out_size; i++)
        printf("%d\n", out_array[i]);

    free(out_array);
    binary_tree_destroy(bt);
    return 0;
}
