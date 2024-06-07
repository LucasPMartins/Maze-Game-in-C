#ifndef ARVORE_H
#define ARVORE_H

#include "grafo.h"

typedef struct NoArvore
{
    Grafo area;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

typedef struct ArvoreBinarias
{
    NoArvore *raiz;
} ArvoreBinaria;

// Protótipos das funções

ArvoreBinaria *criarArvore();
NoArvore *criarNo(Grafo area);
void inserir(ArvoreBinaria *arvore, Grafo area, int ehAreaCentral);
void liberarArvore(NoArvore *no);

#endif // ARVORE_H