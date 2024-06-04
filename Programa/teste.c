#include <stdio.h>
#include <stdlib.h>

// Definição das estruturas

typedef struct Grafo
{
    int chave; // Chave da área do labirinto
    // Outros campos da área do labirinto
} Grafo;

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

// Função principal (main)

int main()
{
    ArvoreBinaria *arvore = criarArvore();

    // Inserir áreas na árvore
    Grafo area1 = {10}; // Exemplo de área com chave 10
    Grafo area2 = {5};  // Exemplo de área com chave 5
    Grafo area3 = {15}; // Exemplo de área com chave 15

    inserirArea(arvore, area1);
    inserirArea(arvore, area2);
    inserirArea(arvore, area3);

    // Imprimir a árvore (opcional)
    printf("Arvore binaria de areas do labirinto:\n");
    imprimirArvore(arvore->raiz);
    printf("\n");

    // Liberação de memória (caso necessário)
    // liberarArvore(arvore);

    return 0;
}
