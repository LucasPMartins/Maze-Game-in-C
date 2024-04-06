#include "grafos.h"
#include "ranking.h"
#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h> // Utilizado para usar teclas do teclado na seleção de opcões

#define ANSI_COLOR_RED "\x1b[31m"     // Cor: Vermelho
#define ANSI_COLOR_GREEN "\x1b[32m"   // Cor: Verde
#define ANSI_COLOR_YELLOW "\x1b[33m"  // Cor: Amarelo
#define ANSI_COLOR_BLUE "\x1b[34m"    // Cor: Azul
#define ANSI_COLOR_MAGENTA "\x1b[35m" // Cor: Magenta
#define ANSI_COLOR_CYAN "\x1b[36m"    // Cor: Ciano
#define ANSI_COLOR_RESET "\x1b[0m"    // Cor: Padrão

void print_logo();
void imprimelento(char *p, int N);

int main()
{
  int op, i;
  char tecla;
  Ranking *ranking = (Ranking*)malloc(1*sizeof(Ranking));
  carregarRanking(ranking);
  do
  {
    system("cls");
    print_logo();
    printf("\n                           1 - JOGAR\n");
    printf("                           2 - RANKING\n");
    printf("                           3 - SOBRE\n");
    printf("                           0 - SAIR\n\n");
    printf("                       Digite sua Opcao:");
    scanf("%d", &op);
    switch (op)
    {
    case 1:

    case 2:
      system("cls");
      print_logo();
      printf(ANSI_COLOR_GREEN);
      printf("\n                         --===  RANKING  ===--\n\n");
      printf(ANSI_COLOR_RESET);
      printf("                      1 - RANKING POR TEMPO TOTAL\n");
      printf("                      2 - RANKING POR PONTUACAO\n\n");
      printf("                          Digite sua Opcao:");
      scanf("%d", &op);
      if(op == 1){
        system("cls");
        print_logo();
        printf(ANSI_COLOR_GREEN);
        printf("\n                 --===  RANKING POR TEMPO TOTAL  ===--\n\n");
        printf(ANSI_COLOR_RESET);
        insertionSort(ranking,1);
        exibeRanking(ranking,1);
      }else if (op == 2){
        system("cls");
        print_logo();
        printf(ANSI_COLOR_GREEN);
        printf("\n                  --===  RANKING POR PONTUACAO  ===--\n\n");
        printf(ANSI_COLOR_RESET);
        insertionSort(ranking,2);
        exibeRanking(ranking,2);
      }else{
        printf(ANSI_COLOR_RED);
        printf("\n                            OPCAO INVALIDA!\n");
        printf(ANSI_COLOR_RESET);
      }
      printf(ANSI_COLOR_GREEN);
      printf("\n                     Pressione \"ESC\" para voltar...");
      printf(ANSI_COLOR_RESET);
      while (1)
      {
        if (_kbhit())
        {
          tecla = _getch();
          if (tecla == 27)
          {        // Verifica se a tecla pressionada é o código ASCII do "Esc"
            break; // Retorna ao menu anterior
          }
        }
      }
      op = 4;
      break;
    case 3:
      system("cls");
      print_logo();
      printf(ANSI_COLOR_GREEN);
      printf("\n(!) SOBRE:\n");
      printf(ANSI_COLOR_RESET);
      printf("O jogo eh um labirinto interativo onde o jogador deve navegar por diferentes\n");
      printf("areas, utilizando conceitos de  Grafos, Arvores Binarias e Ordenacao. Proje-\n");
      printf("to feito para um  trabalho de conclusao de disciplina (Algoritmo e Estrutura\n");
      printf("de Dados 2).\n");
      printf("Criado por: Lucas Martins, Caue Grassi e Pedro Trevisan\n");
      printf(ANSI_COLOR_GREEN);
      printf("\n(?) COMO JOGAR:\n");
      printf("1 - Areas do Labirinto: ");
      printf(ANSI_COLOR_RESET);
      printf("O jogador  interage  diretamente escolhendo caminhos\n");
      printf("para sair do labirinto. Se escolher  um caminho sem saida, volta a sala ini-\n");
      printf("cial (derrota). Encontrar a saida leva a uma nova area (avanco de fase).\n");
      printf(ANSI_COLOR_GREEN);
      printf("2 - Area  Central:  ");
      printf(ANSI_COLOR_RESET);
      printf("Sala especial com pontuacao para avancos. Permite ao jo-\n");
      printf("gador retroceder uma sala,sacrificando pontos. A derrota ocorre se encontrar\n");
      printf("uma sala sem saida e o jogador estiver sem pontos.\n");
      printf(ANSI_COLOR_GREEN);
      printf("3 - Dificuldade Progressiva: ");
      printf(ANSI_COLOR_RESET);
      printf("O numero de salas aumenta a cada fase, tornando\n");
      printf("o percurso mais dificil.\n");
      printf(ANSI_COLOR_GREEN);
      printf("4 - Mapa do Labirinto: ");
      printf(ANSI_COLOR_RESET);
      printf("Caminhos levam  a Area Central. O  progresso eh feito\n");
      printf("completando areas sucessivas. Todas  as areas  levam a Area Central.\n");
      printf(ANSI_COLOR_GREEN);
      printf("5 - Sistema de Ranking: ");
      printf(ANSI_COLOR_RESET);
      printf("Baseado no tempo e na pontuacao na Area Central.\n");
      printf("Armazena as ultimas 10 vitorias, classificando os jogadores  por nome, tempo\n");
      printf("total, tempo por area e pontuacao.\n");
      printf(ANSI_COLOR_GREEN);
      printf("\nPressione \"ESC\" para voltar...");
      printf(ANSI_COLOR_RESET);
      while (1)
      {
        if (_kbhit())
        {
          tecla = _getch();
          if (tecla == 27)
          {        // Verifica se a tecla pressionada é o código ASCII do "Esc"
            break; // Retorna ao menu anterior
          }
        }
      }
      break;
    case 0:
      system("cls");
      printf(ANSI_COLOR_YELLOW);
      printf("Saindo");
      i = 3;
      while (i > 0)
      {
        i--;
        imprimelento("...", 400);
        printf("\b\b\b   \b\b\b");
      }
      printf(ANSI_COLOR_RESET);
      break;
    default:
      break;
    }
  } while (op != 0);
  salvarRanking(ranking);
  return 0;
}

void print_logo()
{
  printf(ANSI_COLOR_GREEN);
  printf(" ______     ______     __   __     ______   ______     ______     __ \n");      
  printf("/\\  ___\\   /\\  ___\\   /\\ \"-.\\ \\   /\\__  _\\ /\\  == \\   /\\  __ \\   /\\ \\      \n");
  printf("\\ \\ \\____  \\ \\  __\\   \\ \\ \\-.  \\  \\/_/\\ \\/ \\ \\  __<   \\ \\  __ \\  \\ \\ \\____ \n");
  printf(" \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \"\\_\\    \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_\\ \\_\\  \\ \\_____\\ \n");
  printf("  \\/_____/   \\/_____/   \\/_/ \\/_/     \\/_/   \\/_/ /_/   \\/_/\\/_/   \\/_____/ \n");
  printf("                                                                \n");
  printf(" __    __     ______     ______     ______               ____             \n");
  printf("/\\ \"-./  \\   /\\  __ \\   /\\___  \\   /\\  ___\\             /\\___\\                     \n");
  printf("\\ \\ \\-./\\ \\  \\ \\  __ \\  \\/_/  /__  \\ \\  __\\            /\\ \\___\\                        \n");
  printf(" \\ \\_\\ \\ \\_\\  \\ \\_\\ \\_\\   /\\_____\\  \\ \\_____\\          \\ \\/ / /                            \n");
  printf("  \\/_/  \\/_/   \\/_/\\/_/   \\/_____/   \\/_____/           \\/_/_/                  \n");
  printf(ANSI_COLOR_RESET);
}

void imprimelento(char *p, int N)
{
  int i;
  for (i = 0; *(p + i) != '\0'; i++)
  {
    printf("%c", *(p + i));
    fflush(stdout);
    Sleep(N);
  }
}

/*TipoGrafo grafo;
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
  */ 
     
       
        



