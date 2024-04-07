#include "arvore.h"
#include "grafos.h"
#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>

NoArvore *criarNo(TipoGrafo dado) {
  NoArvore *novoNo = (NoArvore *)malloc(sizeof(NoArvore));
  if (novoNo == NULL) {
    printf("Erro ao alocar memoria para novo no.\n");
    exit(EXIT_FAILURE);
  }
  novoNo->dado = dado;
  novoNo->esquerda = NULL;
  novoNo->direita = NULL;
  return novoNo;
}

void inserir(ArvoreBinaria *arvore, TipoGrafo dado, int ehAreaCentral) {
  NoArvore *novoNo = criarNo(dado);

  // Trata a inserÁ„o da ·rea central diretamente
  if (ehAreaCentral) {
    // Verifica se a ·rea central j· foi definida
    if (arvore->areaCentral == NULL) {
      arvore->areaCentral = novoNo; // Atribui a ·rea central diretamente se
                                    // ainda n„o foi definida
    } else {
      printf("A area central ja foi definida anteriormente.\n");
    }
  } else {
    // InserÁ„o padr„o para nÛs que n„o s„o a ·rea central
    if (arvore->raiz == NULL) {
      arvore->raiz = novoNo; // Se a ·rvore est· vazia, insere na raiz
    } else {
      // Busca a posiÁ„o de inserÁ„o baseada no n˙mero de vÈrtices
      NoArvore *atual = arvore->raiz;
      NoArvore *anterior = NULL;
      int ehEsquerda = 0;

      // Encontra a posiÁ„o de inserÁ„o
      while (atual != NULL) {
        anterior = atual;
        if (dado.numVertices < atual->dado.numVertices) {
          atual = atual->esquerda;
          ehEsquerda = 1; // Indica que a inserÁ„o ser· ‡ esquerda
        } else {
          atual = atual->direita;
          ehEsquerda = 0; // Indica que a inserÁ„o ser· ‡ direita
        }
      }

      // Insere o novo nÛ na posiÁ„o encontrada
      if (ehEsquerda) {
        anterior->esquerda = novoNo;
      } else {
        anterior->direita = novoNo;
      }
    }
  }
}

void percorrerEmOrdemAux(NoArvore *no) {
  if (no != NULL) {
    percorrerEmOrdemAux(no->esquerda);
    printf("%d ", no->dado.numVertices);
    percorrerEmOrdemAux(no->direita);
  }
}

void percorrerEmOrdem(ArvoreBinaria *arvore) {
  printf("Arvore em ordem: ");
  percorrerEmOrdemAux(arvore->raiz);
  printf("\n");
}

void liberarArvoreAux(NoArvore *raiz) {
  if (raiz == NULL) {
    return;
  }
  liberarArvoreAux(raiz->esquerda);
  liberarArvoreAux(raiz->direita);
  free(raiz);
}

void liberarArvore(ArvoreBinaria *arvore) {
  liberarArvoreAux(arvore->raiz);
  arvore->raiz = NULL;
}

ArvoreBinaria criarArvore() {
  ArvoreBinaria novaArvore;
  novaArvore.raiz = NULL;
  novaArvore.areaCentral = NULL;
  return novaArvore;
}

void percorrerPosOrdemAux(NoArvore *no) {
  if (no != NULL) {
    int count = 0;
    // Visita primeiro os nÛs filhos
    percorrerPosOrdemAux(no->esquerda);
    percorrerPosOrdemAux(no->direita);

    // Processa o nÛ atual
    // printf("Labirinto\n", no->dado.numVertices);
    // Aqui vocÍ pode adicionar mais lÛgicas, como chamar ImprimeGrafo() para
    // mostrar detalhes do grafo
  }
}

void percorrerPosOrdem(ArvoreBinaria *arvore) {
  printf("Arvore em pos-ordem (o ultimo È a raiz):\n");
  percorrerPosOrdemAux(arvore->raiz);
}

void jogarFase(TipoGrafo *grafo, Jogador *jogador) {
  printf("\n\nJogando fase %d...\n", jogador->fasesCompletas + 1);
  percorrerGrafo(
      grafo, 0); // Supondo que 0 seja o vÈrtice inicial padr„o para cada fase
  jogador->fasesCompletas++;
}

void percorrerPosOrdemEJogar(NoArvore *no, Jogador *jogador) {
  if (no != NULL) {
    // Primeiro percorre a sub·rvore esquerda
    percorrerPosOrdemEJogar(no->esquerda, jogador);
    // Em seguida, percorre a sub·rvore direita
    percorrerPosOrdemEJogar(no->direita, jogador);
    // Finalmente, visita o nÛ atual (que n„o È a ·rea central)
    jogarFase(&no->dado, jogador); // Joga a fase associada ao nÛ atual;
  }
}

void iniciarJogoComPosOrdem(ArvoreBinaria *arvore, Jogador *jogador) {

  percorrerPosOrdemEJogar(arvore->raiz, jogador);

  if (arvore->areaCentral != NULL) {
    printf("\n\nEntrando na Area central...\n");
    percorrerAreaCentral(&arvore->areaCentral->dado, 0, jogador);
  }
}
