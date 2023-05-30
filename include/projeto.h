#ifndef __PROJETO_H_
#define __PROJETO_H_

#define TOTAL_BLOCOS 1
#define DATA_TAM 184 
#define CARTEIRA_TAM 256
#define STRING_INICIAL "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks"
#define SEED_ALEATORIA 1234567
#define RECOMPENSA 50
#define MAX_TRANSACOES 61

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
    unsigned int chave;
    struct No *prox;
} No;

typedef struct Contas {
    unsigned int tamanho;
    No *lista;
} Contas;

typedef struct Clientes {
    unsigned int carteira[CARTEIRA_TAM];
    Contas contas;
} Clientes;

typedef struct Blockchain {
    BlocoMinerado *ini;
    BlocoMinerado *fim;
    Clientes clientes;
    unsigned int tamanho;
    MTRand r;
} Blockchain;


BlocoNaoMinerado * inicializaGenesis();
BlocoNaoMinerado * inicializaBloco(Blockchain *);

BlocoMinerado * mineraGenesis(BlocoNaoMinerado *, MTRand *);
BlocoMinerado * mineraBloco(Blockchain *, BlocoNaoMinerado *);

void inicializaContas(Contas *);
No * gerarNo(unsigned int);
int adicionaConta(Contas *, unsigned int);
unsigned int obterIndexDaConta(Contas, unsigned int);
bool buscarContas(Blockchain *, unsigned int);

int copiaContas(Contas, Contas *);
void copiaCarteira(unsigned int[], unsigned int []);

Blockchain * inicializaBlockchain();
int novoBloco(Blockchain *);

Clientes criarBuffer(Blockchain *);
unsigned int * gerarNumerosTransacao(Blockchain *, Clientes);
Clientes gerarTransacoes(Blockchain *, unsigned char *);

void printaCarteira(unsigned int *);
void printaContas(Contas);

#endif
