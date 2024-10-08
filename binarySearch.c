/*
    Problema:
    https://judge.beecrowd.com/en/problems/view/1195

    Referência:
    https://github.com/marcosvianaap/estruturas-de-dados/tree/main/ED1/07%20-%20Arvore%20binaria
*/

#include <stdio.h>
#include <stdlib.h>

// Definição de um nó da árvore binária
typedef struct No {
    int valor;
    struct No *esquerda, *direita;
} No;

// Função para criar um novo nó
No* novoNo(int valor) {
    No* temp = (No*)malloc(sizeof(No));
    temp->valor = valor;
    temp->esquerda = temp->direita = NULL;
    return temp;
}

// Função para inserir um valor na árvore binária de busca
No* insere(No* raiz, int valor) {
    if (raiz == NULL) {
        return novoNo(valor);
    }

    if (valor < raiz->valor) {
        raiz->esquerda = insere(raiz->esquerda, valor);
    } else {
        raiz->direita = insere(raiz->direita, valor);
    }

    return raiz;
}

// Função para realizar a travessia em pré-ordem
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d", raiz->valor);
        if (raiz->esquerda != NULL || raiz->direita != NULL) printf(" ");
        preOrdem(raiz->esquerda);
        if (raiz->esquerda != NULL && raiz->direita != NULL) printf(" ");
        preOrdem(raiz->direita);
    }
}


// Função para realizar a travessia em-ordem
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

// Função para realizar a travessia em pós-ordem
void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        if (raiz->esquerda != NULL) printf(" ");
        posOrdem(raiz->direita);
        if (raiz->direita != NULL) printf(" ");
        printf("%d", raiz->valor);
    }
}

// Função principal
int main() {
    int C, N, valor;
    scanf("%d", &C);  // Lê o número de casos de teste

    for (int caso = 1; caso <= C; caso++) {
        scanf("%d", &N);  // Lê o número de elementos na árvore
        No* raiz = NULL;

        // Lê os elementos da árvore e insere-os
        for (int i = 0; i < N; i++) {
            scanf("%d", &valor);
            raiz = insere(raiz, valor);
        }

        // Imprime o caso
      
        printf("\nCase %d:\n", caso);

        // Travessia em pré-ordem
        printf("Pre.: ");
        preOrdem(raiz);
        printf("\n");

        // Travessia em-ordem
        printf("In..: ");
        emOrdem(raiz);
        printf("\n");

        // Travessia em pós-ordem
        printf("Post: ");
        posOrdem(raiz);
        printf("\n");
     
    }

    return 0;
}
