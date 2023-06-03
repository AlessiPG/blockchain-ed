#include <string.h>
#include <stdlib.h>
#include "openssl/crypto.h"
#include "projeto.h"

BlocoNaoMinerado *inicializaBloco(Blockchain *bc)
{
    BlocoNaoMinerado *novo = malloc(sizeof(BlocoNaoMinerado));
    if (!novo)
        return NULL;

    novo->numero = bc->fim->bloco.numero + 1;
    novo->nonce = 0;
    memcpy(novo->hashAnterior, bc->fim->hash, SHA256_DIGEST_LENGTH);

    return novo;
}

BlocoMinerado *mineraBloco(Blockchain *chain, BlocoNaoMinerado *blc)
{
    if (!blc)
        return NULL;

    BlocoMinerado *novo = malloc(sizeof(BlocoMinerado));
    if (!novo)
        return NULL;

    // Geramos as transacoes aqui pois precisamos trocar a copia da carteira pela carteira de verdade apos minerar o bloco.
    Clientes bufferClientes = gerarTransacoes(chain, blc->data);
    for (int i = 0; i < DATA_TAM - 1; i += 3)
    {
        // se a carteira ficou zerada, removemos a conta da lista
        if (bufferClientes.carteira[blc->data[i]] == 0)
            removeConta(&bufferClientes.contas, blc->data[0]);
        // se a quantidade nao foi 0 e a conta ja nao estava na lista, adicionamos ela na lista
        if (blc->data[i + 2] > 0 && !buscaConta(bufferClientes.contas, blc->data[i + 1]))
            adicionaConta(&bufferClientes.contas, blc->data[i + 1]);
    }
    obterNumeroTransacoes(*blc);

    while (1)
    {
        SHA256((unsigned char *)blc, sizeof(BlocoNaoMinerado), novo->hash);
        if (novo->hash[0] == 0)
            break;
        blc->nonce++;
    }

    novo->bloco = *blc;
    novo->prox = NULL;

    // Apos a mineraçao aplicamos o buffer da carteira e das contas
    chain->clientes = bufferClientes;

    return novo;
}
