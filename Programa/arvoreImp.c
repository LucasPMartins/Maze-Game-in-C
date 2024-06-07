#include "arvore.h"
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

// Implementação das funções

// Função para criar uma árvore binária
ArvoreBinaria *criarArvore()
{
    ArvoreBinaria *arvore = (ArvoreBinaria *)malloc(sizeof(ArvoreBinaria));
    if (arvore)
    {
        arvore->raiz = NULL;
    }
    return arvore;
}

// Função para criar um nó da árvore binária
NoArvore *criarNo(Grafo area)
{
    NoArvore *novoNo = (NoArvore *)malloc(sizeof(NoArvore));
    if (novoNo == NULL)
    {
        printf("Erro ao alocar memoria para novo no.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->area = area;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um nó na árvore binária
void inserir(ArvoreBinaria *arvore, Grafo area, int ehAreaCentral)
{
    NoArvore *novoNo = criarNo(area);

    // Trata a inserção da area central diretamente
    if (ehAreaCentral)
    {
        if (arvore->raiz != NULL)
        {
            printf("Erro: A área central já existe.\n");
            free(novoNo);
            return;
        }
        arvore->raiz = novoNo;
    }
    else
    {
        // Inserção padrão para nós que não são a area central
        if (arvore->raiz == NULL)
        {
            arvore->raiz = novoNo; // Se arvore estar vazia, insere na raiz
        }
        else
        {
            // Busca a posição de inserção baseada no número de vértices
            NoArvore *atual = arvore->raiz;
            NoArvore *anterior = NULL;
            int ehEsquerda = 0;

            // Encontra a posição de inserção
            while (atual != NULL)
            {
                anterior = atual;
                if (area.V < atual->area.V)
                {
                    atual = atual->esquerda;
                    ehEsquerda = 1; // Indica que a insercão sera nó esquerda
                }
                else
                {
                    atual = atual->direita;
                    ehEsquerda = 0; // Indica que a inserção sera nó direita
                }
            }

            // Insere o novo nó na posicão encontrada
            if (ehEsquerda)
            {
                anterior->esquerda = novoNo;
            }
            else
            {
                anterior->direita = novoNo;
            }
        }
    }
}

// Função para liberar a memória de uma árvore binária

void liberarArvore(NoArvore *no)
{
    if (no == NULL)
        return;
    liberarArvore(no->esquerda);
    liberarArvore(no->direita);
    free(no);
}