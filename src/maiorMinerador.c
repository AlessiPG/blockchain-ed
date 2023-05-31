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

void MaiorMinerador(Blockchain bloco,unsigned int size){
	unsigned char moda[256];
	for(int i=0;i<256;i++){
		moda[i]=0;
	}

	BlocoMinerado *paux = bloco.inicio;
	for(int i=0;i<size;i++){
		moda[paux->bloco.data[184]]++;
		paux = paux->prox;
	}

	int maior = 0;
	int blocosMinerados;
	for(int i=0;i<256;i++){
		if(moda[i]>maior){
			maior = i;
			blocosMinerados = moda[i];
		}
	}
	
	printf("Os maiores mineradores sao:\n");
	for(int i=0;i<256;i++){
		if(i==maior){
			printf("%d\n", i);
		}
	}
	printf("Eles mineraram %d blocos\n", blocosMinerados);
}
