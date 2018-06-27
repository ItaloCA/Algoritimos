#include <stdio.h>
#include <stdlib.h> 


typedef struct noh Noh;

typedef struct noh{
    int chave;
    double peso;
    Noh *proximo;
} Noh; 

int esq(int i){
	return 2*i;
}

int dir(int i){
	return 2*i+1;
}

int pai(int i){
	return i/2;
}

void descer(Noh H[], int i, int* ndeH){
	
	int e = esq(i);
	int d = dir(i);
	int menor = -1;
	if(e < *ndeH && H[e].peso < H[i].peso){
		menor = e;
	}else{
		menor = i;
	}
	if(d< *ndeH && H[d].peso < H[menor].peso){
		menor = d;
	}
	if(menor != i){
		Noh p = H[i];
		H[i] = H[menor];
		H[menor] = p; 
		descer(H, menor, ndeH);
	}
	
}

void criarHeap(Noh H[], int* ndeH){
	for (int i = *ndeH/2; i >= 0; i--){
		descer(H, i, ndeH);
	}
}

Noh removerMin(Noh H[], int* ndeH){
	if(*ndeH == 0){
		Noh nulo;
		nulo.chave = -9999.9999;
		return nulo;
	}
	Noh min = H[0];
	H[0] = H[*ndeH - 1];
	*ndeH = *ndeH - 1;
	if(*ndeH>=1)
		descer(H, 0, ndeH);
	return min;
}

void aumentarPrio(Noh H[], int i, double k){
	H[i].peso = k;
	while(i>=1 && H[pai(i)].peso > H[i].peso){
		Noh p = H[i];
		H[i] = H[pai(i)];
		H[pai(i)] = p;
		i = pai(i);
	}
	
}

void alterarPrio(Noh H[], int i, double k, int* ndeH){

	if(k <= H[i].peso)
		aumentarPrio(H, i, k);
	else{
		H[i].peso = k;
		descer(H, i, ndeH);
	}
}



void incluirHeap(Noh H[], int v, double k, int* ndeH){
	H[*ndeH].chave = v;
	H[*ndeH].peso = -1.0;
	*ndeH = *ndeH + 1;
	aumentarPrio(H, (*ndeH)-1, k);
}

int encontrarHeap(Noh H[], int v, int* ndeH){
	for (int i = 0; i < *ndeH; ++i){
		if (H[i].chave == v){
			return i;
		}
	}
	return -1;
}

int main(int argc, char const *argv[])
{

	Noh H[10];
	int n = 0;
	incluirHeap(H,  1, 4.0, &n);
//	n++;
	incluirHeap(H,  2, 5.0, &n);
//	n++;
	incluirHeap(H,  4, 1.0, &n);
//	n++;
	incluirHeap(H,  5, 3.0, &n);
//	n++;


	for (int i = 0; i < n; ++i)	{
		printf("%d %f\n", H[i].chave, H[i].peso);
		if(i == 2 || i == 4 || i == 8 || i == 16)
			printf("------------\n");
	}

//	criarHeap(H, 5);
	
	
	alterarPrio(H, 3, 2.0, &n);
	alterarPrio(H, 0, 4.0, &n);

	for (int i = 0; i < n; ++i)	{
		printf("%d %f\n", H[i].chave, H[i].peso);
		if(i == 2 || i == 4 || i == 8 || i == 16)
			printf("------------\n");
	}




	
	
	printf("removendo min\n");
	Noh min;
	while(n > 0){
		min = removerMin(H,&n);
		printf("%d %f\n", min.chave, min.peso);	
	}
	
	printf("heap final\n");
	for (int i = 0; i < n; ++i)	{
		printf("%d %f\n", H[i].chave, H[i].peso);
		if(i == 2 || i == 4 || i == 8 || i == 16)
			printf("------------\n");
	}
	/*for (int i = 0; i < 9; ++i)	{
		printf("%d %f\n", H[i].chave, H[i].peso);
		if(i == 2 || i == 4 || i == 8 || i == 16)
			printf("------------\n");
	}*/

	return 0;
}