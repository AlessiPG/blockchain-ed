#include "projeto.h"

void printaData(unsigned char *data)
{
    int j, i = 1;
    for (j = 0; j < DATA_TAM - 3; j += 3)
    {
        printf("%3hhu %3hhu %3hhu | ", data[j], data[j + 1], data[j + 2]);
        if (i % 9 == 0)
            printf("\n");
        i++;
    }
    printf("Minerador: %3hhu\n", data[j]);
}

void printaHash(unsigned char *hash)
{
    int i;
    for (i = 0; i < SHA256_DIGEST_LENGTH - 1; i++)
        printf("%02x", hash[i]);
    printf("%02x\n", hash[i]);
}

void printaBlocoNaoMinerado(BlocoNaoMinerado bloco)
{
    printf("Número: %u\tNonce: %u\nData:\nNº de transações: %u\n", bloco.numero, bloco.nonce, obterNumeroTransacoes(bloco));
    printaData(bloco.data);
    printf("Hash anterior: ");
    printaHash(bloco.hashAnterior);
}

void printaBlocoMinerado(BlocoMinerado bloco)
{
    printaBlocoNaoMinerado(bloco.bloco);
    printf("Hash atual   : ");
    printaHash(bloco.hash);
}

void printaCarteira(unsigned int *carteira)
{
    for (int i = 0; i < CARTEIRA_TAM; i += 16)
    {
        for (int j = 0; j < 16; j++)
        {
            printf("%3u:%3u\t", i + j, carteira[i + j]);
        }
        printf("\n");
    }
}

void printaContas(Clientes clientes)
{
    No *atual = clientes.contas.lista;

    while (atual->prox)
    {
        printf("%d->", atual->chave);
        atual = atual->prox;
    }
    printf("%d", atual->chave);
    printf("\n");
}

void printaNos(No *lista)
{
    No *atual = lista;

    while (atual->prox)
    {
        printf("%d, ", atual->chave);
        atual = atual->prox;
    }
    printf("%d", atual->chave);
}
