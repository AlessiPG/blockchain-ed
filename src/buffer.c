#include "projeto.h"

Clientes criarBuffer(Blockchain *bc)
{
    Clientes novo;

    copiaCarteira(bc->clientes.carteira, novo.carteira);

    // Precisamos inicializar a lista de clientes de novo senao o ultimo elemento da lista sera lixo
    inicializaContas(&novo.contas);
    copiaContas(bc->clientes.contas, &novo.contas);

    return novo;
}
