#include "projeto.h"

void menu(Blockchain *blc)
{
    char resposta = 0;
    do
    {
        printf("O que deseja calcular?\n\ta) Endereço com mais bitcoins\n\tb) Endereço que minerou mais blocos\n\tc) Hash do bloco com mais transações\n\td) Hash do bloco com menos transações\n\te) Média de bitcoins por bloco\n\tf) Printar bloco\n\tg) Printar N blocos minerados por um endereço\n\th) Printar N blocos em ordem crescente de número de transações\n\ti) Printar todos os blocos que tem um dado nonce\n\tz)Encerrar\n");
        scanf("%c", &resposta);
        // checa se resposta esta entre a e i
        while (resposta < 'a' || (resposta > 'i' && resposta < 'z'))
            scanf("%c", &resposta);

        switch (resposta)
        {
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
            while (n < 1 || n > TOTAL_BLOCOS)
                scanf("%u", &n);
            printaBlocoMinerado(*obterBlocoPorNumero(blc, n));
            break;
        case 'g':
            unsigned int end, k = 0;
            printf("Quantos blocos serão printados? ");
            scanf("%u", &k);
            printf("Qual o endereço do minerador? (0 < end < %d) ", CARTEIRA_TAM);
            scanf("%u", &end);
            while (end > CARTEIRA_TAM)
                scanf("%u", &end);
            printaNBlocosDoMinerador(blc, k, end);
            break;
        case 'h':
            unsigned int j = 0;
            printf("Quantos blocos serão printados? ");
            scanf("%u", &j);
            printaNBlocosOrdenados(blc, j);
            break;
        case 'i':
            unsigned int nonce = 0;
            printf("Qual o nonce dos blocos? ");
            scanf("%u", &nonce);
            printaBlocosComNonce(blc, nonce);
            break;
        case 'z':
            printf("Desalocando blockchain...\n");
            desaloca(blc);
            break;
        }
    } while (resposta != 'z');
    printf("Encerrando...\n");
}
