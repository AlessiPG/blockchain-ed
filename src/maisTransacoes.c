#include <stdio.h>
#include <stdlib.h>
#include "openssl/crypto.h"
#include "openssl/sha.h"

typedef struct BlocoNaoMinerado{
	unsigned int numero;
	unsigned int nouce;
	unsigned char data[184];
	unsigned char hashAnterior[SHA_DIGEST_LENGTH];
}BlocoNaoMinerado;

typedef struct BlocoMinerado{
	BlocoNaoMinerado bloco;
	unsigned char hash[SHA_DIGEST_LENGTH];
	struct BlocoMinerado *prox;
}BlocoMinerado;

typedef struct Blockchain{
	BlocoMinerado *inicio;
	BlocoMinerado *fim;
	unsigned int tamanho;
}Blockchain;

void MaisTransacoes(Blockchain bloco,unsigned int size){
	unsigned int transacoes[1000];
	for(int i=0;i<1000;i++){
		transacoes[i]=0;
	}

	BlocoMinerado *paux = bloco.inicio;
	for(int i=0;i<size;i++){
		for(int j=0;j<184;j+3){
			if(paux->bloco.data[j]&&paux->bloco.data[j+1]&&paux->bloco.data[j+2]!=0){
				transacoes[i]++;
			}
		}
		
		paux = paux->prox;
	}

	int maisTransacoes = 0;
	for(int i=0;i<1000;i++){
		if(transacoes[i]>maisTransacoes){
			maisTransacoes = transacoes[i];
		}
	}

	printf("Os blocos com mais transacoes sao:\n");
	for(int i=0;i<1000;i++){
		if(i==maisTransacoes){
			printf("%d\n", i);
		}
	}
	printf("Eles possuem %d transacoes\n", maisTransacoes);
}