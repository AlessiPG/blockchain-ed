#include <stdlib.h>
#include "projeto.h"

void inicializaContas(Contas *contas) {
    contas->tamanho = 0;
    contas->lista = NULL;
}

No * gerarNo(int valor) {
    No *novo = malloc(sizeof(struct No));
    if (!novo) return NULL;

    novo->chave = valor;
    novo->prox = NULL;

    return novo;
}

int adicionaConta(Contas *contas, int idx) {
    No *novo = gerarNo(idx);
    if (!novo) return 1;
    
    // Insere no comeco pois a ordem nao importa
    novo->prox = contas->lista;
    contas->lista = novo;

    contas->tamanho++;

    return 0;
}

int copiaContas(Contas orig, Contas *dest) {
    printaContas(*dest);
    dest->tamanho = orig.tamanho;
    
    No *atual = orig.lista;
    // Copia cada elemento da origem 1 por 1
    while (atual) {
        if (adicionaConta(dest, atual->chave)) return 1;
        atual = atual->prox;
    }

    return 0;
}

bool buscarContas(Blockchain *bc, int index) {
    No *atual = bc->clientes.contas.lista;
    while (atual) {
        if (atual->chave == index) return true;
        atual = atual->prox;
    }

    return false;
}
