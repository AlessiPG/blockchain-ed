#include "projeto.h"

void inicializaBlockchain(Blockchain *bc, MTRand *r) {
    BlocoMinerado *genesis = minerarGenesis(inicializaGenesis(), r);
    bc->inicio = genesis;
    bc->fim = genesis;
    bc->tamanho = 0;
}
