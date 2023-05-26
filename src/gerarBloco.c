#include <stdlib.h>
#include <string.h>
#include "projeto.h"
#include "openssl/crypto.h" //arquivo de definição necessário para SHA256_DIGEST_LENGTH
#include "openssl/sha.h" 
#include "mtwister.h"

BlocoNaoMinerado *inicializaBloco(MTRand *r, int numero, unsigned char hash[], int fim){
    BlocoNaoMinerado *novo = malloc(sizeof(BlocoNaoMinerado));
    if(!novo) return NULL;
    novo->numero = numero;
    novo->nonce = 0;
    for(int i = 0; i < 184; ++i)
        novo->data[i] = 0;
    gerarTransacoes(novo->data);//aqui a função receberá r quando gerarTransacoes estiver pronto
    memcpy(novo->hashAnterior, hash, fim);
    //minerarBloco(novo);
    return novo;
}
void insere(Blockchain *blockchain, BlocoMinerado **bloco){
    printf("primeiro eh %d", blockchain->inicio->bloco.numero);
    blockchain->fim->prox = *bloco;
    
}
void processaBloco(Blockchain *blockchain, MTRand *r, int numero, unsigned char hash[], int fim){
    BlocoNaoMinerado *bloco = inicializaBloco(r, numero, hash, fim);
        //unsigned char hash[SHA256_DIGEST_LENGTH];
    do
    {
        SHA256((unsigned char*)bloco, sizeof(bloco), hash);
        if(hash[0] == 0) break;//se nonce = 0 for o hash vÃ¡lido, para a execuÃ§Ã£o antes que altere o nonce
        bloco->nonce++;
    } while(hash[0] != 0);
    BlocoMinerado *novo = malloc(sizeof(BlocoMinerado));
    if (!novo) return NULL;
    novo->bloco = *bloco;
    //memcpy(&(novo->bloco), &bloco, sizeof(BlocoNaoMinerado));
    memcpy(novo->hash, hash, SHA256_DIGEST_LENGTH);
    novo->prox = NULL;
    blockchain->fim->prox = novo;
    blockchain->fim = novo;
    //blockchain->tamanho++;
    //insere(blockchain, &bloco);
    //blockchain->fim->prox = bloco;
    //printf("bloco end %p", bloco);
    //printf("   %p",blockchain->fim->prox);
    //blockchain->fim = bloco;
    //blockchain->tamanho++;
}
