#include "arvore_binaria.h"
#include <stdio.h>
#include <stdlib.h>

NoArvore* criarNo(int dado) {
    NoArvore *novoNo = (NoArvore*)malloc(sizeof(NoArvore));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = dado;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

void inserir(ArvoreBinaria *arvore, int dado) {
    if (arvore->raiz == NULL) {
        arvore->raiz = criarNo(dado);
    } else {
        NoArvore *atual = arvore->raiz;
        while (1) {
            if (dado <= atual->dado) {
                if (atual->esquerda == NULL) {
                    atual->esquerda = criarNo(dado);
                    break;
                } else {
                    atual = atual->esquerda;
                }
            } else {
                if (atual->direita == NULL) {
                    atual->direita = criarNo(dado);
                    break;
                } else {
                    atual = atual->direita;
                }
            }
        }
    }
}

void percorrerEmOrdemAux(NoArvore *no) {
    if (no != NULL) {
        percorrerEmOrdemAux(no->esquerda);
        printf("%d ", no->dado);
        percorrerEmOrdemAux(no->direita);
    }
}

void percorrerEmOrdem(ArvoreBinaria *arvore) {
    printf("Árvore em ordem: ");
    percorrerEmOrdemAux(arvore->raiz);
    printf("\n");
}

void liberarArvoreAux(NoArvore *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarArvoreAux(raiz->esquerda);
    liberarArvoreAux(raiz->direita);
    free(raiz);
}

void liberarArvore(ArvoreBinaria *arvore) {
    liberarArvoreAux(arvore->raiz);
    arvore->raiz = NULL;
}

ArvoreBinaria criarArvore() {
    ArvoreBinaria novaArvore;
    novaArvore.raiz = NULL;
    return novaArvore;
}
