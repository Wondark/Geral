#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

typedef struct _Lista Lista;
typedef struct _Vert Vert;
typedef struct _aresta aresta;
Vert* procurarVert(Lista* L, int N);

//Estrutura Lista
//---------------------------------------------------------------//

struct _Lista{
	Vert* inicio;
	Vert* fim;
	int tam;
};

struct _Vert{
	Vert* prox;
	aresta* ini;
	aresta* fim;
	int tam;
	int N;
	int Tri;
};

struct _aresta{
	aresta* prox;
	aresta* ant;
	int N;
	int tam;
};

//Inicializando a  Lista
//---------------------------------------------------------------//

Lista* novaLista(){
	Lista* L = (Lista*) malloc(sizeof(Lista));
	L->inicio = NULL;
	L->fim = NULL;
	L->tam = 0;

	return L;
}

Vert* novoVert(){
	Vert* V = (Vert*) malloc(sizeof(Vert));
	V->prox = NULL;
	V->ini = NULL;
	V->fim = NULL;
	V->tam = 0;

	return V;
}

aresta* novaAresta(){
	aresta* A = (aresta*) malloc(sizeof(aresta));
	A->prox = NULL;
	A->ant = NULL;
    A->tam = 0;
}

// Inserções
//-----------------------------------------------------------//

void inserirVertice(Lista* L, Vert* V, int N){
    if (L->inicio == NULL){
		L->inicio = V;
		L->fim = L->inicio;
		L->inicio->N = N;

		L->tam++;

	} else if (procurarVert(L, N) != NULL){
        printf("Esse vertice ja existe.\n\n");
        return NULL;

	} else {
		L->fim->prox = V;
		L->fim = V;
		L->fim->N = N;

		L->tam++;
	}
}


void inserirAresta(Vert* V, aresta* A, int N){

	// Verifica se está vazia
	if (V->ini == NULL){
		A->N = N;
		V->ini = A;
		V->fim = A;

		V->tam++;
	}else{
	    A->N = N;
		V->fim->prox = A;
		V->fim = A;

		V->tam++;
	}
}

// Buscas - Vertices e Arestas
Vert* procurarVert(Lista* L, int N){
	Vert* Ve = L->inicio;
	if (L->inicio == NULL){
		printf("O grafo esta vazio\n\n");
		return NULL;
	}else{
		while (Ve != NULL){
			if (Ve->N == N)
				return Ve;
			Ve = Ve->prox;
		}
	}
	return NULL;
}

aresta* procuraAresta(Vert* Ve, int N){
    aresta* A = Ve->ini;

    if (A == NULL)
        return NULL;
    else{
        while (A != NULL){
            if (A->N == N)
                return A;
            A = A->prox;
        }
    }
    return NULL;
}

//Remoções
//-------------------------------------------------------------//
//Aresta
int removerAresta(Vert* V, int N){
	if (V->ini == NULL){
		return 0;
	}

	aresta* A = V->ini;
	aresta* B = A->prox;
	if (A->N == N){
			V->ini = B;
			free(A);
			V->tam--;
			return 1;
	}
	while (A->prox != NULL){
		B = A->prox;
		if(A->prox->N == N){
			A->prox = B->prox;
			free(B);
			V->tam--;
			return 1;
		} else if (A->prox == NULL)
            return 0;
		A = B;
	}
}

//Vertice
int removerVert(Lista* L, int N){
	Vert* V = procurarVert(L, N);
	int M;
	if (V == NULL)
		return 0;

	Vert* V1;
	aresta* A = V->ini;
	while (A != NULL){
		removerAresta(procurarVert(L, A->N), N);
		M = A->N;
		A = A->prox;
		removerAresta(V, M);
	}

	if(L->inicio->N == V->N){
		L->inicio = L->inicio->prox;
		free(V);
		L->tam--;
		return 1;
	}else{
		V1 = L->inicio;
		while(V1->prox != NULL){
			if(V1->prox->N == N){
				V1->prox = V->prox;
				free(V);
				L->tam--;
				return 1;
			}
			V1 = V1->prox;
		}
	}
}

//Vertice Inicio
Vert* RemoveIni(Lista* L){

    if (L->inicio != NULL){
        L->inicio = L->inicio->prox;
        if (L->inicio == NULL)
            L->fim = L->inicio;
        return L->inicio;
    } else {
        return NULL;
    }
}

//Imprimir Grafo
//---------------------------------------------------------------------//
//Imprime Toda a lista
void imprimir(Lista* L){
	Vert* V = L->inicio;
	aresta* A;
	while (V != NULL){
		printf("%d: ", V->N);
		A = V->ini;
		while (A != NULL){
			printf("%d ", A->N);
			A = A->prox;
		}
		V = V->prox;
	printf("\n");
	}
	printf("\n");
}

// Informar grau de todos os vertices
void Grau(Lista* L){
    Vert* V = L->inicio;

    if (L->inicio == NULL){
        printf("Grafo vazio.\n\n");
    } else {
        while (V != NULL){
        printf("Vertice %d: Grau %d\n", V->N, V->tam);
        V = V->prox;
        }
    }
    printf("\n");
}

// Procurar vertice para ajudar na Matriz de adjacencia
int procurarVert2(Lista* L, int N){
	Vert* Ve = L->inicio;
	int i=0;

    while (Ve != NULL){
        if (Ve->N == N)
            return i;
        i++;
        Ve = Ve->prox;
    }
    printf("|||");
}

// Dando valores para o grafo
void IniciarGrafo(Lista* L){

    inserirVertice(L, novoVert(), 1);
    inserirVertice(L, novoVert(), 2);
    inserirVertice(L, novoVert(), 3);
    inserirVertice(L, novoVert(), 4);
    inserirVertice(L, novoVert(), 5);
    inserirVertice(L, novoVert(), 6);
    inserirVertice(L, novoVert(), 7);
    inserirVertice(L, novoVert(), 8);
    inserirVertice(L, novoVert(), 9);
    inserirVertice(L, novoVert(), 10);

    inserirAresta(procurarVert(L, 1), novaAresta(), 5);
    inserirAresta(procurarVert(L, 1), novaAresta(), 4);
    inserirAresta(procurarVert(L, 1), novaAresta(), 2);
    inserirAresta(procurarVert(L, 1), novaAresta(), 10);
    inserirAresta(procurarVert(L, 1), novaAresta(), 8);
    inserirAresta(procurarVert(L, 1), novaAresta(), 6);
    inserirAresta(procurarVert(L, 2), novaAresta(), 3);
    inserirAresta(procurarVert(L, 2), novaAresta(), 4);
    inserirAresta(procurarVert(L, 2), novaAresta(), 1);
    inserirAresta(procurarVert(L, 2), novaAresta(), 10);
    inserirAresta(procurarVert(L, 2), novaAresta(), 9);
    inserirAresta(procurarVert(L, 3), novaAresta(), 5);
    inserirAresta(procurarVert(L, 3), novaAresta(), 4);
    inserirAresta(procurarVert(L, 3), novaAresta(), 2);
    inserirAresta(procurarVert(L, 4), novaAresta(), 1);
    inserirAresta(procurarVert(L, 4), novaAresta(), 2);
    inserirAresta(procurarVert(L, 4), novaAresta(), 3);
    inserirAresta(procurarVert(L, 4), novaAresta(), 5);
    inserirAresta(procurarVert(L, 5), novaAresta(), 3);
    inserirAresta(procurarVert(L, 5), novaAresta(), 4);
    inserirAresta(procurarVert(L, 5), novaAresta(), 1);
    inserirAresta(procurarVert(L, 5), novaAresta(), 6);
    inserirAresta(procurarVert(L, 6), novaAresta(), 5);
    inserirAresta(procurarVert(L, 6), novaAresta(), 1);
    inserirAresta(procurarVert(L, 6), novaAresta(), 8);
    inserirAresta(procurarVert(L, 6), novaAresta(), 7);
    inserirAresta(procurarVert(L, 7), novaAresta(), 6);
    inserirAresta(procurarVert(L, 7), novaAresta(), 8);
    inserirAresta(procurarVert(L, 7), novaAresta(), 9);
    inserirAresta(procurarVert(L, 8), novaAresta(), 6);
    inserirAresta(procurarVert(L, 8), novaAresta(), 1);
    inserirAresta(procurarVert(L, 8), novaAresta(), 10);
    inserirAresta(procurarVert(L, 8), novaAresta(), 9);
    inserirAresta(procurarVert(L, 8), novaAresta(), 7);
    inserirAresta(procurarVert(L, 9), novaAresta(), 7);
    inserirAresta(procurarVert(L, 9), novaAresta(), 8);
    inserirAresta(procurarVert(L, 9), novaAresta(), 10);
    inserirAresta(procurarVert(L, 9), novaAresta(), 2);
    inserirAresta(procurarVert(L, 10), novaAresta(), 1);
    inserirAresta(procurarVert(L, 10), novaAresta(), 2);
    inserirAresta(procurarVert(L, 10), novaAresta(), 9);
    inserirAresta(procurarVert(L, 10), novaAresta(), 8);

}
//A MAIN
//------------------------------------------------------------//
int main(void){
	Lista* L = novaLista();
	int aux = 0;
	int N, M;
	int tam;
	Vert* Ve;

	IniciarGrafo(L);
	do{
		if(aux == 1){
			printf("Informe numero do Vertice: ");
			scanf("%d", &N);
			inserirVertice(L, novoVert(), N);

		}else if (aux == 2){
			printf("Informe as duas vertices interligadas e o tamanho da aresta (Valores separados por espaco): ");
			scanf("%d %d", &N, &M);
			if (!(procurarVert(L, N) == NULL || procurarVert(L, M) == NULL || M == N || procuraAresta(procurarVert(L, M), N) != NULL)){
                inserirAresta(procurarVert(L, N), novaAresta(), M);
                inserirAresta(procurarVert(L, M), novaAresta(), N);
                printf("\n");
			}else
                printf("Um dos vertices nao existem ou ja coexistem.\n\n");

		}else if (aux == 3){
		    printf("\n");
			imprimir(L);

		}else if(aux == 4){
		    printf("\nInforme o vertice a ser removido: ");
			scanf("%d", &N);
			printf("\n");
			if (procurarVert(L, N) != NULL){
				removerVert(L, N);
				printf("Vertice removido.\n");
			} else
                printf("O vertice nao existe.\n");
			printf("\n");

		}else if(aux == 5){
			printf("Informe os dois vertices para se desligarem: ");
			scanf("%d %d", &N, &M);
			if (procurarVert(L, N) != NULL && procurarVert(L, M) != NULL){
                removerAresta(procurarVert(L, N), M);
                removerAresta(procurarVert(L, M), N);
			}
            printf("\n");
		} else if (aux == 6)
            Grau(L);


		printf("1- Inserir Vertice\n");
		printf("2- Inserir Aresta\n");
		printf("3- Visualizar Grafo\n");
		printf("4- Remover Vertice\n");
		printf("5- Remover Aresta\n");
		printf("6- Visualizar Grau de Todos os Vertices\n");
		printf("7- Sair\n");
		printf("\n");

		//printf("\n%d\n", L->tam);
		aux = -1;
	}while(scanf("%d", &aux) == 1 && aux < 7);
	return 0;
}


