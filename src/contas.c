#include <stdlib.h>
#include "projeto.h"

No * gerarNo(int valor) {
    No *novo = malloc(sizeof(struct No));
    if (!novo) return NULL;

    novo->chave = valor;
    novo->prox = NULL;

    return novo;
}

bool buscarContas(Blockchain *bc, int index) {
    No *atual = bc->contas.lista;
    while (atual) {
        if (atual->chave == index) return true;
        atual = atual->prox;
    }

    return false;
}

int adicionaConta(Blockchain *bc, int idx) {
    No *novo = gerarNo(idx);
    if (!novo) return -1;
    
    novo->prox = bc->contas.lista;
    bc->contas.lista = novo;

    bc->contas.tamanho++;

    return 0;
}
