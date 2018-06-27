#include <stdio.h>
#include <stdlib.h>  

typedef struct aresta{
    int vertice1, vertice2;
    double peso;
    struct aresta *proximo;
}aresta;

int main(){
	int i, j = 0, n, ponto_aux, v1, v2, contador = 0, flag, fim, filhoE, filhoD;
	double p, agm = 0;

	aresta *g1 = NULL, *aloca, *aux;

	scanf("%d", &n);

	while(scanf("%d %d %lf", &v1, &v2, &p) != EOF){
		aloca = malloc(sizeof(aresta));
		aloca->vertice1 = v1;
		aloca->vertice2 = v2;
		aloca->peso = p;
		aloca->proximo = g1;
		g1 = aloca;
		++contador;
	}

	int lidos[n];
	aresta *heap[contador], *swap;

	for(i = 0; i < n; ++i){
		lidos[i] = -1;
	}
	aux = g1;
	for(i = 0; i < contador; ++i){
		flag = 0;
		heap[i] = aux;
		ponto_aux = i;
		do{
			if(ponto_aux != 0){
				if(ponto_aux % 2 == 0){	
					if(heap[(ponto_aux/2) - 1]->peso > heap[ponto_aux]->peso){
						swap = heap[ponto_aux/2];
						heap[ponto_aux/2] = heap[ponto_aux];
						heap[ponto_aux] = swap;
						ponto_aux = (ponto_aux/2) - 1;
					}
					else{
						flag = 1;
					}
				}
				else{
					if(heap[((ponto_aux + 1)/2) - 1]->peso > heap[ponto_aux]->peso){
						swap = heap[ponto_aux/2];
						heap[ponto_aux/2] = heap[ponto_aux];
						heap[ponto_aux] = swap;
						ponto_aux = ((ponto_aux + 1)/2) - 1;
					}
					else{
						flag = 1;
					}
				}
			}
			printf("9");
		}while(ponto_aux != 0 && flag != 1);
		printf("1");
		aux = aux->proximo;
	}

	fim = contador;
	for(i = 0; i < contador; ++i){
		flag = 0;
		if(lidos[heap[i]->vertice1] == -1){
			lidos[heap[i]->vertice1] = 1;
			++j;
			flag = 1;
		}
		if(lidos[heap[i]->vertice2] == -1){
			lidos[heap[i]->vertice2] = 1;
			++j;
			flag = 1;
		}
		if(flag == 1){
			agm += heap[i]->peso;	
		}

		heap[0] = heap[fim];
		--fim;
		ponto_aux = 0;
		filhoD = 2;
		filhoE = 1;
		while(ponto_aux <= fim && heap[filhoE]->peso < heap[ponto_aux]->peso || heap[filhoD]->peso < heap[ponto_aux]->peso){
			if(heap[filhoE]->peso < heap[filhoD]->peso){
				swap = heap[ponto_aux];
				heap[ponto_aux] = heap[filhoE];
				heap[filhoE] = swap;
				ponto_aux = filhoE;	
			}
			else{
				swap = heap[ponto_aux];
				heap[ponto_aux] = heap[filhoD];
				heap[filhoD] = swap;
				ponto_aux = filhoD;	
			}
			filhoE = ponto_aux * 2;
			filhoD = (ponto_aux * 2) + 1;
		}

		if(j == contador){
			printf("%f", &agm);
			return 0;
		}
	}



	return 0;
}
