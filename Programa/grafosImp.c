#include "grafos.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXNUMVERTICES 100
#define MAXNUMARESTAS 4500

typedef int TipoValorVertice;
typedef int TipoPeso;

void FGVazio(TipoGrafo *grafo) {
  int i;
  for (i = 0; i < grafo->numVertices; i++) {
    grafo->adj[i].primeiro = (TipoApontador)malloc(sizeof(struct TipoCelula));
    grafo->adj[i].ultimo = grafo->adj[i].primeiro;
    grafo->adj[i].primeiro->prox = NULL;
  }
}

void InsereAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoPeso *peso,
                  TipoGrafo *grafo) {
  TipoApontador novoNo;
  novoNo = (TipoApontador)malloc(sizeof(struct TipoCelula));
  novoNo->item.vertice = *v2;
  novoNo->item.peso = *peso;
  novoNo->prox = NULL;
  grafo->adj[*v1].ultimo->prox = novoNo;
  grafo->adj[*v1].ultimo = novoNo;
  grafo->numArestas++;
}

int ExisteAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoGrafo *grafo) {
  TipoApontador aux;
  aux = grafo->adj[*v1].primeiro->prox;
  while (aux != NULL && aux->item.vertice != *v2) {
    aux = aux->prox;
  }
  if (aux == NULL) {
    return 0;
  } else {
    return 1;
  }
}

void RetiraAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoPeso *peso,
                  TipoGrafo *grafo) {
  TipoApontador aux, ant;
  ant = grafo->adj[*v1].primeiro;
  aux = grafo->adj[*v1].primeiro->prox;
  while (aux != NULL && aux->item.vertice != *v2) {
    ant = aux;
    aux = aux->prox;
  }
  if (aux != NULL) {
    ant->prox = aux->prox;
    free(aux);
  }
}

void ImprimeGrafo(TipoGrafo *grafo) {
  int i;
  TipoApontador aux;
  for (i = 0; i < grafo->numVertices; i++) {
    printf("Vertice %d: ", i);
    aux = grafo->adj[i].primeiro->prox;
    while (aux != NULL) {
      printf("%d (%d) ", aux->item.vertice, aux->item.peso);
      aux = aux->prox;
    }
    printf("\n");
  }
}
void LiberaGrafo(TipoGrafo *grafo) {
  int i;
  TipoApontador aux, ant;
  for (i = 0; i < grafo->numVertices; i++) {
    aux = grafo->adj[i].primeiro->prox;
    grafo->adj[i].primeiro->prox = NULL;
    while (aux != NULL) {
      ant = aux;
      aux = aux->prox;
      free(ant);
    }
  }
  grafo->numVertices = 0;
}
