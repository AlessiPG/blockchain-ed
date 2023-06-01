#include <stdio.h>
#include "projeto.h"

void menu(Blockchain *blc) {
    printf("O que deseja calcular?\n\ta) Endereço com mais bitcoins\n");
    char resposta;
    scanf("%c", &resposta);
    // checa se resposta esta entre a e i
    while (resposta < 'a' || resposta > 'i') scanf("%c", &resposta);
    
    switch (resposta) {
       case 'a': 
           maisBitcoins(blc);
           break;
    }
}
