#include <stdio.h>
#include "projeto.h"

void printaCarteira(unsigned int *carteira) {
    for (int i = 0; i < CARTEIRA_TAM - 1; i++) printf("%d-", carteira[i]);
    printf("%d\n\n", carteira[CARTEIRA_TAM - 1]);
}

void printaContas(Contas contas) {
    No *atual = contas.lista;
    
    while(atual) {
        printf("%d\n", atual->chave);
        atual = atual->prox;
    }
}
