#include <stdlib.h>
#include "projeto.h"

No *gerarNo(unsigned int valor)
{
    No *novo = malloc(sizeof(struct No));
    if (!novo)
        return NULL;

    novo->chave = valor;
    novo->prox = NULL;

    return novo;
}

No *adicionaNo(No *lista, unsigned int n)
{
    No *novo = gerarNo(n);
    if (!novo)
        return NULL;

    novo->prox = lista;

    return novo;
}

void freeEmLista(No *lista)
{
    No *atual;

    while (lista)
    {
        atual = lista;
        lista = lista->prox;
        free(atual);
        atual = NULL;
    }
}
