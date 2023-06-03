#ifndef __PROJETO_H_
#define __PROJETO_H_

#define TOTAL_BLOCOS 1000
#define DATA_TAM 184 
#define CARTEIRA_TAM 256
#define STRING_INICIAL "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks"
#define SEED_ALEATORIA 1234567
#define RECOMPENSA 50
#define MAX_TRANSACOES (DATA_TAM - 1) / 3

#include <stdbool.h>
#include <stdio.h>//por ser um include usado pela maioria dos arquivos .c, foi conveniente deixa-lo aqui
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

typedef struct No {
    unsigned int chave;
    struct No *prox;
} No;

// Lista de contas não vazias.
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

No * gerarNo(unsigned int);
No * adicionaNo(No *, unsigned int);
void freeEmLista(No *lista);

void inicializaContas(Contas *);
int adicionaConta(Contas *, unsigned int);
unsigned int obterIndexDaConta(Contas, unsigned int);
void removeConta(Contas *, unsigned int);
bool buscaConta(Contas, unsigned int);

int copiaContas(Contas, Contas *);
void copiaCarteira(unsigned int[], unsigned int []);

Blockchain * inicializaBlockchain();
int novoBloco(Blockchain *);
BlocoMinerado * obterBlocoPorNumero(Blockchain *, unsigned int);
void desaloca(Blockchain *);

Clientes criarBuffer(Blockchain *);
Clientes gerarTransacoes(Blockchain *, unsigned char *);
unsigned int obterNumeroTransacoes(BlocoNaoMinerado);

void printaCarteira(unsigned int *);
void printaHash(unsigned char *);
void printaContas(Clientes);
void printaData(unsigned char *);
void printaBlocoNaoMinerado(BlocoNaoMinerado);
void printaBlocoMinerado(BlocoMinerado);
void printaNos(No *);

void menu(Blockchain *);

void maisBitcoins(Blockchain *);
void maisMinerou(Blockchain *);
void maisTransacoes(Blockchain *);
void menosTransacoes(Blockchain *);
void mediaBitcoins(Blockchain *);
void printaNBlocos(Blockchain *, unsigned int, unsigned int);
void printaNBlocosDoMinerador(Blockchain *, unsigned int, unsigned int);
void printaNBlocosOrdenados(Blockchain *, unsigned int);
void printaBlocosComNonce(Blockchain *, unsigned int);

#endif
