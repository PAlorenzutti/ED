#include "product.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product {
  char name[MAX_NAME_LENGTH];
  float price;
  float discount;
  int qtd;
  int sales;
};

Product *product_constructor(const char *name, float price, int qtd) {
  Product *product = malloc(sizeof(Product));

  strncpy(product->name, name, MAX_NAME_LENGTH);
  product->name[MAX_NAME_LENGTH - 1] = '\0';

  product->price = price;
  product->qtd = qtd;

  product->discount = 0.0;
  product->sales = 0;

  if (product->price < 0 || product->qtd < 0) {
    free(product);
    printf("VALOR INVALIDO\n");
    return NULL;
  }

  return product;
}

const char *product_get_name(Product *product) { return product->name; }

float product_get_price(Product *product) { return product->price; }

float product_get_discount(Product *product) { return product->discount; }

int product_get_qtd(Product *product) { return product->qtd; }

int product_get_sales(Product *product) { return product->sales; }

void product_set_name(Product *product, const char *name) {
  strncpy(product->name, name, MAX_NAME_LENGTH);
  product->name[MAX_NAME_LENGTH - 1] = '\0';
}

void product_set_price(Product *product, float price) {
  if (price < 0) {
    printf("VALOR INVALIDO\n");
  } else {
    product->price = price;
  }
}

void product_set_discount(Product *product, float discount) {
  if (discount < 0 || discount > 1) {
    printf("VALOR INVALIDO\n");
  } else {
    product->discount = discount;
  }
}

void product_sell(Product *product, int qtd) {
  if (qtd < 0) {
    printf("QUANTIDADE INVALIDA\n");
  }

  if (product->qtd - qtd >= 0 && qtd > 0) {
    product->qtd -= qtd;
    product->sales += qtd;
  } else {
    printf("ESTOQUE INSUFICIENTE\n");
  }
}

void product_buy(Product *product, int qtd) {
  if (qtd < 0) {
    printf("QUANTIDADE INVALIDA");
  } else {
    product->qtd += qtd;
  }
}

float product_get_price_with_discount(Product *product) {
  return product->price - (product->price * product->discount);
}

void product_print(Product *product) {
  printf("Product(%s, %.2f, %.2f, %.2f, %d, %d)\n", product_get_name(product), product->price, product->discount, product_get_price_with_discount(product), product->qtd, product->sales);
}

int product_compare_name(const void *product1, const void *product2){
  Product *p1 = (Product*) product1;
  Product *p2 = (Product*) product2;

  return strcmp(p1->name, p2->name);
}

int product_compare_price(const void *product1, const void *product2){
  Product *p1 = (Product*) product1;
  Product *p2 = (Product*) product2;

  if(p1->price > p2->price){
    return 1;
  }

  if(p1->price < p2->price){
    return -1;
  }

  return 0;
}

int product_compare_sales(const void *product1, const void *product2){
  Product *p1 = (Product*) product1;
  Product *p2 = (Product*) product2;

  if(p1->sales > p2->sales){
    return 1;
  }

  if(p1->sales < p2->sales){
    return -1;
  }

  return 0;
}

void product_destructor(Product *product) { free(product); }
