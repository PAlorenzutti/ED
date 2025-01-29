#include "vector.h"

#include <stdio.h>

void print_vector(Vector *v){
  printf("[");
  for(int i = 0; i < v->size; i++){
    if(i != v->size - 1){
      printf("%d, ", v->data[i]);
    }else{
      printf("%d", v->data[i]);
    }
  }
  printf("]\n");
}

int main() {
  int i, m, val;

  Vector *v;

  v = vector_construct();

  scanf("%d", &m);

  for (i = 0; i < m; i++)
  {
      scanf("%d", &val);
      vector_push_back(v, val);
  }

  print_vector(v);

  vector_reverse(v);

  print_vector(v);

  vector_destroy(v);

  return 0;
}