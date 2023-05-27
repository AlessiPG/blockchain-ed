#include <stdio.h>
#include <stdlib.h>
#include "projeto.h"

unsigned int checaTransacoes(BlocoMinerado *bloco)
{
    int count = 0;
    for (int i = 0; i < 61; i++)
    {
        if (bloco->bloco.data[i] && bloco->bloco.data[i + 1] && bloco->bloco.data[i + 2] != 0)
            count++;
        i += 2;
    }
    return count;
}
void selecao(BlocoMinerado **v, int ini, int fim)
{
    if (ini > fim)
        return;
    for (int i = ini; i < fim; i++)
    {
        if (checaTransacoes(v[i]) < checaTransacoes(v[ini]))
        {
            BlocoMinerado *aux = v[ini];
            v[ini] = v[i];
            v[i] = aux;
        }
    }
}

void ordenacao(BlocoMinerado **v, int ini, int fim)
{
    if (ini >= fim)
        return;
    for (int i = 1; i < fim; i++) // i = 1, pois o bloco 1 não possui transações, logo é o primeiro da lista
    {
        selecao(v, ini + i, fim);
    }
}
void imprimirNPrimeirosBlocos(Blockchain *blockchain, int n)
{
    BlocoMinerado **vetor = malloc(sizeof(BlocoMinerado) * n);
    BlocoMinerado *aux = blockchain->inicio;

    for (int i = 0; i < n; i++)
    {
        vetor[i] = aux;
        aux = aux->prox;
    }

    ordenacao(vetor, 0, n);
    for (int i = 0; i < n; i++)
    {
        printf("Bloco numero: %d\n", vetor[i]->bloco.numero);
    }
}
