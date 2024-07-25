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

  if (numJogadores <= 0)
  {
    return;
  }

  // Ordenar por tempo na área central
  if (tipo == 1)
  {
    for (i = 1; i < numJogadores && i <= 10; i++)
    {
      key = ranking[i];
      j = i - 1;

      while (j >= 0 && ranking[j].tempoAreaCentral < key.tempoAreaCentral)
      {
        ranking[j + 1] = ranking[j];
        j--;
      }
      ranking[j + 1] = key;
    }
  }
  // Ordenar por pontuação
  else if (tipo == 2)
  {
    for (i = 1; i < numJogadores && i <= 10; i++)
    {
      key = ranking[i];
      j = i - 1;

      while (j >= 0 && ranking[j].pontos < key.pontos)
      {
        ranking[j + 1] = ranking[j];
        j--;
      }
      ranking[j + 1] = key;
    }
  }
  else
  {
    printf("Erro na ordenacao: tipo de ordenacao invalido!\n");
  }
}

void exibeRanking(Jogador *ranking, int numJogadores)
{
  printf("    NAME:      TOTAL TIME:    CENTRAL AREA TIME:     SCORE:\n\n");

  if (numJogadores == 0)
  {
    printf(ANSI_COLOR_GREEN);
    printf("\t\t    THE RANKING IS EMPTY!\n\n");
    printf(ANSI_COLOR_RESET);
    return;
  }

  for (int i = 0; i < numJogadores && i < 10; i++)
  {
    printf("%d - %s\t     %.2f\t   %.2f\t\t   %d\n", i + 1, ranking[i].nome, ranking[i].tempoTotal, ranking[i].tempoAreaCentral, ranking[i].pontos);
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
  if (numJogadores > 10) // Salva somente os 10 melhores
  {
    fwrite(ranking, sizeof(Jogador), 10, arquivo);
  }
  else
  {
    fwrite(ranking, sizeof(Jogador), numJogadores, arquivo);
  }

  // Escrever os jogadores no arquivo

  fclose(arquivo);
}

Jogador *retornaJogador(Jogador *jogadores, int numJogadores, char *nome)
{
  for (int i = 0; i < numJogadores; i++)
  {
    if (strcmp(jogadores[i].nome, nome) == 0) // verifica se o jogador existe
    {
      return &jogadores[i];
    }
  }
  return NULL;
}

Jogador *adicionarJogador(Jogador *jogadores, int *numJogadores, const char *nome)
{
  if (!nome || !numJogadores)
  {
    fprintf(stderr, "Argumentos inválidos passados para adicionarJogador.\n");
    return NULL;
  }

  // Aumenta o número de jogadores
  (*numJogadores)++;

  // Realoca memória para acomodar o novo jogador
  jogadores = realloc(jogadores, (*numJogadores) * sizeof(Jogador));
  if (!jogadores)
  {
    perror("Erro ao realocar memória");
    return NULL; // Retorna NULL para indicar falha
  }

  // Inicializa o novo jogador
  Jogador *novoJogador = &jogadores[*numJogadores - 1];
  memset(novoJogador, 0, sizeof(Jogador)); // Inicializa com zeros
  strncpy(novoJogador->nome, nome, sizeof(novoJogador->nome) - 1);
  novoJogador->nome[sizeof(novoJogador->nome) - 1] = '\0'; // Garante terminação nula

  return novoJogador;
}
