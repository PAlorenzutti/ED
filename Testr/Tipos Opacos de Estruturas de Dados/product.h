#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#define MAX_NAME_LENGTH 64

typedef struct product Product;

Product *product_constructor(const char *name, float price, int qtd);

void product_destructor(Product *product);

const char *product_get_name(Product *product);

float product_get_price(Product *product);

float product_get_discount(Product *product);

int product_get_qtd(Product *product);

int product_get_sales(Product *product);

void product_set_name(Product *product, const char *name);

void product_set_price(Product *product, float price);

void product_set_discount(Product *product, float discount);

void product_sell(Product *product, int qtd);

void product_buy(Product *product, int qtd);

float product_get_price_with_discount(Product *product);

int product_compare_name(const void *product1, const void *product2);

int product_compare_price(const void *product1, const void *product2);

int product_compare_sales(const void *product1, const void *product2);

void product_print(Product *product);

#endif