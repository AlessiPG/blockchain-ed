#include <stdlib.h>
#include <string.h>
#include "mtwister.h"
#include "projeto.h"

BlocoNaoMinerado *inicializaGenesis(){
    BlocoNaoMinerado *novo = malloc(sizeof(BlocoNaoMinerado));
    if(!novo) return NULL;
    
    novo->numero = 1;
    novo->nonce = 0;
    //inicializa o vetor com a frase e completa o restante com zeros(numéricos e não em "caracteres")
    const char frase[] = "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks";
    size_t tamanho = strlen(frase);

    memcpy(novo->data, frase, tamanho);
    memset(novo->data + tamanho, 0, sizeof(novo->data) - tamanho);

    for (int i=0; i<SHA256_DIGEST_LENGTH; ++i)
        novo->hashAnterior[i] = 0;

    return novo;
}
