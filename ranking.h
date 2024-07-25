#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED

#include <stdio.h>
#include <string.h>

typedef struct
{
  char nome[25];
  double tempoTotal;
  double tempoAreaCentral;
  int pontos;
} Jogador;

void insertionSort(Jogador *ranking, int numJogadores, int tipo);
void exibeRanking(Jogador *ranking, int numJogadores);
Jogador *lerRanking(const char *nomeArquivo, int *numJogadores);
void salvarRanking(const char *nomeArquivo, Jogador *ranking, int numJogadores);
Jogador *retornaJogador(Jogador *jogadores, int numJogadores, char *nome);
Jogador *adicionarJogador(Jogador *jogadores, int *numJogadores, const char *nome);

#endif // RANKING_H_INCLUDED