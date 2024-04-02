#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaRanking(Ranking *ranking) { ranking->numJogadores = 0; }

void insertionSort(Ranking *ranking) {
  int i, j;
  Jogador key;
  for (i = 1; i < ranking->numJogadores; i++) {
    key = ranking->jogadores[i];
    j = i - 1;

    while (j >= 0 && ranking->jogadores[j].pontos < key.pontos) {
      ranking->jogadores[j + 1] = ranking->jogadores[j];
      j = j - 1;
    }
    ranking->jogadores[j + 1] = key;
  }
}

void adicionaJogador(Ranking *ranking, char *nome, double tempoTotal,
                     int pontos) {
  if (ranking->numJogadores < MAX_JOGADORES) {
    strncpy(ranking->jogadores[ranking->numJogadores].nome, nome,
            sizeof(ranking->jogadores[0].nome) - 1);
    ranking->jogadores[ranking->numJogadores]
        .nome[sizeof(ranking->jogadores[0].nome) - 1] = '\0';
    ranking->jogadores[ranking->numJogadores].tempoTotal = tempoTotal;
    ranking->jogadores[ranking->numJogadores].pontos = pontos;
    ranking->numJogadores++;
    insertionSort(ranking);
  } else {
    // Se o novo jogador tem mais pontos que o último do ranking ordenado,
    // substitui o último
    if (pontos > ranking->jogadores[MAX_JOGADORES - 1].pontos) {
      strncpy(ranking->jogadores[MAX_JOGADORES - 1].nome, nome,
              sizeof(ranking->jogadores[0].nome) - 1);
      ranking->jogadores[MAX_JOGADORES - 1]
          .nome[sizeof(ranking->jogadores[0].nome) - 1] = '\0';
      ranking->jogadores[MAX_JOGADORES - 1].tempoTotal = tempoTotal;
      ranking->jogadores[MAX_JOGADORES - 1].pontos = pontos;
      insertionSort(ranking);
    }
  }
}

void exibeRanking(const Ranking *ranking) {
  printf("Ranking:\n");
  for (int i = 0; i < ranking->numJogadores; i++) {
    printf("%d. %s - Pontos: %d, Tempo Total: %.2f\n", i + 1,
           ranking->jogadores[i].nome, ranking->jogadores[i].pontos,
           ranking->jogadores[i].tempoTotal);
  }
}

void salvarRanking(const Ranking *ranking) {
  FILE *arquivo = fopen("ranking.txt", "w");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de ranking para escrita.\n");
    return;
  }

  for (int i = 0; i < ranking->numJogadores; i++) {
    fprintf(arquivo, "%s,%d,%.2f\n", ranking->jogadores[i].nome,
            ranking->jogadores[i].pontos, ranking->jogadores[i].tempoTotal);
  }

  fclose(arquivo);
  printf("Ranking salvo com sucesso.\n");
}

void carregarRanking(Ranking *ranking) {
  FILE *arquivo = fopen("ranking.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de ranking para leitura.\n");
    return;
  }

  inicializaRanking(ranking); // Reinicia o ranking antes de carregar os dados

  while (!feof(arquivo)) {
    Jogador jogador;
    if (fscanf(arquivo, "%24[^,],%d,%lf\n", jogador.nome, &jogador.pontos,
               &jogador.tempoTotal) == 3) {
      if (ranking->numJogadores < MAX_JOGADORES) {
        ranking->jogadores[ranking->numJogadores++] = jogador;
      }
    }
  }

  fclose(arquivo);
  printf("Ranking carregado com sucesso.\n");
}

void limparRanking(Ranking *ranking) {
  ranking->numJogadores = 0;
  printf("O histórico do ranking foi limpo.\n");
}

void removerJogador(Ranking *ranking, char *nome) {
  int i, j;
  for (i = 0; i < ranking->numJogadores; i++) {
    if (strcmp(ranking->jogadores[i].nome, nome) == 0) {
      // Jogador encontrado, desloca todos os seguintes uma posição para trás
      for (j = i; j < ranking->numJogadores - 1; j++) {
        ranking->jogadores[j] = ranking->jogadores[j + 1];
      }
      ranking->numJogadores--; // Decrementa o número total de jogadores
      printf("Jogador '%s' removido do ranking.\n", nome);
      return;
    }
  }
  printf("Jogador '%s' não encontrado no ranking.\n", nome);
}
