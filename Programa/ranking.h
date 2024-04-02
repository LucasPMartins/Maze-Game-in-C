#include <stdio.h>
#include <string.h>

#define MAX_JOGADORES 10

typedef struct {
  char nome[25];
  double tempoTotal;
  int pontos;
} Jogador;

typedef struct {
  Jogador jogadores[MAX_JOGADORES];
  int numJogadores;
} Ranking;

void inicializaRanking(Ranking *ranking);

void insertionSort(Ranking *ranking);

void adicionaJogador(Ranking *ranking, char *nome, double tempoTotal,
                     int pontos);

void exibeRanking(const Ranking *ranking);

void salvarRanking(const Ranking *ranking);

void carregarRanking(Ranking *ranking);

void limparRanking(Ranking *ranking);

void removerJogador(Ranking *ranking, char *nome);
