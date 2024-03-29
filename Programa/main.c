#include "grafos.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct jogador {
  char nome[25];
  double *tempoArea;
  double tempoTotal;
  int pontos;
} Jogador;

int main() {
  TipoGrafo grafo;
  int numVertices, numArestas, i, j, v1, v2, peso;
  TipoValorVertice *v1_ptr, *v2_ptr;
  TipoPeso *peso_ptr;

  FILE *arquivo = fopen("ranking.txt", "rw");

  if (arquivo == NULL) {

    printf("Erro ao abrir o arquivo.\n");

    return 1;
  }
  printf("Digite o número de vértices do grafo: ");
  scanf("%d", &numVertices);
  printf("Digite o número de arestas do grafo: ");
  scanf("%d", &numArestas);

  grafo.numVertices = numVertices; // Set the number of vertices

  FGVazio(&grafo);

  for (i = 0; i < numArestas; i++) {
    printf("Digite as extremidades da aresta %d: ", i + 1);
    scanf("%d %d", &v1, &v2);
    printf("Digite o peso da aresta %d: ", i + 1);
    scanf("%d", &peso);
    v1_ptr = &v1;
    v2_ptr = &v2;
    peso_ptr = &peso;
    InsereAresta(v1_ptr, v2_ptr, peso_ptr, &grafo);
  }

  printf("Grafo:\n");
  ImprimeGrafo(&grafo);

  fclose(arquivo);
  return 0;
}