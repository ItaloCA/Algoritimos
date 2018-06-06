#include <stdio.h>
#include <stdlib.h>    

typedef struct noh Noh;
typedef struct fila Fila;
typedef struct grafo Grafo;

typedef struct noh{
    int chave;
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

void enfila(Fila* fila, int nova_chave){                        
    if (fila->tamanho == 0){                                    
        fila->fim = (Noh*) malloc(sizeof(Noh));                    
        fila->inicio = (Noh*) malloc(sizeof(Noh));                
        fila->fim->chave = nova_chave;                            
        fila->fim->proximo = NULL;                                
        fila->inicio = fila->fim;                                
    }else{                                                        
        Noh* aux = fila->fim;                                    
        aux->proximo = (Noh*) malloc(sizeof(Noh));                
        aux->proximo->chave = nova_chave;                        
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

int main(){
    int n,u,v, v1, v2, o;
    
    Grafo grafo;


    scanf("dl\nformat=edgelist1\nn=%d\ndata:", &n);
    // scanf("%d\n",&n);
    grafo.n = n;
    
    int atingido[n];

    grafo.V = (Fila **) malloc(n*sizeof(Fila*));
    for (int i = 0; i < n; ++i){
        grafo.V[i] = (Fila *) malloc(sizeof(Fila));
        grafo.V[i]->tamanho = 0;
        grafo.V[i]->inicio = NULL;
        grafo.V[i]->fim = NULL;
    }

    while(scanf("%d %d", &v1, &v2) == 2){
        enfila(grafo.V[v1-1], v2-1);
        enfila(grafo.V[v2-1], v1-1);
        
    }

    // Funcao Principal

    for (int i = 0; i < grafo.n; ++i){
        atingido[i] = -1;
    }

    for (o = 0; o < n; ++o){
        if (atingido[o] == -1){


            atingido[o] = o;
            Fila fila = {0, NULL, NULL};
            
            //enfila o em F
            enfila(&fila, o);

            //Busca em Largura
            // while(F não estiver vazia){
            while(fila.tamanho != 0){
            //     //desenfile um vertice u de F
                u = desenfila(&fila);
            //     //adiciona u em componente
                atingido[u] = o;
            //     //para cada v pertencendo a N(u)
                if(grafo.V[u]->inicio != NULL){

                    for(Noh*p = grafo.V[u]->inicio; p != NULL; p = p->proximo){
                        //Se não atingido[v]{
                        if(atingido[p->chave] == -1){
                            //atingido[v] = verdadeiro
                            atingido[p->chave] = o;
                            //enfile v em F
                        enfila(&fila, p->chave);
                        }
                    }
                }
            }

        // Saida
            


            printf("%d", o+1);
            for (int i = o+1; i < n; ++i){
                if(atingido[i] == o)
                    printf(" %d", i+1);
            }
            printf("\n");
        }

    }
    
    return 0;
}
