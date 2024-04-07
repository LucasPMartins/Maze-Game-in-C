#ifndef GRAFOS_H_INCLUDED
#define GRAFOS_H_INCLUDED

#include "ranking.h"
#define MAXNUMVERTICES 100
#define MAXNUMARESTAS 4500

typedef int TipoValorVertice;
typedef int TipoPeso;

typedef struct TipoItem {
  TipoValorVertice vertice;
  TipoPeso peso;
  int ehSaida;     // 1 para saída e 0 para padrão
  int ehSumidouro; // 1 para sumidouro e 0 para padrão
} TipoItem;

struct TipoCelula {
  TipoItem item;
  struct TipoCelula *prox;
};

typedef struct TipoCelula *TipoApontador;

typedef struct TipoLista {
  TipoApontador primeiro, ultimo;
} TipoLista;

typedef struct TipoGrafo {
  TipoLista adj[MAXNUMVERTICES];
  int numVertices;
  int numArestas;
  int ehAreaCentral;
} TipoGrafo;

void FGVazio(TipoGrafo *grafo);
void InsereAresta(TipoValorVertice v1, TipoValorVertice v2, TipoPeso peso,
                  TipoGrafo *grafo, int ehSaida, int ehSumidouro);
int ExisteAresta(TipoValorVertice v1, TipoValorVertice v2, TipoGrafo *grafo);
void RetiraAresta(TipoValorVertice v1, TipoValorVertice v2, TipoGrafo *grafo);
void ImprimeGrafo(TipoGrafo *grafo);
void LiberaGrafo(TipoGrafo *grafo);
void exibirOpcoes(TipoGrafo *grafo, TipoValorVertice verticeAtual);
TipoApontador encontrarVertice(TipoGrafo *grafo, TipoValorVertice verticeAtual,
                               int escolha);
void percorrerGrafo(TipoGrafo *grafo, TipoValorVertice verticeInicial);
void percorrerAreaCentral(TipoGrafo *grafo, int verticeInicial,
                          Jogador *jogador);
#endif // GRAFOS_H_INCLUDED
