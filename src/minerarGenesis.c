#include <stdlib.h>
#include <string.h>
#include "openssl/crypto.h" //arquivo de definição necessário para SHA256_DIGEST_LENGTH
#include "openssl/sha.h" //arquivo de definição necessário função SHA256
#include "projeto.h"

BlocoMinerado *minerarGenesis(BlocoNaoMinerado *bloco, MTRand *r){
    //escolhe o minerador
    bloco->data[183] = genRandLong(r)%256;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    do
    {
        SHA256((unsigned char*)bloco, sizeof(bloco), hash);
        if(hash[0] == 0) break;//se nonce = 0 for o hash válido, para a execução antes que altere o nonce
        bloco->nonce++;
    } while(hash[0] != 0);
    BlocoMinerado *novo = malloc(sizeof(BlocoMinerado));
    novo->bloco = *bloco;
    memcpy(novo->hash, hash, SHA256_DIGEST_LENGTH);
    novo->prox = NULL;
    return novo;
}


/*
 * Ordem de geração de numeros
 * 1)numero de transcoes do bloco
 * 2) os valores das transacoes (origem>destino>qtd)
 * 3) codigo minerador
 * 
 */
