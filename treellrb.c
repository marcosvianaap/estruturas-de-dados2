/*
    Baseado em:
    https://www.youtube.com/watch?v=DaWNuijRRFY&list=PL8iN9FQ7_jt6XjYc0H01AVJoCePsiSNEq

   Árvores Rubro-Negras (Red-Black Trees)
    - Árvore balanceada que possui nós com um atributo de cor, que pode ser vermelho ou preto.
    - A raíz é sempre preta.
    - Todas as folhas são pretas.
    - Não há dois nós vermelhos adjacentes.
    - Busca, inserção e remoção com complexidade O(log n).
    - Todos os caminhos de algum nó para suas folhas contêm o mesmo número de nós negros
    - Os dois filhos de um nó vermelho são pretos.
    
*/

#include <stdio.h>
#include <stdlib.h>


// Possui balanceamanto mais a esquerda

#define RED 1
#define BLACK 0

struct No {
    int dado;
    struct No* esq;
    struct No* dir;
    int cor;
    
};
typedef struct No No;

//funcao auxiliar para balanceamento;
int cor(No* no){
    if (no == NULL){
        return BLACK;
    } 
    return no->cor;
    
} 

// funcao administrativa para troca de cores, nao altera estrutura ou dados;
void trocaCor(No* no){
    no->cor = !no->cor;
    if (no->esq != NULL){
        no->esq->cor = !no->esq->cor;
    }
    if (no->dir != NULL){
        no->dir->cor = !no->dir->cor;
    }
}

//funcao para rotacionar a esquerda;
No* rotEsq(No* no_a){
    No* no_b = no_a->dir;
    no_a->dir = no_b->esq;
    no_b->esq = no_a;
    no_b->cor = no_a->cor;
    no_a->cor = RED;
    return no_b;
}

//funcao para rotacionar a direita;
No* rotDir(No* no_a){
    No* no_b = no_a->esq;
    no_a->esq = no_b->dir;
    no_b->dir = no_a;
    no_b->cor = no_a->cor;
    no_a->cor = RED;
    return no_b;
}

No* balancear(No* no) {
    // Se o nó da direita é vermelho e o nó da esquerda não é vermelho, rotacione à esquerda
    if (cor(no->dir) == RED) {
        no = rotEsq(no);
    }

    // Se dois nós consecutivos à esquerda são vermelhos, rotacione à direita
    if (cor(no->esq) == RED && cor(no->esq->esq) == RED) {
        no = rotDir(no);
    }

    // Se ambos os filhos são vermelhos, troca as cores
    if (cor(no->esq) == RED && cor(no->dir) == RED) {
        trocaCor(no);
    }
  
    return no;
}

No* insert(No* no, int valor, int *resposta) {
    if (no == NULL) {
        No* newNode = (No*)malloc(sizeof(No));
        if (newNode == NULL) {
            *resposta = 0;
            return NULL;
        }
        newNode->dado = valor;
        newNode->cor = RED;
        newNode->dir = NULL;
        newNode->esq = NULL;
        *resposta = 1;
        return newNode;
    }

    if (valor < no->dado) {
        no->esq = insert(no->esq, valor, resposta);
    } else if (valor > no->dado) {
        no->dir = insert(no->dir, valor, resposta);
    } else {
        // Valor já existe
        *resposta = 0;
        return no;
    }

    no = balancear(no);

    return no;
}

// Função para calcular a altura da árvore;
int altura(No* no){
    if (no == NULL){
        return 0;
    } 
    int altura_esq = altura(no->esq);
    int altura_dir = altura(no->dir);
    // o perador ternario "?" é utilizado para retornar a maior altura de subarvores;
    return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
}

// Função para contar os nós vermelhos e pretos;
void contarNos(No* no, int *vermelhos, int *pretos){
    //Não faz nada se o nó for nulo
    if (no == NULL) {
        return; 
    }

    // Incrementando a contagem de nós
    if (cor(no) == RED){
        (*vermelhos)++;
    }
    else {
        (*pretos)++;
    }
    contarNos(no->esq, vermelhos, pretos);
    contarNos(no->dir, vermelhos, pretos);
}

// Função para fazer percurso em ordem
void percursoEmOrdem(No* no){
    if (no == NULL) {
        return;
    }
    percursoEmOrdem(no->esq);
    printf("%d ", no->dado);
    percursoEmOrdem(no->dir);
}

int main() {
    No* raiz = NULL;
    int resposta;
    
    // Inserindo os valores na árvore
    int valores[] = {12, 5, 15, 3, 10, 13, 17, 4, 7, 11, 14, 6, 8};
    int n = sizeof(valores) / sizeof(valores[0]);
    
    for (int i = 0; i < n; i++) {
        raiz = insert(raiz, valores[i], &resposta);
    }

    // 1. Percurso em ordem
    printf("Percurso em ordem: ");
    percursoEmOrdem(raiz);
    printf("\n");

    // 2. Raiz da árvore
    printf("Raiz: %d\n", raiz->dado);

    // 3. Altura da árvore
    printf("Altura: %d\n", altura(raiz));

    // 4. Contar nós vermelhos e pretos
    int vermelhos = 0, pretos = 0;
    contarNos(raiz, &vermelhos, &pretos);
    printf("Quantidade de nós vermelhos: %d\n", vermelhos);
    printf("Quantidade de nós pretos: %d\n", pretos);

    return 0;
}
