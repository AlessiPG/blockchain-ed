#include <stdlib.h>
#include <string.h>
#include "projeto.h"

BlocoNaoMinerado * inicializaBloco(Blockchain *bc) {
    BlocoNaoMinerado *novo = malloc(sizeof(BlocoNaoMinerado));
    if (!novo) return NULL;

    novo->numero = bc->fim->bloco.numero + 1;
    novo->nonce = 0;
    if (gerarTransacoes(novo->data)) return NULL;
    memcpy(novo->hashAnterior, bc->fim->hash, SHA256_DIGEST_LENGTH);

    return novo;
}

BlocoMinerado * mineraBloco(BlocoNaoMinerado *blc) {
    if (!blc) return NULL;

    BlocoMinerado *novo = malloc(sizeof(BlocoMinerado));
    if (!novo) return NULL;

    while (1) {
        SHA256((unsigned char *) blc, sizeof(BlocoNaoMinerado), novo->hash);
        if (novo->hash[0] == 0) break;
        blc->nonce++;
    }

    novo->bloco = *blc;
    novo->prox = NULL;

    return novo;
}
