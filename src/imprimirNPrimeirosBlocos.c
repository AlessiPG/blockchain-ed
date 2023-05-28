#include <stdio.h>
#include <stdlib.h>
#include "projeto.h"

unsigned int checaTransacoes(BlocoMinerado *bloco)
{
    int count = 0;
    for (int i = 0; i < 61; i++)
    {
        if (bloco->bloco.data[i] && bloco->bloco.data[i + 1] && bloco->bloco.data[i + 2] != 0)//checa as posições 3 a 3 para verificar se elas são de fato transações
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
        if (checaTransacoes(v[i]) < checaTransacoes(v[ini]))//condição para posicionamento no vetor = qtd de transações
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
        selecao(v, ini + i, fim);//envia recursivamente o vetor para que sempre o bloco com menos transações seja posicionado na primeira posição
    }
}
void imprimirNPrimeirosBlocos(Blockchain *blockchain, int n)
{
    BlocoMinerado **vetor = malloc(sizeof(BlocoMinerado) * n);
    BlocoMinerado *aux = blockchain->inicio;

    for (int i = 0; i < n; i++)//adiciona os blocos de 1 até n em um vetor
    {
        vetor[i] = aux;
        aux = aux->prox;
    }

    ordenacao(vetor, 0, n);
    for (int i = 0; i < n; i++)//imprime (preciso deixar isso mais bonito)
    {
        printf("Bloco numero: %d\n", vetor[i]->bloco.numero);
    }
}
