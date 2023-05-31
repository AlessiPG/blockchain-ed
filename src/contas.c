#include <stdlib.h>
#include "projeto.h"

void inicializaContas(Contas *contas) {
    contas->tamanho = 0;
    contas->lista = NULL;
}

No * gerarNo(unsigned int valor) {
    No *novo = malloc(sizeof(struct No));
    if (!novo) return NULL;

    novo->chave = valor;
    novo->prox = NULL;

    return novo;
}

int adicionaConta(Contas *contas, unsigned int index) {
    No *novo = gerarNo(index);
    if (!novo) return 1;
    
    // Insere no comeco pois a ordem nao importa
    novo->prox = contas->lista;
    contas->lista = novo;

    contas->tamanho++;

    return 0;
}

int copiaContas(Contas orig, Contas *dest) {
    No *atual = orig.lista;
    // Copia cada elemento da origem 1 por 1
    while (atual) {
        if (adicionaConta(dest, atual->chave)) return 1;
        atual = atual->prox;
    }

    return 0;
}

// retorna o index para carteira do n-esimo elemento da lista (n começa em 1)
unsigned int obterIndexDaConta(Contas contas, unsigned int n) {
    if (n > contas.tamanho) return -1;
    No *atual = contas.lista;
    
    for (unsigned int i = 1; i < n && atual; i++) atual = atual->prox;

    return atual->chave;
}

// remove o elemento da lista com chave igual a n
void removeConta(Contas *contas, unsigned int n) {
    No* atual = contas->lista;
    
    // checa se o primeiro elemento ja é o correto
    if (atual->chave == n) {
        contas->lista = atual->prox;
        free(atual);
        return;
    }

    No* ultimo = NULL;
    while (atual) {
        if (atual->chave == n) break;
        ultimo = atual;
        atual = atual->prox;
    }

    if (atual) {
        ultimo->prox = atual->prox;
        free(atual);
    }

    contas->tamanho--;
}

bool buscaConta(Contas contas, unsigned int n) {
    No *atual = contas.lista;
    while (atual) {
        if (atual->chave == n) return true;
        atual = atual->prox;
    }

    return false;
}
