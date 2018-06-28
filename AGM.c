#include <stdio.h>
#include <stdlib.h> 


typedef struct noh Noh;
typedef struct fila Fila;
typedef struct grafo Grafo;
typedef struct aresta Aresta;

typedef struct noh{
    int chave;
    double peso;
    Noh *proximo;
} Noh; 

typedef struct fila{
    int tamanho;
    Noh *inicio;
    Noh *fim;
} Fila; 

typedef struct grafo{
    int n;
    Fila** V;
} Grafo;

typedef struct aresta{
	int u;
	int v;
	double peso;
}Aresta;


void enfila(Fila* fila, int nova_chave, double novo_peso){                        
    if (fila->tamanho == 0){                                    
        fila->fim = (Noh*) malloc(sizeof(Noh));                    
        fila->inicio = (Noh*) malloc(sizeof(Noh));                
        fila->fim->chave = nova_chave;
        fila->fim->peso = novo_peso;                           
        fila->fim->proximo = NULL;                                
        fila->inicio = fila->fim;                                
    }else{                                                        
        Noh* aux = fila->fim;                                    
        aux->proximo = (Noh*) malloc(sizeof(Noh));                
        aux->proximo->chave = nova_chave;
        aux->proximo->peso = novo_peso;                        
        aux->proximo->proximo = NULL;                            
        fila->fim = aux->proximo;                                
    }                                                            

    fila->tamanho++;                                            
}       

int desenfila(Fila* fila){                                        
    if (fila->tamanho == 0)                                        
    {                                                            
        return -1;                                                
    }                                                            
    int chave = fila->inicio->chave;                            
    Noh* aux = fila->inicio;
    fila->inicio = fila->inicio->proximo;                         
    fila->tamanho--;                    
    free(aux);                        
    return chave;                                                
}

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


int main(int argc, char const *argv[]){
	int n, v1, v2, m = 0;
	double peso;
	Noh* u, *v;
	Grafo grafo;


    scanf("dl\nformat=edgelist1\nn=%d\ndata:", &n);
    //scanf("%d\n",&n);
    grafo.n = n;
    
    int atingido[n];
    Aresta arestas[n*n];
   // int pai[n];
    double somaE= 0.0;

    grafo.V = (Fila **) malloc(n*sizeof(Fila*));
    for (int i = 0; i < n; ++i){
        grafo.V[i] = (Fila *) malloc(sizeof(Fila));
        grafo.V[i]->tamanho = 0;
        grafo.V[i]->inicio = NULL;
        grafo.V[i]->fim = NULL;
    	
    	atingido[i] = 0;
    	//pai[i] = -1;
    }

    while(scanf("%d %d %lf", &v1, &v2, &peso) == 3){
        enfila(grafo.V[v1-1], v2-1, peso);
        enfila(grafo.V[v2-1], v1-1, peso);

    }

// PRIM

   	Noh H[n];
   	int n_H = 0;

   	atingido[0] = 1;
	v = grafo.V[0]->inicio;
   	for(int i = 0; i < grafo.V[0]->tamanho; i++){
   		atingido[v->chave] = 1;
   		incluirHeap(H, v->chave, v->peso, &n_H);
   		


   		v = v->proximo;
   	}

   	Noh aux;
   	while(n_H > 0){

   		aux = removerMin(H, &n_H);
   		u = &aux;

   		somaE += u->peso;
   		atingido[u->chave] = 2;
   		v = grafo.V[u->chave]->inicio;
   		for (int i = 0; i < grafo.V[u->chave]->tamanho && v != NULL; i++){

   			if(atingido[v->chave] == 0){
   				atingido[v->chave] = 1;
   				incluirHeap(H, v->chave, v->peso, &n_H);


   			}else{
   				int iv = encontrarHeap(H, v->chave, &n_H);
   				if(iv >= 0 && v->peso < H[iv].peso){
   					alterarPrio(H, iv, v->peso, &n_H);

   				}
   			}
   			v = v->proximo;
   		}
   	}

   	printf("%.3lf\n", somaE);


    


	return 0;
}

