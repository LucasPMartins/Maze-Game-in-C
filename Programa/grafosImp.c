#include "grafos.h"
#include "ranking.h"
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
    printf("Opcao invalida. Tente novamente.\n");
    return NULL;
  }

  TipoApontador aux = grafo->adj[verticeAtual].primeiro->prox;
  int contador = 1;

  while (aux != NULL && contador < escolha) {
    aux = aux->prox;
    contador++;
  }

  if (aux == NULL || contador != escolha) {
    printf("Opcao invalida. Tente novamente.\n");
    return NULL;
  }

  return aux;
}

void exibirOpcoes(TipoGrafo *grafo, TipoValorVertice verticeAtual) {
  int contador = 1;
  printf("\nOpcoes de movimento a partir da sala %d:\n", verticeAtual);

  TipoApontador adjacente = grafo->adj[verticeAtual].primeiro->prox;
  if (!adjacente) {
    printf("Sem saidas disponiveis.\n");
    return;
  }

  while (adjacente) {
    printf("%d. Sala %d", contador, adjacente->item.vertice);
    if (adjacente->item.ehSaida)
      printf(" - Saida");
    if (adjacente->item.ehSumidouro)
      printf(" - Sumidouro");
    printf("\n");
    adjacente = adjacente->prox;
    contador++;
  }
  printf("Escolha uma opcao ou digite -1 para sair.\n");
}

void percorrerGrafo(TipoGrafo *grafo, TipoValorVertice verticeInicial) {
  TipoValorVertice verticeAtual = verticeInicial;
  printf("\n\nExplorando o labirinto...\n");

  while (1) {
    exibirOpcoes(grafo, verticeAtual);
    printf("Sua escolha: ");
    int escolha;
    if (scanf("%d", &escolha) != 1) {
      printf("Entrada invalida.\n");
      while (getchar() != '\n')
        ; // Limpa o buffer
      continue;
    }

    if (escolha == -1) {
      printf("Exploracao encerrada.\n");
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
      printf("Saida encontrada! Fim da exploracao.\n");
      break;
    }
  }
}

void percorrerAreaCentral(TipoGrafo *grafo, int verticeInicial,
                          Jogador *jogador) {
  int verticeAtual = verticeInicial;
  int verticeAnterior = -1; // Inicializa sem um vértice anterior válido
  int escolha;
  TipoApontador adj;

  printf("\n\nIniciando a exploração da área central...\n");

  while (1) {
    printf("Você está no vértice %d com %d pontos.\n", verticeAtual,
           jogador->pontos);
    exibirOpcoes(grafo, verticeAtual); // Lista as conexões e seus pesos

    scanf("%d", &escolha);
    while (getchar() != '\n')
      ; // Limpa o buffer de entrada

    if (escolha == -1) {
      printf("Exploração da área central encerrada.\n");
      break;
    }

    adj = encontrarVertice(grafo, verticeAtual, escolha);
    if (adj == NULL) {
      printf("Opção inválida. Tente novamente.\n");
      continue;
    }

    // Acumula pontos baseado no peso da aresta
    jogador->pontos += adj->item.peso;
    printf("Movendo para o vértice %d. Pontos acumulados: %d\n",
           adj->item.vertice, jogador->pontos);

    if (adj->item.ehSumidouro) {
      printf("Você chegou a um sumidouro! ");
      if (jogador->pontos > 0) {
        printf("Usando 1 ponto para retroceder.\n");
        jogador->pontos -= 1; // Usa um ponto para "retroceder" a ação
        verticeAtual = verticeAnterior != -1
                           ? verticeAnterior
                           : verticeInicial; // Volta ao vértice anterior ou
                                             // inicial se não houver anterior
        continue; // Continua a exploração a partir do vértice anterior
      } else {
        printf(
            "Não possui pontos suficientes para retroceder. Jogo encerrado.\n");
        break; // Termina o jogo se não há pontos para retroceder
      }
    } else if (adj->item.ehSaida) {
      printf("Você encontrou uma saída com %d pontos! Exploração concluída.\n",
             jogador->pontos);
      break; // Encontrou uma saída, termina a exploração
    }

    verticeAnterior = verticeAtual;   // Atualiza o vértice anterior
    verticeAtual = adj->item.vertice; // Atualiza o vértice atual para o próximo
  }
}
