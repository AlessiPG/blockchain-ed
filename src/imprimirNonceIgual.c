#include <stdlib.h>
#include "projeto.h"
#include <stdio.h>

void imprimirNonceIgual(Blockchain *blockchain, unsigned int n){
    int i;
    BlocoMinerado *aux = blockchain->inicio;
    printf("=======================================\n");
    printf("Impressao de blocos com nonce = %d\n",n);
    printf("=======================================\n");
    while (aux != NULL)
    {
        if(aux->bloco.nonce == n){
            printf("Numero do bloco: %d\n", aux->bloco.numero);
            printf("Nonce: %d\n", aux->bloco.nonce);
            printf("Data: ");
            for (i = 0; i < 184; i++)
                printf("%d", aux->bloco.data[i]);
            printf("\n");
            printf("Hash anterior: ");
            for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
                printf("%02x", aux->bloco.hashAnterior[i]);
            printf("\n");
            printf("Hash atual: ");
            for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
                printf("%02x", aux->hash[i]);
            printf("\n");
            printf("=======================================================\n");
        }
        aux = aux->prox;
        
    }
}