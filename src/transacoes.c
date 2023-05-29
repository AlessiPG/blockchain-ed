#include "projeto.h"

/*  Ordem de geração de numeros
        1) numero de transcoes do bloco  
        2) os valores das transacoes (origem>destino>qtd)
        3) codigo minerador */

unsigned int * gerarTransacoes(Blockchain *bc, unsigned char *data) {
    // Precisamos fazer copias do vetor da carteira e da lista de contas para podermos alterar sem ter efeitos na blockchain
    unsigned int *bufferCarteira = copiaCarteira(bc->clientes.carteira);
    Contas bufferConta = copiaListaContas(bc->clientes.contas);

    //Clientes bufferClientes = { .carteira = bufferCarteira, .contas = bufferConta };

    int n_transacoes = genRandLong(&bc->r) % MAX_TRANSACOES;

    return bufferCarteira;
}
