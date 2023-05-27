#ifndef __PROJETO_H
#define __PROJETO_H

#include <string.h>
#include "mtwister.h"

#define TOTAL_BLOCOS 10
#define SHA256_DIGEST_LENGTH 32

typedef struct BlocoNaoMinerado
{
  unsigned int numero; //4
  unsigned int nonce; //4
  unsigned char data[184]; //nao alterar. Deve ser inicializado com zeros.
  unsigned char hashAnterior[SHA256_DIGEST_LENGTH]; //32
} BlocoNaoMinerado;

typedef struct BlocoMinerado
{
  BlocoNaoMinerado bloco;
  unsigned char hash[SHA256_DIGEST_LENGTH];
  struct BlocoMinerado *prox;
} BlocoMinerado;

typedef struct Blockchain
{
    BlocoMinerado *inicio;
    BlocoMinerado *fim;
    unsigned int tamanho;
} Blockchain;

BlocoMinerado *minerarGenesis(BlocoNaoMinerado *bloco, MTRand *r);

BlocoNaoMinerado *inicializaGenesis();

BlocoNaoMinerado *inicializaBloco(MTRand *r, int numero, unsigned char hash[]);

void gerarTransacoes(unsigned char *data);

void processaBloco(Blockchain *blockchain, MTRand *r, int numero, unsigned char hash[]);

void inicializaBlockchain(Blockchain *bc, MTRand *r);

void adicionaNoFinal(Blockchain *bc, BlocoMinerado *bm);

void imprimirNPrimeirosBlocos(BlocoMinerado blockchain, int n);

void imprimirNonceIgual(BlocoMinerado blockchain, unsigned int n);

float acharMediaBitcoins(Blockchain bc, unsigned int carteira[]);

#endif
