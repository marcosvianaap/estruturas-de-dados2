/*
    Baseado em :
    https://www.vivaolinux.com.br/script/Arvore-B

    Referência:
    https://www.youtube.com/watch?v=r6psF2NUMfg&ab_channel=Programa%C3%A7%C3%A3oDescomplicada%7CLinguagemC
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ordem da árvore B é 2
#define MIN_DEGREE 2

// Estrutura do nó da árvore B
struct BTreeNode {
    int *keys;   
    struct BTreeNode **children; 
    int numKeys;                 
    int isLeaf;                  
};
typedef struct BTreeNode BTreeNode;

// Estrutura da árvore B
struct BTree {
    BTreeNode *root; 
};
typedef struct BTree BTree;

// Cria e inicializa um novo nó
BTreeNode* createNode(int isLeaf) {
    BTreeNode* novoNo = malloc(sizeof(BTreeNode)); 
    novoNo->keys = malloc((MIN_DEGREE * 2 - 1) * sizeof(int)); 
    novoNo->children = malloc(MIN_DEGREE * 2 * sizeof(BTreeNode *)); 
    novoNo->numKeys = 0; 
    novoNo->isLeaf = isLeaf;
    return novoNo; 
}

// Função para dividir o filho de um nó
void splitChild(BTreeNode *parent, int index, BTreeNode *child) {
    BTreeNode *novoFilho;
    novoFilho = createNode(child->isLeaf);
    novoFilho->numKeys = MIN_DEGREE - 1; 

    // Move as últimas chaves do filho para o novo filho
    for (int i = 0; i < MIN_DEGREE - 1; i++) {
        novoFilho->keys[i] = child->keys[i + MIN_DEGREE];
    }

    // Move os filhos do filho se não for folha
    if (!child->isLeaf) {
        for (int i = 0; i < MIN_DEGREE; i++) {
            novoFilho->children[i] = child->children[i + MIN_DEGREE];
        }
    }

    // Atualiza o número de chaves do nó filho
    child->numKeys = MIN_DEGREE - 1;

    // Move os filhos do nó pai
    for (int i = parent->numKeys; i >= index + 1; i--) {
        parent->children[i + 1] = parent->children[i];
    }

    // Adiciona novo filho
    parent->children[index + 1] = novoFilho;

    // Move a chave do filho para o pai
    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    // Coloca chave no pai
    parent->keys[index] = child->keys[MIN_DEGREE - 1];
    // Aumenta o número de chaves do pai
    parent->numKeys++;
}

// Função para inserir uma nova chave
void insertNonFull(BTreeNode *node, int key) {
    int i = node->numKeys - 1;

    // Se for folha, insere a chave diretamente
    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            // Move as chaves maiores para a direita
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        // Se não for folha, procura o filho apropriado para inserir
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        // Se o filho estiver cheio, divide-o
        if (node->children[i]->numKeys == (MIN_DEGREE * 2 - 1)) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        // Chama recursivamente para inserir no filho correto
        insertNonFull(node->children[i], key);
    }
}

// Função para inserir uma nova chave na árvore B
void insert(BTree *tree, int key) {
    if (tree->root == NULL) {
        // Se a árvore estiver vazia, cria uma nova raiz
        tree->root = createNode(1); 
        tree->root->keys[0] = key; 
        tree->root->numKeys = 1; 
    } else {
        // Se a raiz estiver cheia, divide-a
        if (tree->root->numKeys == (MIN_DEGREE * 2 - 1)) {
            BTreeNode *novaRaiz = createNode(0);
            novaRaiz->children[0] = tree->root; 
            splitChild(novaRaiz, 0, tree->root);
            int i = 0;
            if (novaRaiz->keys[0] < key) {
                i++;
            }
            insertNonFull(novaRaiz->children[i], key); 
            tree->root = novaRaiz; 
        } else {
            insertNonFull(tree->root, key); 
        }
    }
}

// Função para percorrer a árvore B em ordem
void inorderTraversal(BTreeNode *node) {
    if (node != NULL) {
        for (int i = 0; i < node->numKeys; i++) {
            if (!node->isLeaf) {
                // Percorre os filhos à esquerda
                inorderTraversal(node->children[i]);
            }
            printf("%d ", node->keys[i]);
        }
        if (!node->isLeaf) {
            inorderTraversal(node->children[node->numKeys]);
        }
    }
}

// Função para buscar uma chave na árvore B
int search(BTreeNode *node, int key) {
    int i = 0;

    // Procura a posição da chave
    while (i < node->numKeys && key > node->keys[i]) {
        i++;
    }

    // Se encontrar a chave, retorna sucesso
    if (i < node->numKeys && node->keys[i] == key) {
        return 1;
    }

    // Se o nó for folha e não encontrar, retorna falha
    if (node->isLeaf) {
        return 0;
    }

    // Continua a busca no filho apropriado
    return search(node->children[i], key);
}

int main() {
    BTree* tree = malloc(sizeof(BTree));
    tree->root = NULL; 

    char comando[50];
    int valor;
    printf("Para utilizar digite: 'insere 10' \n");

    // Lê comandos de entrada
    while (fgets(comando, sizeof(comando), stdin) != NULL) {
        if (sscanf(comando, "insere %d", &valor) == 1) {
            insert(tree, valor);
        } else if (strcmp(comando, "percorre\n") == 0) {
            printf("Percurso da árvore B em ordem: ");
            inorderTraversal(tree->root);
            printf("\n");
        } else if (sscanf(comando, "busca %d", &valor) == 1) {
            if (search(tree->root, valor)) {
                printf("Valor %d encontrado!\n", valor);
            } else {
                printf("Valor %d não encontrado!\n", valor);
            }
        }
    }

    return 0;
}
