#include <stdio.h>
#include "projeto.h"

void printaCarteira(unsigned int *carteira) {
    for (int i = 0; i < CARTEIRA_TAM - 1; i++) printf("%d-", carteira[i]);
    printf("%d\n\n", carteira[CARTEIRA_TAM - 1]);
}

void printaContas(Clientes clientes) {
    No *atual = clientes.contas.lista;
    
    while(atual) {
        printf("%d:%d\n", atual->chave, clientes.carteira[atual->chave]);
        atual = atual->prox;
    }
}

void printaData(unsigned char *data) {
    for (int i = 0; i < DATA_TAM; i++) printf("%u ", data[i]);
    printf("\n");
}
