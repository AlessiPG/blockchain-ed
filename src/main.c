#include "projeto.h"

int main(void)
{
    Blockchain *corrente = inicializaBlockchain();
    if (!corrente)
        return -1;

    // subtraimos 1 de TOTAL_BLOCOS para levar o genesis em conta
    for (int i = 0; i < TOTAL_BLOCOS - 1; i++)
    {
        novoBloco(corrente);
    }

    BlocoMinerado *aux = corrente->ini;
    while (aux != NULL)
    {
        printaBlocoMinerado(*aux);
        aux = aux->prox;
    }

    menu(corrente);
    int sistema = 0;
    for (int i = 0; i < 256; i++)
        sistema += corrente->clientes.carteira[i];
    printf("\nTOTAL BTC SISTEMA: %d\n", sistema);
    return 0;
}
