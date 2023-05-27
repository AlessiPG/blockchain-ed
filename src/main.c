#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/crypto.h" //arquivo de definição necessário para SHA256_DIGEST_LENGTH
#include "openssl/sha.h"    //arquivo de definição necessário função SHA256
#include "mtwister.h"
#include "projeto.h"

int main()
{
    int i;
    MTRand r = seedRand(1234567);

    unsigned int carteira[256];

    Blockchain blockchain;
    inicializaBlockchain(&blockchain, &r);

    for (i = 0; i < 256; ++i)
        carteira[i] = 0;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    memcpy(hash, blockchain.inicio->hash, SHA256_DIGEST_LENGTH);

    for (i = 1; i < TOTAL_BLOCOS; ++i)
        processaBloco(&blockchain, &r, i + 1, hash);

    BlocoMinerado *aux = blockchain.inicio;

    while (aux != NULL)
    {
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

        aux = aux->prox;
    }
}
