#include <stdio.h>
#include <stdlib.h>
#include "openssl/crypto.h"
#include "openssl/sha.h"

typedef struct BlocoNaoMinerado{
	unsigned int numero;
	unsigned int nouce;
	unsigned char data[184];
	unsigned char hashAnterior[SHA256_DIGEST_LENGTH];
}BlocoNaoMinerado;

typedef struct BlocoMinerado{
	BlocoNaoMinerado bloco;
	unsigned char hash[SHA256_DIGEST_LENGTH];
	struct BlocoMinerado *prox;
}BlocoMinerado;

typedef struct Blockchain{
	BlocoMinerado *inicio;
	BlocoMinerado *fim;
	unsigned int tamanho;
}Blockchain;

void MaisRico(unsigned int carteira[], int size){
	int maior = 0;
	for(int i=0;i<size;i++){
		if(carteira[i]>maior){
			maior = carteira[i];
		}
	}	
	printf("Os mais ricos sao:\n");
	for(int i=0;i<size;i++){
		if(carteira[i]==maior){
			printf("%d\n", i);
		}
	}
	printf("Eles possuem %d bitcoins\n", maior);
}