#include <stdlib.h>
#include <string.h>
#include "projeto.h"

Blockchain * inicializaBlockchain() {
    Blockchain *nova = malloc(sizeof(Blockchain));
    memset(nova->carteira, 0, sizeof(nova->carteira));
    nova->tamanho = 0;
    nova->r = seedRand(SEED_ALEATORIA);

    BlocoMinerado *genesis = mineraGenesis(inicializaGenesis(), &nova->r);
    if (!genesis) return NULL;
    
    nova->ini = nova->fim = genesis;
    
    unsigned char minerador = genesis->bloco.data[DATA_TAM - 1];
    // Adiciona a recompensa em bitcoins na carteira do minerador
    nova->carteira[minerador] = RECOMPENSA;
    // Adiciona o minerador na lista de contas com dinheiro
    adicionaConta(nova, minerador);

    return nova;
}

int novoBloco(Blockchain *bc) {
    BlocoMinerado *novo = mineraBloco(inicializaBloco(bc));

    bc->fim->prox = novo;
    bc->fim = novo;
    bc->tamanho++;

    unsigned char minerador = novo->bloco.data[DATA_TAM - 1];
    bc->carteira[minerador] += RECOMPENSA;
    // Se o minerador ja nao esta na lista de contas com dinheiro..
    if (!buscarContas(bc, minerador)) {
        adicionaConta(bc, novo->bloco.data[DATA_TAM - 1]);
    }
    return 0;
}
