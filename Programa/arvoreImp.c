#include "arvore.h"

// Implementação das funções

ArvoreBinaria *criarArvore()
{
    ArvoreBinaria *arvore = (ArvoreBinaria *)malloc(sizeof(ArvoreBinaria));
    if (arvore)
    {
        arvore->raiz = NULL;
    }
    return arvore;
}

NoArvore *inserirNo(NoArvore *no, Grafo area)
{
    if (no == NULL)
    {
        NoArvore *novoNo = (NoArvore *)malloc(sizeof(NoArvore));
        if (novoNo)
        {
            novoNo->area = area;
            novoNo->esquerda = NULL;
            novoNo->direita = NULL;
            return novoNo;
        }
    }
    else
    {
        if (area.chave < no->area.chave)
        {
            no->esquerda = inserirNo(no->esquerda, area);
        }
        else if (area.chave > no->area.chave)
        {
            no->direita = inserirNo(no->direita, area);
        }
    }
    return no;
}

void inserirArea(ArvoreBinaria *arvore, Grafo area)
{
    arvore->raiz = inserirNo(arvore->raiz, area);
}

// Função auxiliar para imprimir a árvore (opcional)
void imprimirArvore(NoArvore *no)
{
    if (no != NULL)
    {
        imprimirArvore(no->esquerda);
        printf("%d ", no->area.chave);
        imprimirArvore(no->direita);
    }
}