#include "arvore.h"
#include "grafo.h"

typedef struct Pilha
{
    NoArvore **nos;
    int topo;
    int capacidade;
} Pilha;