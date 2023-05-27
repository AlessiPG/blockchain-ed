#ifndef __PROJETO_H_
#define __PROJETO_H_

#define DATA_TAM 184 
#define CARTEIRA_TAM 256
#define STRING_INICIAL "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks"
#define SEED_ALEATORIA 1234567
#define RECOMPENSA 50

#include <stdbool.h>
#include "openssl/sha.h"
#include "mtwister.h"

typedef struct BlocoNaoMinerado {
    unsigned int numero;
    unsigned int nonce;
    unsigned char data[DATA_TAM];
    unsigned char hashAnterior[SHA256_DIGEST_LENGTH];
} BlocoNaoMinerado;

typedef struct BlocoMinerado {
    BlocoNaoMinerado bloco;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    struct BlocoMinerado *prox;
} BlocoMinerado;

typedef struct No { // Lista de contas não vazias.
    int chave;
    struct No *prox;
} No;

typedef struct Contas {
    unsigned int tamanho;
    No *lista;
} Contas;

typedef struct Blockchain {
    BlocoMinerado *ini;
    BlocoMinerado *fim;
    unsigned int carteira[CARTEIRA_TAM];
    Contas contas;
    unsigned int tamanho;
    MTRand r;
} Blockchain;


BlocoNaoMinerado * inicializaGenesis();
BlocoNaoMinerado * inicializaBloco(Blockchain *);

BlocoMinerado * mineraGenesis(BlocoNaoMinerado *, MTRand *);
BlocoMinerado * mineraBloco(BlocoNaoMinerado *blc);

No * gerarNo(int);
bool buscarContas(Blockchain *, int);
int adicionaConta(Blockchain *, int);

Blockchain * inicializaBlockchain();
int novoBloco(Blockchain *);

int gerarTransacoes(unsigned char *);

#endif
