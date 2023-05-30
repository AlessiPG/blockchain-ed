#include <stdlib.h>
#include "projeto.h"

/*  Ordem de geração de numeros
        1) numero de transacoes do bloco  
        2) os valores das transacoes (origem>destino>qtd)
        3) codigo minerador */
unsigned int * gerarNumerosTransacao(Blockchain *bc, Clientes clientes) {
    unsigned int *nums = malloc(sizeof(unsigned int) * 3);
    
    // origem: intervalo de [1 - tamanho da lista de contas]
    nums[0] = 1 + genRandLong(&bc->r) % clientes.contas.tamanho;

    // destino: intervalo de [0 - CARTEIRA_TAM] evitando que seja igual a origem
    nums[1] = nums[0];
    while (nums[0] == nums[1]) nums[1] = genRandLong(&bc->r) % CARTEIRA_TAM;
    
    // quantidade: intervalo de [0 - dinheiro na conta do origem-esimo elemento da lista de contas
    unsigned int dinheiroNaConta = clientes.carteira[obterIndexDaConta(clientes.contas, nums[0])];
    nums[2] = genRandLong(&bc->r) % dinheiroNaConta;

    return nums;
}

Clientes gerarTransacoes(Blockchain *bc, unsigned char *data) {
    // Precisamos fazer copias do vetor da carteira e da lista de contas para podermos alterar sem ter efeitos na blockchain
    Clientes bufferClientes = criarBuffer(bc);

    int n_transacoes = genRandLong(&bc->r) % MAX_TRANSACOES;

    for (int i = 0; i < n_transacoes; i++) {
        unsigned int *numeros = gerarNumerosTransacao(bc, bufferClientes);
        
        printf("%d, %d, %d\n", numeros[0], numeros[1], numeros[2]);
        free(numeros);
    }

    return bufferClientes;
}
