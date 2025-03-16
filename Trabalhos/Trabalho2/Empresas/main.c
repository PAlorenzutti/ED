#include "empresa.h"
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    //leitura do arquivo;
    char filename[100];
    scanf("%99s", filename);

    FILE *file = fopen(filename, "r");

    int n;
    fscanf(file, "%d", &n);

    Vector *empresas = vector_construct();

    for (int i = 0; i < n; i++) {
        char nome[MAX_NAME_LENGTH];
        char sigla[MAX_SIGLA_LENGTH];
        float valor_unitario;
        int total_acoes, acoes_vendidas;

        fscanf(file, "%s %s %f %d %d", nome, sigla, &valor_unitario, &total_acoes, &acoes_vendidas);

        Empresa *e = empresa_construct(nome, sigla, valor_unitario, total_acoes, acoes_vendidas);
        vector_push_back(empresas, e);
    }

    fclose(file);

    for (int i = 0; i < vector_size(empresas); i++) {
        Empresa *e = (Empresa *)vector_get(empresas, i);
        print_empresa(e);
    }

    for (int i = 0; i < vector_size(empresas); i++) {
        Empresa *e = (Empresa *)vector_get(empresas, i);
        empresa_destroy(e);
    }

    vector_destroy(empresas);

    return 0;
}