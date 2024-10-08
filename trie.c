/*
    Baseado em:
    https://www.youtube.com/watch?v=Spmw4hTo7ek&t=2514s&ab_channel=Computa%C3%A7%C3%A3ocomProf.Foleis

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_OFFSET 32
#define ASCII_RANGE 95  // ASCII de 32 a 126

// Estrutura da Trie
struct TrieNode {
    struct TrieNode *children[ASCII_RANGE];
    int isEndOfWord;
    char *password;
};
typedef struct TrieNode TrieNode;

// Inicializa um nó da Trie
TrieNode* initNode() {
    TrieNode *node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = 0;
    node->password = NULL;

    for (int i = 0; i < ASCII_RANGE; i++) {
        node->children[i] = NULL;
    }

    return node;
}

// Função para inserir uma senha na Trie
void insert(TrieNode* root, const char *password) {
    TrieNode *current = root;

    // Mantém o ponteiro original
    const char *original_password = password;
    while (*password) {
        int index = *password - ASCII_OFFSET;
        if (index < 0 || index >= ASCII_RANGE) {
            return;
        }
        if (!current->children[index]) {
            current->children[index] = initNode();
        }
        current = current->children[index];
        password++;
    }
    current->isEndOfWord = 1;

    // Armazena a senha completa no nó final
    current->password = strdup(original_password);
}

// Função recursiva para buscar e imprimir senhas com determinado prefixo
int printPasswordsWithPrefix(TrieNode *root) {
    int found = 0;

    if (root->isEndOfWord && root->password) {
        printf("%s \n", root->password);
        found = 1;
    }

    for (int i = 0; i < ASCII_RANGE; i++) {
        if (root->children[i]) {
            found |= printPasswordsWithPrefix(root->children[i]);
        }
    }

    return found;
}

// Função para buscar prefixo na Trie e imprimir todas as senhas que coincidem
void searchPrefix(TrieNode *root, const char *prefix) {
    TrieNode *current = root;
    while (*prefix) {
        int index = *prefix - ASCII_OFFSET;
        if (index < 0 || index >= ASCII_RANGE || !current->children[index]) {
            printf("Nenhuma senha encontrada com esse prefixo.\n");
            return;
        }
        current = current->children[index];
        prefix++;
    }

    if (!printPasswordsWithPrefix(current)) {
        printf("Nenhuma senha encontrada com esse prefixo.\n");
    } else {
        // Para garantir que a saída fique organizada
        printf("\n");
    }
}

int main() {
    TrieNode *root = initNode();
    char password[100];
    
    // Abre o arquivo rockyou-menor.txt para inserir senhas na Trie
    FILE *file = fopen("rockyou-menor.txt", "r");

    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo de senhas.\n");
        return 1;
    }

    // Insere senhas na Trie
    int counter = 0;
    while (fgets(password, sizeof(password), file)) {
        password[strcspn(password, "\n")] = '\0';  // Remove newline
        insert(root, password);
        counter++;
    }
    

    
    // Realiza consultas de prefixos a partir da entrada padrão
    char prefix[100];
    while (fgets(prefix, sizeof(prefix), stdin)) {
        prefix[strcspn(prefix, "\n")] = '\0';  // Remove newline
        printf("%s \n", prefix);
        printf("\n");
        searchPrefix(root, prefix);  // Realiza a busca pelo prefixo
    }


    return 0;
}
