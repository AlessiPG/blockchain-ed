#include <stdio.h>
#include "projeto.h"

void menu(Blockchain *blc) {
    printf("O que deseja calcular?\n\ta) Endereço com mais bitcoins\n\tb) Endereço que minerou mais blocos\n\tc) Hash do bloco com mais transações\n\td) Hash do bloco com menos transações\n\te) Média de bitcoins por bloco\n\tf) Printar bloco\n\tg) Printar N blocos minerados por um endereço\n");
    char resposta;
    scanf("%c", &resposta);
    // checa se resposta esta entre a e i
    while (resposta < 'a' || resposta > 'i') scanf("%c", &resposta);
    
    switch (resposta) {
        case 'a': 
            maisBitcoins(blc);
            break;
        case 'b':
            maisMinerou(blc);
            break;
        case 'c':
            maisTransacoes(blc);
            break;
        case 'd':
            menosTransacoes(blc);
            break;
        case 'e':
            mediaBitcoins(blc);
            break;
        case 'f':
            unsigned int n = 0;
            printf("Qual o número do bloco para ser printado? (1 < n < %d) ", TOTAL_BLOCOS);
            while (n < 1 || n > TOTAL_BLOCOS) scanf("%u", &n);
            printaBlocoMinerado(*obterBlocoPorNumero(blc, n));
            break;
        case 'g':
            unsigned int end, k = 0;
            printf("Quantos blocos serão printados? ");
            scanf("%u", &k);
            printf("Qual o endereço do minerador? (0 < end < %d) ", CARTEIRA_TAM);
            scanf("%u", &end);
            while (end > CARTEIRA_TAM) scanf("%u", &end);
            printaNBlocosMinerados(blc, k, end);
            break;
    }
}
