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
    No *atual = bc->clientes.contas.lista;
    while (atual) {
        if (atual->chave == index) return true;
        atual = atual->prox;
    }

    return false;
}

int adicionaConta(Contas *cnts, int idx) {
    No *novo = gerarNo(idx);
    if (!novo) return -1;
    
    // Insere no comeco pois a ordem nao importa
    novo->prox = cnts->lista;
    cnts->lista = novo;

    cnts->tamanho++;

    return 0;
}

Contas copiaListaContas(Contas velho) {
    Contas nova = { 
        .tamanho = velho.tamanho
    };
    
    No *atual = velho.lista;
    // Copia cada elemento da lista velha 1 por 1
    while (atual) {
        adicionaConta(&nova, atual->chave);
        atual = atual->prox;
    }

    return nova;
}
