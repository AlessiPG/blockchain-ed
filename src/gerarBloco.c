#include <stdlib.h>
#include <string.h>
#include "projeto.h"
#include "openssl/crypto.h" //arquivo de defini��o necess�rio para SHA256_DIGEST_LENGTH
#include "openssl/sha.h"
#include "mtwister.h"

BlocoNaoMinerado *inicializaBloco(MTRand *r, int numero, unsigned char hash[])
{
    BlocoNaoMinerado *novo = malloc(sizeof(BlocoNaoMinerado));
    if (!novo)
        return NULL;
    novo->numero = numero;
    novo->nonce = 0;
    for (int i = 0; i < 184; ++i)
        novo->data[i] = 0;
    gerarTransacoes(novo->data); // aqui a fun��o receber� r quando gerarTransacoes estiver pronto
    memcpy(novo->hashAnterior, hash, SHA256_DIGEST_LENGTH);
    return novo;
}

void processaBloco(Blockchain *blockchain, MTRand *r, int numero, unsigned char hash[])
{
    BlocoNaoMinerado *bloco = inicializaBloco(r, numero, hash);
    do
    {
        SHA256((unsigned char *)bloco, sizeof(bloco), hash);
        if (hash[0] == 0)
            break; // se nonce = 0 for o hash válido, para a execução antes que altere o nonce
        bloco->nonce++;
    } while (hash[0] != 0);
    BlocoMinerado *novo = malloc(sizeof(BlocoMinerado));
    if (!novo)
        return;
    novo->bloco = *bloco;

    memcpy(novo->hash, hash, SHA256_DIGEST_LENGTH);
    novo->prox = NULL;
    blockchain->fim->prox = novo;
    blockchain->fim = novo;
}
