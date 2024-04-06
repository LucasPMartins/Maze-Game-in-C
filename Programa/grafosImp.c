#include "grafos.h"
#include <stdio.h>
#include <stdlib.h>

void FGVazio(TipoGrafo *grafo) {
  int i;
  for (i = 0; i < MAXNUMVERTICES; i++) {
    grafo->adj[i].primeiro = (TipoApontador)malloc(sizeof(struct TipoCelula));
    grafo->adj[i].ultimo = grafo->adj[i].primeiro;
    grafo->adj[i].primeiro->prox = NULL;
  }
  grafo->numVertices = 0;
  grafo->numArestas = 0;
}

void InsereAresta(TipoValorVertice v1, TipoValorVertice v2, TipoPeso peso,
                  TipoGrafo *grafo, int ehSaida, int ehSumidouro) {
  TipoApontador novoNo = (TipoApontador)malloc(sizeof(struct TipoCelula));
  novoNo->item.vertice = v2;
  novoNo->item.peso = peso;
  novoNo->item.ehSaida = ehSaida;
  novoNo->item.ehSumidouro = ehSumidouro;
  novoNo->prox = NULL;
  grafo->adj[v1].ultimo->prox = novoNo;
  grafo->adj[v1].ultimo = novoNo;
  grafo->numArestas++;
}

int ExisteAresta(TipoValorVertice v1, TipoValorVertice v2, TipoGrafo *grafo) {
  TipoApontador aux = grafo->adj[v1].primeiro->prox;
  while (aux != NULL) {
    if (aux->item.vertice == v2) {
      return 1;
    }
    aux = aux->prox;
  }
  return 0;
}

void RetiraAresta(TipoValorVertice v1, TipoValorVertice v2, TipoGrafo *grafo) {
  TipoApontador aux, ant;
  ant = grafo->adj[v1].primeiro;
  aux = grafo->adj[v1].primeiro->prox;
  while (aux != NULL && aux->item.vertice != v2) {
    ant = aux;
    aux = aux->prox;
  }
  if (aux != NULL) {
    ant->prox = aux->prox;
    if (grafo->adj[v1].ultimo == aux) {
      grafo->adj[v1].ultimo = ant;
    }
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

TipoApontador encontrarVertice(TipoGrafo *grafo, TipoValorVertice verticeAtual,
                               int escolha) {
  if (escolha < 1) {
    printf("Opção inválida. Tente novamente.\n");
    return NULL;
  }

  TipoApontador aux = grafo->adj[verticeAtual].primeiro->prox;
  int contador = 1;

  while (aux != NULL && contador < escolha) {
    aux = aux->prox;
    contador++;
  }

  if (aux == NULL || contador != escolha) {
    printf("Opção inválida. Tente novamente.\n");
    return NULL;
  }

  return aux;
}

void exibirOpcoes(TipoGrafo *grafo, TipoValorVertice verticeAtual) {
  int contador = 1;
  printf("\nOpções de movimento a partir da sala %d:\n", verticeAtual);

  TipoApontador adjacente = grafo->adj[verticeAtual].primeiro->prox;
  if (!adjacente) {
    printf("Sem saídas disponíveis.\n");
    return;
  }

  while (adjacente) {
    printf("%d. Sala %d", contador, adjacente->item.vertice);
    if (adjacente->item.ehSaida)
      printf(" - Saída");
    if (adjacente->item.ehSumidouro)
      printf(" - Sumidouro");
    printf("\n");
    adjacente = adjacente->prox;
    contador++;
  }
  printf("Escolha uma opção ou digite -1 para sair.\n");
}

void percorrerGrafo(TipoGrafo *grafo, TipoValorVertice verticeInicial) {
  TipoValorVertice verticeAtual = verticeInicial;
  printf("Explorando o labirinto...\n");

  while (1) {
    exibirOpcoes(grafo, verticeAtual);
    printf("Sua escolha: ");
    int escolha;
    if (scanf("%d", &escolha) != 1) {
      printf("Entrada inválida.\n");
      while (getchar() != '\n')
        ; // Limpa o buffer
      continue;
    }

    if (escolha == -1) {
      printf("Exploração encerrada.\n");
      break;
    }

    TipoApontador proximo = encontrarVertice(grafo, verticeAtual, escolha);
    if (!proximo)
      continue;

    verticeAtual = proximo->item.vertice;
    if (proximo->item.ehSumidouro) {
      printf("Caiu em um sumidouro! Fim do jogo.\n");
      break;
    }
    if (proximo->item.ehSaida) {
      printf("Saída encontrada! Fim da exploração.\n");
      break;
    }
  }
}
