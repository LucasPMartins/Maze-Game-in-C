#include "arvore.h"
#include "grafos.h"
#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para a função sleep_ms

void print_logo() {
  printf(" __     __     _   _     __   __     __     __ "
         "\n");
  printf("/\\  _\\   /\\  _\\   /\\ \"-.\\ \\   /\\__  _\\ /\\  == \\   "
         "/\\  __ \\   /\\ \\      \n");
  printf("\\ \\ \\__  \\ \\  _\\   \\ \\ \\-.  \\  \\//\\ \\/ \\ \\  __<   "
         "\\ \\  _ \\  \\ \\ \\_ \n");
  printf(" \\ \\__\\  \\ \\_\\  \\ \\\\ \"\\\\    \\ \\\\  \\ \\_\\ "
         "\\\\  \\ \\\\ \\\\  \\ \\__\\ \n");
  printf("  \\/__/   \\/_/   \\// \\//     \\//   \\// //   "
         "\\//\\//   \\/___/\n");
  printf(" _    _     __     __     __               __        "
         "     \n");
  printf("/\\ \"-./  \\   /\\  _ \\   /\\_  \\   /\\  __\\             "
         "/\\_\\                     \n");
  printf("\\ \\ \\-./\\ \\  \\ \\  _ \\  \\//  /_  \\ \\  _\\            "
         "/\\ \\_\\                        \n");
  printf(" \\ \\\\ \\ \\\\  \\ \\\\ \\\\   /\\__\\  \\ \\__\\        "
         "  \\ \\/ / /                            \n");
  printf("  \\//  \\//   \\//\\//   \\/__/   \\/__/           "
         "\\///                  \n");
}

void imprimelento(char *p, int N) {
  for (int i = 0; *(p + i) != '\0'; i++) {
    printf("%c", *(p + i));
    fflush(stdout);
  }
}

void iniciarJogo() {
  ArvoreBinaria arvore = criarArvore();
  TipoGrafo grafo1, grafo2, grafo3;
  grafo1.numVertices = 3;
  grafo2.numVertices = 4;
  grafo3.numVertices = 5;

  FGVazio(&grafo1);
  FGVazio(&grafo2);
  FGVazio(&grafo3);

  // Conexões do Grafo 1
  InsereAresta(0, 1, 1, &grafo1, 0, 0); // Aresta normal
  InsereAresta(1, 2, 1, &grafo1, 1, 0); // Aresta para saída
  InsereAresta(2, 0, 1, &grafo1, 0, 1); // Aresta para sumidouro

  // Conexões do Grafo 2
  InsereAresta(0, 1, 1, &grafo2, 0, 0); // Aresta normal
  InsereAresta(1, 2, 1, &grafo2, 0, 0); // Aresta normal
  InsereAresta(2, 3, 1, &grafo2, 1, 0); // Aresta para saída
  InsereAresta(3, 1, 1, &grafo2, 0, 1); // Aresta para sumidouro

  // Conexões do Grafo 3 (grafo raiz)
  InsereAresta(0, 1, 10, &grafo3, 0, 0); // Aresta ponderada
  InsereAresta(1, 2, 20, &grafo3, 0, 0); // Aresta ponderada
  InsereAresta(2, 3, 30, &grafo3, 1, 0); // Aresta ponderada para saída
  InsereAresta(3, 4, 40, &grafo3, 0, 1); // Aresta ponderada para sumidouro
  InsereAresta(4, 0, 50, &grafo3, 0,
               0); // Aresta ponderada de volta ao início (opcional)

  // Inserindo os grafos na árvore
  inserir(&arvore, grafo1);
  inserir(&arvore, grafo2);
  inserir(&arvore, grafo3);

  // Iniciando o jogo percorrendo a árvore em pós-ordem e jogando cada fase
  percorrerPosOrdemInterativo(arvore.raiz);

  liberarArvore(&arvore);
}

int main() {
  int op;
  Ranking *ranking = (Ranking *)malloc(sizeof(Ranking));

  carregarRanking(ranking);

  do {

    print_logo();
    printf("\n                           1 - JOGAR\n");
    printf("                           2 - RANKING\n");
    printf("                           3 - SOBRE\n");
    printf("                           0 - SAIR\n\n");
    printf("                       Digite sua Opcao: ");
    scanf("%d", &op);
    getchar();

    switch (op) {
    case 1:
      print_logo();
      printf("\nIniciando o jogo...\n");

      iniciarJogo();

      printf("\nRetornando ao menu principal...\n");
      break;
    case 2:
      print_logo();
      printf("\n                         --===  RANKING  ===--\n\n");
      printf("                      1 - RANKING POR TEMPO TOTAL\n");
      printf("                      2 - RANKING POR PONTUACAO\n\n");
      printf("                          Digite sua Opcao:");
      scanf("%d", &op);
      if (op == 1) {

        print_logo();
        printf("\n                 --===  RANKING POR TEMPO TOTAL  ===--\n\n");
        insertionSort(ranking, 1);
        exibeRanking(ranking, 1);
      } else if (op == 2) {
        print_logo();
        printf("\n                  --===  RANKING POR PONTUACAO  ===--\n\n");
        insertionSort(ranking, 2);
        exibeRanking(ranking, 2);
      } else {
        printf("\n                            OPCAO INVALIDA!\n");
      }
      printf("\n                     Pressione \"Enter\" para voltar...");
      while (getchar() != '\n')
        ;
      op = 4;
      break;
    case 3:
      print_logo();
      printf("\n(!) SOBRE:\n");
      printf("O jogo eh um labirinto interativo onde o jogador deve navegar "
             "por diferentes\n");
      printf("areas, utilizando conceitos de  Grafos, Arvores Binarias e "
             "Ordenacao. Proje-\n");
      printf("to feito para um  trabalho de conclusao de disciplina (Algoritmo "
             "e Estrutura\n");
      printf("de Dados 2).\n");
      printf("Criado por: Lucas Martins, Caue Grassi e Pedro Trevisan\n");
      printf("\n(?) COMO JOGAR:\n");
      printf("1 - Areas do Labirinto: ");
      printf("O jogador  interage  diretamente escolhendo caminhos\n");
      printf("para sair do labirinto. Se escolher  um caminho sem saida, volta "
             "a sala ini-\n");
      printf("cial (derrota). Encontrar a saida leva a uma nova area (avanco "
             "de fase).\n");
      printf("2 - Area  Central:  ");
      printf("Sala especial com pontuacao para avancos. Permite ao jo-\n");
      printf("gador retroceder uma sala,sacrificando pontos. A derrota ocorre "
             "se encontrar\n");
      printf("uma sala sem saida e o jogador estiver sem pontos.\n");
      printf("3 - Dificuldade Progressiva: ");
      printf("O numero de salas aumenta a cada fase, tornando\n");
      printf("o percurso mais dificil.\n");
      printf("4 - Mapa do Labirinto: ");
      printf("Caminhos levam  a Area Central. O  progresso eh feito\n");
      printf("completando areas sucessivas. Todas  as areas  levam a Area "
             "Central.\n");
      printf("5 - Sistema de Ranking: ");
      printf("Baseado no tempo e na pontuacao na Area Central.\n");
      printf("Armazena as ultimas 10 vitorias, classificando os jogadores  por "
             "nome, tempo\n");
      printf("total, tempo por area e pontuacao.\n");
      printf("\nPressione \"Enter\" para voltar...");
      while (getchar() != '\n')
        ;
      break;
    case 0:
      printf("Saindo do jogo...\n");

      break;
    default:
      printf("\nOpção inválida!\n");
    }
  } while (op != 0);

  free(ranking);
  return 0;
}
