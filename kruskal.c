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
    fila->inicio = fila->inicio->proximo;                         
    fila->tamanho--;                                            
    return chave;                                                
}


int main(int argc, char const *argv[]){
	int n,u,v, v1, v2, o, peso, m = 0;
    
    Grafo grafo;


    // scanf("dl\nformat=edgelist1\nn=%d\ndata:", &n);
    scanf("%d\n",&n);
    grafo.n = n;
    
    int atingido[n];

    grafo.V = (Fila **) malloc(n*sizeof(Fila*));
    for (int i = 0; i < n; ++i){
        grafo.V[i] = (Fila *) malloc(sizeof(Fila));
        grafo.V[i]->tamanho = 0;
        grafo.V[i]->inicio = NULL;
        grafo.V[i]->fim = NULL;
    }

    while(scanf("%d %d %f", &v1, &v2, &peso) == 3){
        enfila(grafo.V[v1-1], v2-1, peso);
     //   enfila(grafo.V[v2-1], v1-1, peso);
        m++;
    }

    // algoritmo kruskal
    // Criando grafo T
 //    Grafo T;
 //    T.V = (Fila **) malloc(n*sizeof(Fila*));
 //    for (int i = 0; i < n; ++i){
 //        T.V[i] = (Fila *) malloc(sizeof(Fila));
 //        T.V[i]->tamanho = 0;
 //        T.V[i]->inicio = NULL;
 //        T.V[i]->fim = NULL;
 //    }
	// // Criando vetor L[x] para Lista (registro Conjunto)
 //    Fila* L[n];
 //    for (int i = 0; i < n; ++i){
 //    	Fila c = {0, NULL, NULL};
 //    	enfila(&c, i, 0);
 //    	L[i] = &c;
 //    }




    // tentativa
    Aresta arestas[m];
    Noh* no;
    int j = 0;
    for (int i = 0; i < n; ++i){
    	no = grafo.V[i]->inicio;

   		while(no != NULL){
   			arestas[j].u = i;
   			arestas[j].v = no->chave;
   			arestas[j].peso = no->peso;

   			no = no->proximo;
   			j++;
   		}
    }
    

   

    



	return 0;
}