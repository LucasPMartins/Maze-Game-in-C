#include "arvore.h"
#include "grafo.h"
#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

// Função para criar uma pilha
Pilha *criarPilha(int capacidade)
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if (pilha)
    {
        pilha->capacidade = capacidade;
        pilha->topo = -1;
        pilha->nos = (NoArvore **)malloc(capacidade * sizeof(NoArvore *));
    }
    return pilha;
}

// Função para verificar se a pilha está cheia
int estaCheia(Pilha *pilha)
{
    return pilha->topo == pilha->capacidade - 1;
}

// Função para verificar se a pilha está vazia
int estaVazia(Pilha *pilha)
{
    return pilha->topo == -1;
}

// Função para empilhar um nó
void empilhar(Pilha *pilha, NoArvore *no)
{
    if (estaCheia(pilha))
    {
        printf("Pilha cheia\n");
        return;
    }
    pilha->nos[++pilha->topo] = no;
}

// Função para desempilhar um nó
NoArvore *desempilhar(Pilha *pilha)
{
    if (estaVazia(pilha))
    {
        printf("Pilha vazia\n");
        return NULL;
    }
    return pilha->nos[pilha->topo--];
}

// Função auxiliar para percorrer a árvore até o último nó e preencher a pilha
void preencherPilha(NoArvore *no, Pilha *pilha)
{
    if (no == NULL)
    {
        return;
    }
    empilhar(pilha, no);
    if (no->esquerda == NULL && no->direita == NULL)
    {
        return;
    }
    if (no->direita != NULL)
    {
        preencherPilha(no->direita, pilha);
    }
    if (no->esquerda != NULL)
    {
        preencherPilha(no->esquerda, pilha);
    }
}

// Função para inicializar a pilha com o caminho do último nó até a raiz
Pilha *inicializarPercurso(ArvoreBinaria *arvore)
{
    Pilha *pilha = criarPilha(100); // Defina a capacidade conforme necessário
    preencherPilha(arvore->raiz, pilha);
    return pilha;
}

// Função para percorrer a árvore do último nó até a raiz
Grafo *proximoNo(Pilha *pilha)
{
    if (estaVazia(pilha))
    {
        return NULL;
    }
    NoArvore *no = desempilhar(pilha);
    return &no->area;
}

// Função para liberar a memória da pilha
void liberarPilha(Pilha *pilha)
{
    if (pilha != NULL)
    {
        free(pilha->nos); // Libera o array de ponteiros
        free(pilha);      // Libera a estrutura da pilha
    }
}