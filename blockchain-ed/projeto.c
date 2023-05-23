#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/crypto.h" //arquivo de defini��o necess�rio para SHA256_DIGEST_LENGTH
#include "openssl/sha.h" //arquivo de defini��o necess�rio fun��o SHA256
#include "mtwister.h"
#include "projeto.h"


BlocoNaoMinerado *inicializaGenesis(){
    BlocoNaoMinerado *novo = malloc(sizeof(BlocoNaoMinerado));
    if(!novo) return NULL;
    
    novo->numero = 1;
    novo->nonce = 0;
    //inicializa o vetor com a frase e completa o restante com zeros(num�ricos e n�o em "caracteres")
    const char frase[] = "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks";
    size_t tamanho = strlen(frase);

    memcpy(novo->data, frase, tamanho);
    memset(novo->data + tamanho, 0, sizeof(novo->data) - tamanho);

    for (int i=0; i<SHA256_DIGEST_LENGTH; ++i)
        novo->hashAnterior[i] = 0;

    return novo;
}

BlocoMinerado *minerarGenesis(BlocoNaoMinerado *bloco, MTRand *r){
    //escolhe o minerador
    bloco->data[183] = genRandLong(r)%256;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    do
    {
        SHA256((unsigned char*)bloco, sizeof(bloco), hash);
        if(hash[0] == 0) break;//se nonce = 0 for o hash v�lido, para a execu��o antes que altere o nonce
        bloco->nonce++;
    } while(hash[0] != 0);
    BlocoMinerado *novo = malloc(sizeof(BlocoMinerado));
    novo->bloco = *bloco;
    memcpy(novo->hash, hash, SHA256_DIGEST_LENGTH);
    novo->prox = NULL;
    return novo;
}


/*
 * Ordem de gera��o de numeros
 * 1)numero de transcoes do bloco
 * 2) os valores das transacoes (origem>destino>qtd)
 * 3) codigo minerador
 * 
 */