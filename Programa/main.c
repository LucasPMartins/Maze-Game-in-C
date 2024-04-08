#include "arvore.h"
#include "grafos.h"
#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h> // Para a função sleep_ms

void print_logo()
{
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
}


void imprimelento(char *p, int N) {
  for (int i = 0; *(p + i) != '\0'; i++) {
    printf("%c", *(p + i));
    fflush(stdout);
  }
}

Jogador iniciarJogo(double *tempoAreaCentral) {
  struct timeval inicio, fim;
  ArvoreBinaria arvore = criarArvore();
  TipoGrafo grafo1, grafo2, grafo3, areaCentral;
  grafo1.numVertices = 3;
  grafo2.numVertices = 4;
  grafo3.numVertices = 5;
  areaCentral.numVertices = 7;

  FGVazio(&grafo1);
  FGVazio(&grafo2);
  FGVazio(&grafo3);
  FGVazio(&areaCentral);

  // Conexões do Grafo 1
  InsereAresta(0, 1, 0, &grafo1, 0, 0); // Aresta normal
  InsereAresta(1, 2, 0, &grafo1, 1, 0); // Aresta para saída
  InsereAresta(2, 0, 0, &grafo1, 0, 1); // Aresta para sumidouro

  // Conexões do Grafo 2
  InsereAresta(0, 1, 0, &grafo2, 0, 0); // Aresta normal
  InsereAresta(1, 2, 0, &grafo2, 0, 0); // Aresta normal
  InsereAresta(2, 3, 0, &grafo2, 1, 0); // Aresta para saída
  InsereAresta(3, 1, 0, &grafo2, 0, 1); // Aresta para sumidouro

  // Conexões do Grafo 3 (grafo raiz)
  InsereAresta(0, 1, 0, &grafo3, 0, 0); // Aresta ponderada
  InsereAresta(1, 2, 0, &grafo3, 0, 0); // Aresta ponderada
  InsereAresta(2, 3, 0, &grafo3, 1, 0); // Aresta ponderada para saída
  InsereAresta(3, 4, 0, &grafo3, 0, 1); // Aresta ponderada para sumidouro
  InsereAresta(4, 0, 0, &grafo3, 0,
               0); // Aresta ponderada de volta ao início (opcional)

  // Adicionando arestas à área central
  InsereAresta(0, 1, 5, &areaCentral, 0, 0); // Aresta ponderada comum
  InsereAresta(1, 2, 3, &areaCentral, 0, 1); // Sumidouro no vértice 2 com peso
  InsereAresta(1, 3, 2, &areaCentral, 1, 0); // Saída no vértice 3 com peso
  InsereAresta(2, 4, 1, &areaCentral, 0, 1);
  InsereAresta(2, 2, 1, &areaCentral, 0, 0);

  // Inserindo os grafos na árvore
  inserir(&arvore, grafo1, 0);
  inserir(&arvore, grafo2, 0);
  inserir(&arvore, grafo3, 0);
  inserir(&arvore, areaCentral, 1);

  // Iniciando o jogo percorrendo a árvore em pós-ordem e jogando cada fase
  Jogador jogador;
  jogador.pontos = 0;
  jogador.tempoTotal = 0;
  jogador.fasesCompletas = 0;
  printf("Entre com o nome do jogador: ");
  fgets(jogador.nome, sizeof(jogador.nome), stdin);
  // Remove o caractere de nova linha, se presente
  jogador.nome[strcspn(jogador.nome, "\n")] = 0;
  printf("Bem-vindo, %s!\n", jogador.nome);
  gettimeofday(&inicio, NULL);
  iniciarJogoComPosOrdem(&arvore, &jogador);
  gettimeofday(&fim, NULL);
  *tempoAreaCentral = (double)(fim.tv_sec - inicio.tv_sec) + (double)(fim.tv_usec - inicio.tv_usec) / 1000000.0;
  liberarArvore(&arvore);
  return jogador;
}

int main() {
  struct timeval inicio, fim;
  double tempoAreaCentral;
  double tempo_total;
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
      gettimeofday(&inicio, NULL);
      Jogador jogador =
          iniciarJogo(&tempoAreaCentral); // Essa função precisa ser ajustada conforme descrito
      gettimeofday(&fim, NULL);
      tempo_total = (double)(fim.tv_sec - inicio.tv_sec) + (double)(fim.tv_usec - inicio.tv_usec) / 1000000.0;
      printf("Tempo total de jogo: %.2f segundos\n", tempo_total);
      jogador.tempoTotal = tempo_total;
      jogador.tempoAreaCentral = tempoAreaCentral;
      printf("\nRetornando ao menu principal...\n");

      // Adiciona o jogador ao ranking
      adicionaJogador(ranking, jogador.nome, jogador.tempoTotal,
                      jogador.pontos,jogador.tempoAreaCentral);
      printf("Resultado adicionado ao ranking.\n");

      // Salva o ranking atualizado
      salvarRanking(ranking);
      printf("Ranking atualizado salvo com sucesso.\n");
      break;
    case 2:
      print_logo();
      printf("\n                         --===  RANKING  ===--\n\n");
      printf("                   1 - RANKING POR TEMPO NA AREA CENTRAL\n");
      printf("                      2 - RANKING POR PONTUACAO\n\n");
      printf("                          Digite sua Opcao:");
      scanf("%d", &op);
      if (op == 1) {

        print_logo();
        printf("\n                 --===  RANKING POR TEMPO NA AREA CENTRAL  ===--\n\n");
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
      printf("\nOpcao invalida!\n");
    }
  } while (op != 0);

  free(ranking);
  return 0;
}