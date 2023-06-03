#include "projeto.h"

// endereço com mais bitcoins e o número de bitcoins dele (liste mais de um em caso de empate)
void maisBitcoins(Blockchain *blc)
{
    unsigned int maiorN = 0;
    No *maiores = gerarNo(0); // lista para guardar os endereços com mais bitcoins

    for (int i = 0; i < CARTEIRA_TAM; i++)
    {
        if (blc->clientes.carteira[i] > maiorN)
        {
            maiorN = blc->clientes.carteira[i];
            freeEmLista(maiores);
            maiores = gerarNo(i);
        }
        else if (blc->clientes.carteira[i] == maiorN)
        {
            maiores = adicionaNo(maiores, i);
        }
    }

    printf("O(s) endereços ");
    printaNos(maiores);
    printf(" possuem %d, que é o maior número de bitcoins.\n", maiorN);

    freeEmLista(maiores);
}

// endereço que minerou mais blocos (liste mais de um em caso de empate)
void maisMinerou(Blockchain *blc)
{
    // primeiro passamos pela blockchain contando quantos blocos cada endereço minerou
    unsigned int mineradores[CARTEIRA_TAM] = {0};

    BlocoMinerado *atual = blc->ini;
    while (atual)
    {
        mineradores[atual->bloco.data[DATA_TAM - 1]]++;
        atual = atual->prox;
    }

    // agora achamos os endereços que mais mineraram
    unsigned int maiorN = 0;
    No *maiores = gerarNo(0);

    for (int i = 0; i < CARTEIRA_TAM; i++)
    {
        if (mineradores[i] > maiorN)
        {
            maiorN = mineradores[i];
            freeEmLista(maiores);
            maiores = gerarNo(i);
        }
        else if (mineradores[i] == maiorN)
        {
            maiores = adicionaNo(maiores, i);
        }
    }

    printf("O(s) endereços ");
    printaNos(maiores);
    printf(" mineraram %d blocos, que é o maior número de blocos minerados.\n", maiorN);
}

// hash do bloco com mais transações e o número de transações dele (liste mais de um em caso de empate)
void maisTransacoes(Blockchain *blc)
{
    // primeiro achamos os numeros dos blocos com mais transacoes
    unsigned int maiorN = 0;
    No *maiores = gerarNo(0);

    BlocoMinerado *atual = blc->ini; // pegamos o prox do ini pra pularmos o bloco genesis

    while (atual)
    {
        unsigned int n_transacoes = obterNumeroTransacoes(atual->bloco);
        if (n_transacoes > maiorN)
        {
            maiorN = n_transacoes;
            freeEmLista(maiores);
            maiores = gerarNo(atual->bloco.numero);
        }
        else if (n_transacoes == maiorN)
        {
            maiores = adicionaNo(maiores, atual->bloco.numero);
        }
        atual = atual->prox;
    }

    // passamos pela lista de numeros de blocos com o maior numero de transacoes
    No *atual2 = maiores;
    printf("O(s) hash do(s) bloco(s) com o maior número de transações (%d) são:\n", maiorN);
    while (atual2)
    {
        printf("Bloco %d: ", atual2->chave); // somamos 1 pois os numeros da blockchain começam em 1
        printaHash(obterBlocoPorNumero(blc, atual2->chave)->hash);
        atual2 = atual2->prox;
    }
}

// hash do bloco com menos transações e o número de transações dele (liste mais de um em caso de empate)
void menosTransacoes(Blockchain *blc)
{
    unsigned int menorN = 61; // numero maximo de transacoes num bloco
    No *menores = gerarNo(0);

    BlocoMinerado *atual = blc->ini;

    while (atual)
    {
        unsigned int n_transacoes = obterNumeroTransacoes(atual->bloco);
        if (n_transacoes < menorN)
        {
            menorN = n_transacoes;
            freeEmLista(menores);
            menores = gerarNo(atual->bloco.numero);
        }
        else if (n_transacoes == menorN)
        {
            menores = adicionaNo(menores, atual->bloco.numero);
        }
        atual = atual->prox;
    }

    No *atual2 = menores;
    printf("O(s) hash do(s) bloco(s) com o menor número de transações (%d) são:\n", menorN);
    while (atual2)
    {
        printf("Bloco %d: ", atual2->chave);
        printaHash(obterBlocoPorNumero(blc, atual2->chave)->hash);
        atual2 = atual2->prox;
    }
}

// quantidade média de bitcoins por bloco
void mediaBitcoins(Blockchain *blc)
{
    float media = 0;
    BlocoMinerado *atual = blc->ini->prox;

    while (atual)
    {
        // passa por todas as quantidades de bitcoins de um bloco e adiciona em media
        for (int i = 2; i < DATA_TAM; i += 3)
            media += atual->bloco.data[i];

        atual = atual->prox;
    }

    media = media / TOTAL_BLOCOS;

    printf("A média de bitcoins por bloco na blockchain é %.3lf\n", media);
}

// imprimir todos os campos dos n primeiros blocos minerados por um dado endereço.
void printaNBlocosDoMinerador(Blockchain *blc, unsigned int n, unsigned int endereco)
{
    BlocoMinerado *atual = blc->ini;

    printf("O(s) seguinte(s) bloco(s) foram minerados pelo endereço %u:\n", endereco);
    while (atual && n > 0)
    {
        unsigned int minerador = atual->bloco.data[DATA_TAM - 1];
        if (minerador != endereco)
        {
            atual = atual->prox;
            continue;
        }

        printaBlocoMinerado(*atual);
        n--;
        atual = atual->prox;
    }
}

// imprimir todos os campos dos n primeiros blocos. A impressão deve ser em ordem crescente de quantidade de transações do bloco
void printaNBlocosOrdenados(Blockchain *blc, unsigned int n)
{
    // criaremos 2 vetores de tamanho n ligados etre si. um guarda o numero de um bloco e o outro guarda o numero de transacoes daquele bloco
    unsigned int numeros[n];
    unsigned int transacoes[n];

    BlocoMinerado *atual = blc->ini->prox;
    for (unsigned int i = 0; i < n; i++)
    {
        numeros[i] = atual->bloco.numero;
        transacoes[i] = obterNumeroTransacoes(atual->bloco);
        atual = atual->prox;
    }

    // agora precisamos ordenar o vetor transacoes, refletindo as mudancas no vetor numeros
    for (unsigned int i = 0; i < n; i++)
    {
        unsigned int j = i;
        while (j > 0 && transacoes[j - 1] > transacoes[j])
        {
            unsigned int temp = transacoes[j];
            transacoes[j] = transacoes[j - 1];
            transacoes[j - 1] = temp;

            temp = numeros[j];
            numeros[j] = numeros[j - 1];
            numeros[j - 1] = temp;

            j--;
        }
    }

    printf("O(s) %d primeiro(s) bloco(s) em ordem crescente de número de transações são:\n", n);

    // agora usamos o vetor numeros ja ordenado pra printar os blocos
    for (unsigned int i = 0; i < n; i++)
        printaBlocoMinerado(*obterBlocoPorNumero(blc, numeros[i]));
}

void printaBlocosComNonce(Blockchain *blc, unsigned int nonce)
{
    BlocoMinerado *atual = blc->ini;

    while (atual)
    {
        if (atual->bloco.nonce == nonce)
            printaBlocoMinerado(*atual);
        atual = atual->prox;
    }
}
