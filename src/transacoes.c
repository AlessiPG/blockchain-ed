#include <stdlib.h>
#include "projeto.h"

/*  Ordem de geração de numeros
        1) numero de transacoes do bloco  
        2) os valores das transacoes (origem>destino>qtd)
        3) codigo minerador */
unsigned int * gerarNumerosTransacao(Blockchain *bc, Clientes clientes) {
    unsigned int *nums = malloc(sizeof(unsigned int) * 3);
    if (!nums) return NULL;
    
    // origem: intervalo de [1 - tamanho da lista de contas]
    nums[0] = genRandLong(&bc->r) % clientes.contas.tamanho;
    // convertemos o indice da lista, pra um indice da carteira
    nums[0] = obterIndexDaConta(clientes.contas, nums[0]);

    // destino: intervalo de [0 - CARTEIRA_TAM] evitando que seja igual a origem
    nums[1] = nums[0];
    while (nums[0] == nums[1]) nums[1] = genRandLong(&bc->r) % CARTEIRA_TAM;
    
    // quantidade: intervalo de [0 - dinheiro na conta do origem-esimo elemento da lista de contas
    nums[2] = genRandLong(&bc->r) % (clientes.carteira[nums[0]] + 1);

    return nums;
}

Clientes gerarTransacoes(Blockchain *bc, unsigned char *data) {
    // Precisamos fazer copias do vetor da carteira e da lista de contas para podermos alterar sem ter efeitos na blockchain
    Clientes bufferClientes = criarBuffer(bc);
    
    int n_transacoes = genRandLong(&bc->r) % MAX_TRANSACOES;

    unsigned int index = 0; // index para data
 
    for (int i = 0; i < n_transacoes; i++) {
        // numeros[0] = origem, [1] = destino, [2] = quantidade
        unsigned int *numeros = gerarNumerosTransacao(bc, bufferClientes);

        // removemos a quantidade de moedas na carteira da origem
        bufferClientes.carteira[numeros[0]] -= numeros[2];
        // se a carteira ficou zerada, removemos a conta da lista
        if (bufferClientes.carteira[numeros[0]] == 0) removeConta(&bufferClientes.contas, numeros[0]);
        
        // adicionamos a quantidade de moedas na carteira do destino
        bufferClientes.carteira[numeros[1]] += numeros[2];
        // se a quantidade nao foi 0 e a conta ja nao estava na lista, adicionamos ela na lista
        if (numeros[2] > 0 && !buscaConta(bufferClientes.contas, numeros[1])) adicionaConta(&bufferClientes.contas, numeros[1]);

        // finalmente, adicionamos os numeros na data e aumentamos o index por 3
        data[index] = numeros[0];
        data[index + 1] = numeros[1];
        data[index + 2] = numeros[2];
        index += 3;
    
        free(numeros);
    }

    // geramos e guardamos o minerador na data
    data[DATA_TAM - 1] = genRandLong(&bc->r) % CARTEIRA_TAM;

    return bufferClientes;
}
