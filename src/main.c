#include <stdio.h>
#include <stdlib.h>
#include "openssl/crypto.h" //arquivo de definição necessário para SHA256_DIGEST_LENGTH
#include "openssl/sha.h" //arquivo de definição necessário função SHA256
#include "mtwister.h"
#include "projeto.h"


int main() {
    int i;
    MTRand r = seedRand(1234567);
    BlocoMinerado *blockchain = NULL;
    unsigned int carteira[256];
    
    for(i=0; i<256; ++i)
    carteira[i] = 0;

    BlocoNaoMinerado *genesis = inicializaGenesis();
    blockchain = minerarGenesis(genesis, &r);

    printf("Bloco numero = %d\n",blockchain->bloco.numero);
    printf("nonce = %d\n",blockchain->bloco.nonce);
    printf("Hash anterior = ");
    for(i = 0; i< SHA256_DIGEST_LENGTH; i++)
        printf("%02x",blockchain->bloco.hashAnterior[i]);
    printf("\n");
    printf("Hash atual = ");
    for(i = 0; i< SHA256_DIGEST_LENGTH; i++)
        printf("%02x",blockchain->hash[i]);
    printf("\nMinerador = %d\n",blockchain->bloco.data[183]);
    printf("%d\n", genRandLong(&r)%256);
    for(i = 0;i < TOTAL_BLOCOS; ++i) {
    
    }

}
