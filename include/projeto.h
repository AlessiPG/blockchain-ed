#ifndef __PROJETO_H
#define __PROJETO_H

#define TOTAL_BLOCOS 1000
#define SHA256_DIGEST_LENGTH 32

typedef struct BlocoNaoMinerado
{
  unsigned int numero;//4
  unsigned int nonce;//4
  unsigned char data[184];//nao alterar. Deve ser inicializado com zeros.
  unsigned char hashAnterior[SHA256_DIGEST_LENGTH]; //32
}BlocoNaoMinerado;

typedef struct BlocoMinerado
{
  BlocoNaoMinerado bloco;
  unsigned char hash[SHA256_DIGEST_LENGTH];
  struct BlocoMinerado *prox;
} BlocoMinerado;

BlocoNaoMinerado *inicializaGenesis();

BlocoMinerado *minerarGenesis(BlocoNaoMinerado *bloco, MTRand *r);

void imprimirNPrimeirosBlocos(BlocoMinerado blockchain, int n);

void imprimirNonceIgual(BlocoMinerado blockchain, unsigned int n);

#endif
