#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaRanking(Ranking *ranking) { ranking->numJogadores = 0; }

void insertionSort(Ranking *ranking, int tipo) {
  int i, j;
  Jogador key;
  if (tipo == 1) {
    for (i = 1; i < ranking->numJogadores; i++) {
      key = ranking->jogadores[i];
      j = i - 1;

      while (j >= 0 && ranking->jogadores[j].tempoAreaCentral < key.tempoAreaCentral) {
        ranking->jogadores[j + 1] = ranking->jogadores[j];
        j = j - 1;
      }
      ranking->jogadores[j + 1] = key;
    }
  } else if (tipo == 2) {
    for (i = 1; i < ranking->numJogadores; i++) {
      key = ranking->jogadores[i];
      j = i - 1;

      while (j >= 0 && ranking->jogadores[j].pontos < key.pontos) {
        ranking->jogadores[j + 1] = ranking->jogadores[j];
        j = j - 1;
      }
      ranking->jogadores[j + 1] = key;
    }
  } else {
    printf("Erro na ordenacao!");
  }
}

void adicionaJogador(Ranking *ranking, char *nome, double tempoTotal,
                     int pontos,double tempoAreaCentral) {
  if (ranking->numJogadores < MAX_JOGADORES) {
    strncpy(ranking->jogadores[ranking->numJogadores].nome, nome,
            sizeof(ranking->jogadores[0].nome) - 1);
    ranking->jogadores[ranking->numJogadores]
        .nome[sizeof(ranking->jogadores[0].nome) - 1] = '\0';
    ranking->jogadores[ranking->numJogadores].tempoTotal = tempoTotal;
    ranking->jogadores[ranking->numJogadores].tempoAreaCentral = tempoAreaCentral;
    ranking->jogadores[ranking->numJogadores].pontos = pontos;
    ranking->numJogadores++;
    insertionSort(ranking, 1);
  } else {
    // Se o novo jogador tem mais pontos que o último do ranking ordenado,
    // substitui o último
    if (pontos > ranking->jogadores[MAX_JOGADORES - 1].pontos) {
      strncpy(ranking->jogadores[MAX_JOGADORES - 1].nome, nome,
              sizeof(ranking->jogadores[0].nome) - 1);
      ranking->jogadores[MAX_JOGADORES - 1]
          .nome[sizeof(ranking->jogadores[0].nome) - 1] = '\0';
      ranking->jogadores[MAX_JOGADORES - 1].tempoTotal = tempoTotal;
      ranking->jogadores[ranking->numJogadores].tempoAreaCentral = tempoAreaCentral;
      ranking->jogadores[MAX_JOGADORES - 1].pontos = pontos;
      insertionSort(ranking, 1);
    }
  }
}

void exibeRanking(const Ranking *ranking, int tipo) {
  if (tipo == 1) {
    for (int i = 0; i < ranking->numJogadores; i++) {
      printf("               %d. %s - Tempo na Area Central: %.2f - Tempo Total: %.2f\n", i + 1,
             ranking->jogadores[i].nome, ranking->jogadores[i].tempoAreaCentral, ranking->jogadores[i].tempoTotal);
    }
  } else if (tipo == 2) {
    for (int i = 0; i < ranking->numJogadores; i++) {
      printf("               %d. %s - Pontuacao: %d - Tempo Total: %.2f\n", i + 1,
             ranking->jogadores[i].nome, ranking->jogadores[i].pontos, ranking->jogadores[i].tempoTotal);
    }
  }
}

void salvarRanking(const Ranking *ranking) {
  FILE *arquivo = fopen("ranking.txt", "w");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de ranking para escrita.\n");
    return;
  }

  for (int i = 0; i < ranking->numJogadores; i++) {
    fprintf(arquivo, "%s,%d,%.2f,%.2f\n", ranking->jogadores[i].nome,
            ranking->jogadores[i].pontos, ranking->jogadores[i].tempoTotal,ranking->jogadores[i].tempoAreaCentral);
  }

  fclose(arquivo);
  printf("\n\nRanking salvo com sucesso.\n");
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
    if (fscanf(arquivo, "%24[^,],%d,%lf,%lf\n", jogador.nome, &jogador.pontos,
               &jogador.tempoTotal,&jogador.tempoAreaCentral) == 4) {
      if (ranking->numJogadores < MAX_JOGADORES) {
        ranking->jogadores[ranking->numJogadores++] = jogador;
      }
    }
  }

  fclose(arquivo);
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