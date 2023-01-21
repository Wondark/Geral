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
	//Vert* Ve = procurarVert(L, N);
	// Verificar se a lista está vazia

	// faca um if com o inicio de L != NULL

    if (L->inicio == NULL){
		L->inicio = V;
		L->fim = L->inicio;
		L->inicio->N = N;

		L->tam++;
	} /*else if (Ve->N == N){
        printf("Não adicionado\n");
    }*/ else {
		L->fim->prox = V;
		L->fim = V;
		L->fim->N = N;

		L->tam++;
	}
}

/*void inserirVertIni(Lista* L){
    Vert *V;

    if (L->inicio == NULL){

    }
}*/

void inserirAresta(Vert* V, aresta* A, int N, int tam){

	// Verificar se está vazia
	if (V->ini == NULL){
		A->N = N;
		A->tam = tam;
		V->ini = A;
		V->fim = A;

		V->tam++;
	}else{
	    A->N = N;
		A->tam = tam;
		V->fim->prox = A;
		V->fim = A;

		V->tam++;
	}
}

// Procura Vertice e retorna um vertice
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
	printf("O vertice %d nao existe\n\n", N);
	return NULL;
}

//Remoções
//-------------------------------------------------------------//
//Remove Aresta desejada
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
		}
		A = B;
	}

}

//Remove Vertice desejado
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
		printf("\nVertice removido\n");
		return 1;
	}else{
		V1 = L->inicio;
		while(V1->prox != NULL){
			if(V1->prox->N == N){
				V1->prox = V->prox;
				free(V);
				L->tam--;
				printf("\nVertice removido\n");
				return 1;
			}
			V1 = V1->prox;
		}
	}
}

//Remove Vertice do inicio
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

//Imprimi Matriz de Adjacencia: 0 - Nao ha adjacencia, 1 - Ha adjacencia
void Adjacencia(Lista* L){
    int i, j;
    int M[L->tam][L->tam];
    Vert* V = L->inicio;
    aresta* A;
    //Zerando pontos de impossibilidade

    if (L->inicio == NULL){
        printf("O grafo esta vazio\n");
    } else {
        printf("   ");
        for (i=0; i < (L->tam); i++){
            printf("%d  ", V->N);
            for(j=0; j < (L->tam); j++){
                M[i][j] = 0;
            }
            V = V->prox;
        }
        printf("\n");

        i=0;
        j=0;
        V = L->inicio;
        while (V != NULL){
            A = V->ini;
            while (A != NULL){
                j = procurarVert2(L, A->N);
                M[i][j] = 1;
                A = A->prox;
            }
            i++;
            V = V->prox;
        }

        V = L->inicio;
        for (i=0; i < (L->tam); i++){
            printf("%d  ", V->N);
            for(j=0; j < (L->tam); j++){
                printf("%d  ", M[i][j]);
            }
            V = V->prox;
            printf("\n");
        }
    }
    printf("\n");
}

// Busca em Largura
void Largura(Lista* L, Vert* V){
    Vert *Ar[L->tam +1], *G[L->tam +1];
    int i=0, j=0;
    Vert *Ve, *Vi;
    aresta* A;

    //Transformando todos os vertices em nao visitados
    if (V->ini != NULL){
        Ve = L->inicio;
        while (Ve != NULL){
            Ve->Tri = -1;
            Ve = Ve->prox;
        }
        for (i=0; i < L->tam+1; i++){
            Ar[i] = NULL;
            G[i] = NULL;
        }


        i = 0;
        Ar[i] = V;
        G[i] = V;
        Ve = V;
        i++;
        while(Ar[j] != NULL){
            A = Ve->ini;
            Ve->Tri = 1;
            while(A != NULL){
                Vi = procurarVert(L, A->N);
                if (Vi->Tri == -1){
                    Vi->Tri = 0;
                    Ar[i] = Vi;
                    G[i] = Vi;
                    A = A->prox;
                    i++;
                } else {
                    A = A->prox;
                }
            }
            Ar[j] = NULL;
            j++;
            Ve = Ar[j];
        }

// Imprimir a sequencia em largura
        j=0;
        while (G[j] != NULL){
            printf("%d ", G[j]->N);
            j++;
        }
        printf("\n");
    } else {
        printf("Nao e possivel, vertice sem arestas\n");
    }


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

    inserirAresta(procurarVert(L, 1), novaAresta(), 5, 10);
    inserirAresta(procurarVert(L, 1), novaAresta(), 4, 9);
    inserirAresta(procurarVert(L, 1), novaAresta(), 2, 7);
    inserirAresta(procurarVert(L, 1), novaAresta(), 10, 8);
    inserirAresta(procurarVert(L, 1), novaAresta(), 8, 9);
    inserirAresta(procurarVert(L, 1), novaAresta(), 6, 8);
    inserirAresta(procurarVert(L, 2), novaAresta(), 3, 4);
    inserirAresta(procurarVert(L, 2), novaAresta(), 4, 5);
    inserirAresta(procurarVert(L, 2), novaAresta(), 1, 7);
    inserirAresta(procurarVert(L, 2), novaAresta(), 10, 9);
    inserirAresta(procurarVert(L, 2), novaAresta(), 9, 9);
    inserirAresta(procurarVert(L, 3), novaAresta(), 5, 4);
    inserirAresta(procurarVert(L, 3), novaAresta(), 4, 1);
    inserirAresta(procurarVert(L, 3), novaAresta(), 2, 4);
    inserirAresta(procurarVert(L, 4), novaAresta(), 1, 9);
    inserirAresta(procurarVert(L, 4), novaAresta(), 2, 5);
    inserirAresta(procurarVert(L, 4), novaAresta(), 3, 1);
    inserirAresta(procurarVert(L, 4), novaAresta(), 5, 3);
    inserirAresta(procurarVert(L, 5), novaAresta(), 3, 4);
    inserirAresta(procurarVert(L, 5), novaAresta(), 4, 3);
    inserirAresta(procurarVert(L, 5), novaAresta(), 1, 10);
    inserirAresta(procurarVert(L, 5), novaAresta(), 6, 18);
    inserirAresta(procurarVert(L, 6), novaAresta(), 5, 18);
    inserirAresta(procurarVert(L, 6), novaAresta(), 1, 8);
    inserirAresta(procurarVert(L, 6), novaAresta(), 8, 9);
    inserirAresta(procurarVert(L, 6), novaAresta(), 7, 9);
    inserirAresta(procurarVert(L, 7), novaAresta(), 6, 9);
    inserirAresta(procurarVert(L, 7), novaAresta(), 8, 3);
    inserirAresta(procurarVert(L, 7), novaAresta(), 9, 6);
    inserirAresta(procurarVert(L, 8), novaAresta(), 6, 9);
    inserirAresta(procurarVert(L, 8), novaAresta(), 1, 9);
    inserirAresta(procurarVert(L, 8), novaAresta(), 10, 2);
    inserirAresta(procurarVert(L, 8), novaAresta(), 9, 4);
    inserirAresta(procurarVert(L, 8), novaAresta(), 7, 3);
    inserirAresta(procurarVert(L, 9), novaAresta(), 7, 6);
    inserirAresta(procurarVert(L, 9), novaAresta(), 8, 4);
    inserirAresta(procurarVert(L, 9), novaAresta(), 10, 2);
    inserirAresta(procurarVert(L, 9), novaAresta(), 2, 9);
    inserirAresta(procurarVert(L, 10), novaAresta(), 1, 8);
    inserirAresta(procurarVert(L, 10), novaAresta(), 2, 9);
    inserirAresta(procurarVert(L, 10), novaAresta(), 9, 2);
    inserirAresta(procurarVert(L, 10), novaAresta(), 8, 2);

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
			printf("Informe as duas vertices inter-ligadas e o tamanho da aresta (Valores separados por espaco: ");
			scanf("%d %d %d", &N, &M, &tam);
			inserirAresta(procurarVert(L, N), novaAresta(), M, tam);
			inserirAresta(procurarVert(L, M), novaAresta(), N, tam);
			printf("\n");

		}else if (aux == 3){
		    printf("\n");
			imprimir(L);

		}else if(aux == 4){
		    printf("\nInforme o vertice a ser removido: ");
			scanf("%d", &N);
			printf("\n");
			if (procurarVert(L, N) != NULL){
				removerVert(L, N);
			}
			printf("\n");

		}else if(aux == 5){
			printf("Informe as duas vertices para se desligarem: ");
			scanf("%d %d", &N, &M);
			removerAresta(procurarVert(L, N), M);
			removerAresta(procurarVert(L, M), N);

		} else if (aux == 6){
            Grau(L);

		} else if (aux == 7){
            printf("Informe o Vertice para calcular o grau: ");
            scanf("%d", &N);
            Ve = procurarVert(L, N);
            if (Ve != NULL){
            printf("Vertice %d: Grau %d\n\n", N, Ve->tam);
            }
		} else if (aux == 8){
            Adjacencia(L);
		} else if (aux == 9){
		    printf("\nQual o vertice a ser iniciado: ");
		    scanf("%d", &N);
		    printf("\n");
            Largura(L, procurarVert(L, N));
            printf("\n");
		}


		printf("1- Inserir Vertice\n");
		printf("2- Inserir Aresta\n");
		printf("3- Visualizar Grafo\n");
		printf("4- Remover Vertice\n");
		printf("5- Remover Aresta\n");
		printf("6- Visualizar Grau de Todos os Vertices\n");
		printf("7- Visualizar Grau de um Vertice\n");
		printf("8- Visualizar Matriz de Adjacencia\n");
		printf("9- Busca em largura\n");
		printf("10- Sair\n");
		printf("\n");
		printf("\n%d\n", L->tam);
		aux = -1;
	}while(scanf("%d", &aux) == 1 && aux < 10);
	return 0;
}


