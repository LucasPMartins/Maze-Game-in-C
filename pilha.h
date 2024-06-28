#include "arvore.h"
#include "grafo.h"

// Estrutura da pilha
typedef struct Pilha
{
    NoArvore **nos; // Array de ponteiros para NoArvore
    int topo;
    int capacidade;
} Pilha;

Pilha *criarPilha(int capacidade);
int estaCheia(Pilha *pilha);
int estaVazia(Pilha *pilha);
void empilhar(Pilha *pilha, NoArvore *no);
NoArvore *desempilhar(Pilha *pilha);
void preencherPilha(NoArvore *no, Pilha *pilha);
Pilha *inicializarPercurso(ArvoreBinaria *arvore);
Grafo *proximoNo(Pilha *pilha);
void liberarPilha(Pilha *pilha);