#include <stdio.h>
#include <stdlib.h>

int* alocaVetor(int qtd);
int** alocaMatriz(int linhas, int colunas);

int main() {
    int** matriz = alocaMatriz(4,4);
    
}

int *alocaVetor(int qtd) {
    int* vetor = (int*)malloc(qtd * sizeof(int));
    int i;
    for(i = 0; i < qtd; i++) {
        *(vetor + i) = 0;
        printf("%d\n",*(vetor + i));
    }
    return vetor;
}

int** alocaMatriz(int linhas, int colunas) {
    int** matriz;
    int i;
    for(i = 0; i < linhas; i++) {
        *(*(matriz + i)) = alocaVetor(colunas);
    }
    return matriz;
}