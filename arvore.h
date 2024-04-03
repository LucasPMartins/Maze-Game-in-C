#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

typedef struct NoArvore {
    int dado;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

typedef struct {
    NoArvore *raiz;
} ArvoreBinaria;

ArvoreBinaria criarArvore();
void inserir(ArvoreBinaria *arvore, int dado);
void percorrerEmOrdem(ArvoreBinaria *arvore);
void liberarArvore(ArvoreBinaria *arvore);

#endif // ARVORE_H_INCLUDED
