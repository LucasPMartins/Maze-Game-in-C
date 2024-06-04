#include "grafo.h"

typedef struct NoArvore
{
    Grafo area;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

typedef struct ArvoreBinaria
{
    NoArvore *raiz;
} ArvoreBinaria;

// Protótipos das funções

ArvoreBinaria *criarArvore();
NoArvore *inserirNo(NoArvore *no, Grafo area);
void inserirArea(ArvoreBinaria *arvore, Grafo area);
void imprimirArvore(NoArvore *no); // Função auxiliar para imprimir a árvore (opcional)