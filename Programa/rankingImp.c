#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED "\x1b[31m" // coloca cor nos textos
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m" // cor padrao

void insertionSort(Jogador *ranking, int numJogadores, int tipo)
{
  int i, j;
  Jogador key;
  if (tipo == 1)
  {
    for (i = 1; i < numJogadores && i <= 10; i++)
    {
      key = ranking[i];
      j = i - 1;

      while (j >= 0 && ranking[j].tempoAreaCentral < key.tempoAreaCentral)
      {
        ranking[j + 1] = ranking[j];
        j = j - 1;
      }
      ranking[j + 1] = key;
    }
  }
  else if (tipo == 2)
  {
    for (i = 1; i < numJogadores && i <= 10; i++)
    {
      key = ranking[i];
      j = i - 1;

      while (j >= 0 && ranking[j].pontos < key.pontos)
      {
        ranking[j + 1] = ranking[j];
        j = j - 1;
      }
      ranking[j + 1] = key;
    }
  }
  else
  {
    printf("Erro na ordenacao!");
  }
}

void exibeRanking(Jogador *ranking, int numJogadores)
{
  printf("    NOME:     TEMPO TOTAL:   TEMPO AREA CENTRAL:   PONTUACAO:\n\n");
  for (int i = 0; i < numJogadores && i < 10; i++)
  {
    printf("%d - %s\t     %.2f\t\t   %.2f\t\t   %d\n", i + 1, ranking[i].nome, ranking[i].tempoTotal, ranking[i].tempoAreaCentral, ranking[i].pontos);
  }
  printf("\n");
}

Jogador *lerRanking(const char *nomeArquivo, int *numJogadores)
{
  FILE *arquivo = fopen(nomeArquivo, "rb");
  if (!arquivo)
  {
    perror("Erro ao abrir o arquivo");
    exit(EXIT_FAILURE);
  }

  // Obter o tamanho do arquivo
  fseek(arquivo, 0, SEEK_END);
  long tamanhoArquivo = ftell(arquivo);
  rewind(arquivo);

  // Calcular quantos jogadores existem no arquivo
  *numJogadores = tamanhoArquivo / sizeof(Jogador);
  // Alocar memória para o vetor de jogadores
  Jogador *ranking = malloc(*numJogadores * sizeof(Jogador));
  if (!ranking)
  {
    perror("Erro de alocação de memória");
    exit(EXIT_FAILURE);
  }

  // Ler os jogadores do arquivo para o vetor
  fread(ranking, sizeof(Jogador), *numJogadores, arquivo);

  fclose(arquivo);
  return ranking;
}

void salvarRanking(const char *nomeArquivo, Jogador *ranking, int numJogadores)
{
  FILE *arquivo = fopen(nomeArquivo, "wb");
  if (!arquivo)
  {
    perror("Erro ao abrir o arquivo");
    exit(EXIT_FAILURE);
  }

  // Escrever os jogadores no arquivo
  fwrite(ranking, sizeof(Jogador), numJogadores, arquivo);

  fclose(arquivo);
}

Jogador *retornaJogador(Jogador *jogadores, int numJogadores, char *nome, char *senha)
{
  for (int i = 0; i < numJogadores; i++)
  {
    if (senha == NULL) // Verifica somente o nome
    {
      if (strcmp(jogadores[i].nome, nome) == 0) // Se existir um nome igual não é possivel cria novo jogador
      {
        return &jogadores[i];
      }
    }
    else if (strcmp(jogadores[i].nome, nome) == 0 && strcmp(jogadores[i].senha, senha) == 0) // verifica se o jogador e senha
    {
      return &jogadores[i];
    }
  }
  return NULL;
}

Jogador *adicionarJogador(Jogador *jogadores, int *numJogadores, char *nome, char *senha)
{
  *numJogadores += 1;
  jogadores = realloc(jogadores, (*numJogadores) * sizeof(Jogador));
  if (!jogadores)
  {
    perror("Erro ao realocar memória");
    exit(EXIT_FAILURE);
  }
  strcpy(jogadores[*numJogadores - 1].nome, nome);
  strcpy(jogadores[*numJogadores - 1].senha, senha);
  jogadores[*numJogadores - 1].tempoAreaCentral = 0;
  jogadores[*numJogadores - 1].pontos = 0;
  jogadores[*numJogadores - 1].tempoTotal = 0;
  return &jogadores[*numJogadores - 1];
}
