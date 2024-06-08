#include "arvore.h"
#include "grafo.h"
#include "pilha.h"
#include "ranking.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <sys/time.h>
#include <windows.h> //sleep

#define ANSI_COLOR_RED "\x1b[31m" // coloca cor nos textos
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m" // cor padrao

void print_logo();
void printMenuJogar(Jogador *ranking, int *numJogadores);
void printRanking(Jogador *ranking, int numJogadores);
void printSobre();

void iniciarJogo(Jogador *jogador);
int JogarArea(Jogador *jogador, Grafo *grafo);
ArvoreBinaria *inicializarAreas();
int retornaSala(Grafo *grafo, int sala_atual, int num);
void fornecerDica(Grafo *grafo, int sala_atual);

void imprimelento(char *p, int N);

int main()
{
    char *menuOptions[] = {" P L A Y\n", " R A N K I N G\n", " A B O U T\n", " E X I T\n"};
    int numOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
    int selectedIndex = 0, sair = 0, i;
    char input;

    int numJogadores = 0;
    Jogador *jogadores = malloc(sizeof(Jogador));
    // lerRanking("ranking.txt", &numJogadores);

    do
    {
        print_logo();
        printf("\nSelect an OPTION:\n\n");
        // Imprime as opções com a seleção indicada
        for (int i = 0; i < numOptions; i++)
        {
            if (selectedIndex == i)
            {
                if (selectedIndex == 0)
                {
                    printf(ANSI_COLOR_GREEN);
                    printf("   %s\n", menuOptions[i]);
                    printf(ANSI_COLOR_RESET);
                }
                else
                {
                    printf(ANSI_COLOR_GREEN);
                    printf("\n   %s\n", menuOptions[i]);
                    printf(ANSI_COLOR_RESET);
                }
            }
            else
            {
                printf("%s", menuOptions[i]);
            }
        }

        // Lê a tecla pressionada
        input = getch();

        // Atualiza a seleção com base na tecla pressionada
        switch (input)
        {
        case 'w':
        case 'W':
        case 72: // Código ASCII para seta para cima
            selectedIndex = (selectedIndex - 1 + numOptions) % numOptions;
            break;
        case 's':
        case 'S':
        case 80: // Código ASCII para seta para baixo
            selectedIndex = (selectedIndex + 1) % numOptions;
            break;
        case 13:                                 // Código ASCII para tecla Enter
            if (selectedIndex == numOptions - 1) // SAIR
            {
                printf(ANSI_COLOR_YELLOW);
                printf("Exiting the game");
                for (i = 0; i < 3; i++)
                {
                    imprimelento("...", 250);
                    printf("\b\b\b   \b\b\b");
                }
                printf("\n\n");
                printf(ANSI_COLOR_RESET);
                sair = 1; // Define a variável para sair do menu
            }
            else
            {
                if (selectedIndex == 0) // JOGAR
                {
                    printMenuJogar(jogadores, &numJogadores);
                }
                else if (selectedIndex == 1) // RANKING
                {
                    printRanking(jogadores, numJogadores);
                }
                else if (selectedIndex == 2) // SOBRE
                {
                    printSobre();
                }
            }
            break;
        default:
            break;
        }
    } while (sair != 1); // Loop até que a opção "Sair" seja selecionada

    salvarRanking("ranking.txt", jogadores, numJogadores);

    // Liberar a memória alocada para o vetor de jogadores
    free(jogadores);

    return 0;
}

void print_logo()
{

    system("cls");
    printf(ANSI_COLOR_GREEN);
    printf(" ______  ______  __   __  ______  ______  ______  __       \n");
    printf("/\\  ___\\/\\  ___\\/\\ \"-.\\ \\/\\__  _\\/\\  == \\/\\  __ \\/\\ \\      \n");
    printf("\\ \\ \\___\\ \\  __\\\\ \\ \\-.  \\/_/\\ \\/\\ \\  __<\\ \\  __ \\ \\ \\____ \n");
    printf(" \\ \\_____\\ \\_____\\ \\_\\\\\"\\_\\ \\ \\_\\ \\ \\_\\ \\_\\ \\_\\ \\_\\ \\_____\\ \n");
    printf("  \\/_____/\\/_____/\\/_/ \\/_/  \\/_/  \\/_/ /_/\\/_/\\/_/\\/_____/ \n");
    // printf("                                                                \n");
    printf(" __    __  ______  ______  ______             ____             \n");
    printf("/\\ \"-./  \\/\\  __ \\/\\___  \\/\\  ___\\           /\\___\\                     \n");
    printf("\\ \\ \\-./\\ \\ \\  __ \\/_/  /_\\ \\  __\\          /\\ \\___\\                        \n");
    printf(" \\ \\_\\ \\ \\_\\ \\_\\ \\_\\/\\_____\\ \\_____\\        \\ \\/ / /                            \n");
    printf("  \\/_/  \\/_/\\/_/\\/_/\\/_____/\\/_____/         \\/_/_/                  \n\n");
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

void printSobre()
{
    char tecla;
    while (1)
    {
        if (_kbhit())
        {
            tecla = _getch();
            print_logo();
            printf(ANSI_COLOR_GREEN);
            printf("-------==================< A B O U T >==================-------\n\n");
            printf("(!) ABOUT:\n");
            printf(ANSI_COLOR_RESET);
            printf("The game is an interactive maze where the player  must navigate\n");
            printf("through different areas using Graphs, Binary Trees, and Sorting\n");
            printf("concepts. Project done for a conclusion of discipline work \n");
            printf("(Algorithms and Data Structures 2).\n\n");
            printf("Created by: Lucas Martins, Caue Grassi, and Pedro Trevisan\n");
            printf(ANSI_COLOR_GREEN);
            printf("\n(?) HOW TO PLAY:\n");
            printf("1 - Maze Areas:");
            printf(ANSI_COLOR_RESET);
            printf(" The player interacts directly by choosing paths\n");
            printf("to exit  the maze. Choosing a dead-end path  leads  back to the \n");
            printf("starting room (defeat). Finding the exit leads to a new area.\n");
            printf(ANSI_COLOR_GREEN);
            printf("2 - Central Area: ");
            printf(ANSI_COLOR_RESET);
            printf("Special room with score for level ups. Allows\n");
            printf("the player to go back  one room, sacrificing points. Defeat oc-\n");
            printf("curs if a  dead-end room is  encountered and the  player has no \n");
            printf("points left.\n");
            printf(ANSI_COLOR_GREEN);
            printf("3 - Progressive Difficulty: ");
            printf(ANSI_COLOR_RESET);
            printf("The  number of  rooms  increases in\n");
            printf("each level, making the path more difficult.\n");
            printf(ANSI_COLOR_GREEN);
            printf("4 - Maze Map: ");
            printf(ANSI_COLOR_RESET);
            printf("Paths lead to the  Central Area. Progress is made\n");
            printf("by completing  successive areas. All areas  lead to the Central \n");
            printf("Area.\n");
            printf(ANSI_COLOR_GREEN);
            printf("5 - Ranking System: ");
            printf(ANSI_COLOR_RESET);
            printf("Based on time and score in the Central Area.\n");
            printf("Ranking players by time per area and score.\n\n");
            printf(ANSI_COLOR_GREEN);
            printf("Press 'ESC' to EXIT...");
            printf(ANSI_COLOR_RESET);
            if (tecla == 27)
            { // Verifica se a tecla pressionada é o código ASCII do "Esc"
                break;
            }
        }
    }
}

void printRanking(Jogador *jogadores, int numJogadores)
{
    char *menuOptions[] = {" SCORE RANKING\n", " TIME RANKING\n", " BACK\n"};
    int numOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
    int selectedIndex = 0, sair = 0;
    char input;

    int i;
    do
    {
        print_logo();
        printf(ANSI_COLOR_GREEN);
        printf("------================< R A N K I N G >================------\n");
        printf(ANSI_COLOR_RESET);
        printf("\nSelect an OPTION:\n\n");
        // Imprime as opções com a seleção indicada
        for (int i = 0; i < numOptions; i++)
        {
            if (selectedIndex == i)
            {
                if (selectedIndex == 0)
                {
                    printf(ANSI_COLOR_GREEN);
                    printf("   %s\n", menuOptions[i]);
                    printf(ANSI_COLOR_RESET);
                }
                else
                {
                    printf(ANSI_COLOR_GREEN);
                    printf("\n   %s\n", menuOptions[i]);
                    printf(ANSI_COLOR_RESET);
                }
            }
            else
            {
                printf("%s", menuOptions[i]);
            }
        }

        // Lê a tecla pressionada
        input = getch();

        // Atualiza a seleção com base na tecla pressionada
        switch (input)
        {
        case 'w':
        case 'W':
        case 72: // Código ASCII para seta para cima
            selectedIndex = (selectedIndex - 1 + numOptions) % numOptions;
            break;
        case 's':
        case 'S':
        case 80: // Código ASCII para seta para baixo
            selectedIndex = (selectedIndex + 1) % numOptions;
            break;
        case 13:                                 // Código ASCII para tecla Enter
            if (selectedIndex == numOptions - 1) // SAIR
            {
                sair = 1; // Define a variável para sair do menu
            }
            else
            {
                if (selectedIndex == 0) // RANKING POR PONTUAÇÃO
                {
                    print_logo();
                    printf(ANSI_COLOR_GREEN);
                    printf("-----============< S C O R E  R A N K I N G >============-----\n\n");
                    printf(ANSI_COLOR_RESET);
                    insertionSort(jogadores, numJogadores, 2);
                    exibeRanking(jogadores, numJogadores);
                    printf(ANSI_COLOR_GREEN);
                    system("pause");
                    printf(ANSI_COLOR_RESET);
                }
                else if (selectedIndex == 1) // RANKING POR TEMPO
                {
                    print_logo();
                    printf(ANSI_COLOR_GREEN);
                    printf("-----=============< T I M E  R A N K I N G >=============-----\n\n");
                    printf(ANSI_COLOR_RESET);
                    insertionSort(jogadores, numJogadores, 1);
                    exibeRanking(jogadores, numJogadores);
                    printf(ANSI_COLOR_GREEN);
                    system("pause");
                    printf(ANSI_COLOR_RESET);
                }
            }
            break;
        default:
            break;
        }
    } while (sair != 1); // Loop até que a opção "Sair" seja selecionada
}

void printMenuJogar(Jogador *jogadores, int *numJogadores)
{
    char nome[50];
    Jogador *jogador;
    int i;

    print_logo();
    printf(ANSI_COLOR_GREEN);
    printf("------===================< P L A Y >===================------\n");
    printf(ANSI_COLOR_RESET);
    printf("\nEnter your name: ");
    printf(ANSI_COLOR_YELLOW);
    setbuf(stdin, NULL);
    scanf("%49s", nome);
    printf(ANSI_COLOR_RESET);

    jogador = retornaJogador(jogadores, *numJogadores, nome);
    if (jogador == NULL) // NOVO JOGADOR
    {
        jogador = adicionarJogador(jogadores, numJogadores, nome);
        if (jogador == NULL)
        {
            printf("Erro na criação de jogador");
            system("pause");
            return;
        }
        printf(ANSI_COLOR_YELLOW);
        printf("\nSAVING");
        i = 3;
        while (i > 0)
        {
            imprimelento("...", 250);
            printf("\b\b\b   \b\b\b");
            i--;
        }
        printf(ANSI_COLOR_RESET);
    }
    else
    {
        printf(ANSI_COLOR_YELLOW);
        printf("\nLOADING");
        i = 3;
        while (i > 0)
        {
            imprimelento("...", 250);
            printf("\b\b\b   \b\b\b");
            i--;
        }
        printf(ANSI_COLOR_RESET);
    }
    iniciarJogo(jogador);
}

void iniciarJogo(Jogador *jogador)
{
    int sair = 0, i;
    int retorno;
    char tecla;

    double tempo;
    struct timeval inicio, fim;

    ArvoreBinaria *arvore = inicializarAreas();
    if (!arvore)
    {
        fprintf(stderr, "Erro ao inicializar a árvore de áreas.\n");
        return;
    }
    Pilha *pilha = inicializarPercurso(arvore); // Pilha de grafos a serem usados
    if (!pilha)
    {
        fprintf(stderr, "Erro ao inicializar a pilha.\n");
        liberarArvore(arvore->raiz);
        free(arvore);
        return;
    }

    gettimeofday(&inicio, NULL); // INICIA O TEMPO TOTAL

    Grafo *grafo = proximoNo(pilha);

    while (grafo != NULL && !sair)
    {
        system("cls");
        print_logo();
        printf(ANSI_COLOR_GREEN);
        printf("-----===============< B E S T  S C O R E >===============-----\n");
        printf(ANSI_COLOR_RESET);
        printf("NAME:      TOTAL TIME:    CENTRAL AREA TIME:     SCORE:\n");
        printf("%s\t     %.2f\t   %.2f\t\t   %d\n", jogador->nome, jogador->tempoTotal, jogador->tempoAreaCentral, jogador->pontos);
        printf(ANSI_COLOR_GREEN);
        printf("------===============<******************>===============------\n");
        printf("\nPress 'Enter' to CONTINUE or 'Esc' to EXIT...\n\n");
        printf(ANSI_COLOR_RESET);
        while (1)
        {
            if (_kbhit())
            {
                tecla = _getch();
                if (tecla == 13) // Verifica se a tecla pressionada é o código ASCII do "Enter"
                {
                    retorno = JogarArea(jogador, grafo);
                    if (retorno == 2)
                    {
                        system("cls");
                        print_logo();
                        printf(ANSI_COLOR_GREEN);
                        printf("-----===============< Y O U R  S C O R E >===============-----\n");
                        printf(ANSI_COLOR_RESET);
                        printf("NAME:      TOTAL TIME:    CENTRAL AREA TIME:     SCORE:\n");
                        printf("%s\t     %.2f\t   %.2f\t\t   %d\n", jogador->nome, jogador->tempoTotal, jogador->tempoAreaCentral, jogador->pontos);
                        printf(ANSI_COLOR_GREEN);
                        printf("------===============<******************>===============------\n\n");
                        system("pause");
                    }
                    if (retorno == 1)
                    {
                        printf(ANSI_COLOR_YELLOW);
                        printf("LOADING NEXT AREA");
                        i = 3;
                        while (i > 0)
                        {
                            imprimelento("...", 250);
                            printf("\b\b\b   \b\b\b");
                            i--;
                        }
                        printf(ANSI_COLOR_RESET);
                        liberarGrafo(grafo);
                    }
                    break; // Sai do loop interno para continuar o jogo
                }
                if (tecla == 27) // Verifica se a tecla pressionada é o código ASCII do "Esc"
                {
                    sair = 1;
                    break;
                }
            }
        }
        if (!sair)
        {
            grafo = proximoNo(pilha);
        }
    }

    gettimeofday(&fim, NULL); // FINALIZA O TEMPO TOTAL
    tempo = (double)(fim.tv_sec - inicio.tv_sec) + (double)(fim.tv_usec - inicio.tv_usec) / 1000000.0;
    jogador->tempoTotal = tempo;

    free(arvore);
    free(pilha);
}

ArvoreBinaria *inicializarAreas()
{
    srand(time(NULL));

    // Grafo 1:
    Grafo *grafo1 = criarGrafo(9, 1);
    adicionarAresta(grafo1, 0, 1, 0);
    adicionarAresta(grafo1, 0, 2, 0);
    adicionarAresta(grafo1, 1, 3, 0);
    adicionarAresta(grafo1, 1, 4, 0);
    adicionarAresta(grafo1, 1, 5, 0);
    adicionarAresta(grafo1, 2, 6, 0);
    adicionarAresta(grafo1, 2, 7, 0);
    adicionarAresta(grafo1, 2, 8, 0);
    defineSaida(grafo1);

    // // Grafo 2:
    Grafo *grafo2 = criarGrafo(9, 1);
    adicionarAresta(grafo2, 0, 1, 0);
    adicionarAresta(grafo2, 0, 2, 0);

    adicionarAresta(grafo2, 1, 3, 0);
    adicionarAresta(grafo2, 1, 4, 0);
    adicionarAresta(grafo2, 1, 5, 0);

    adicionarAresta(grafo2, 2, 6, 0);
    adicionarAresta(grafo2, 2, 7, 0);
    adicionarAresta(grafo2, 2, 8, 0);

    adicionarVerticesExponencialmente(grafo2, 3, 1);
    adicionarVerticesExponencialmente(grafo2, 4, 1);
    adicionarVerticesExponencialmente(grafo2, 5, 1);
    adicionarVerticesExponencialmente(grafo2, 6, 2);
    adicionarVerticesExponencialmente(grafo2, 7, 2);
    adicionarVerticesExponencialmente(grafo2, 8, 2);
    defineSaida(grafo2);

    // // Grafo 3:
    Grafo *grafo3 = criarGrafo(9, 1);
    adicionarAresta(grafo3, 0, 1, 0);
    adicionarAresta(grafo3, 0, 2, 0);

    adicionarAresta(grafo3, 1, 3, 0);
    adicionarAresta(grafo3, 1, 4, 0);
    adicionarAresta(grafo3, 1, 5, 0);

    adicionarAresta(grafo3, 2, 6, 0);
    adicionarAresta(grafo3, 2, 7, 0);
    adicionarAresta(grafo3, 2, 8, 0);

    adicionarVerticesExponencialmente(grafo3, 3, 1);
    adicionarVerticesExponencialmente(grafo3, 4, 1);
    adicionarVerticesExponencialmente(grafo3, 5, 1);
    adicionarVerticesExponencialmente(grafo3, 6, 2);
    adicionarVerticesExponencialmente(grafo3, 7, 2);
    adicionarVerticesExponencialmente(grafo3, 8, 2);

    adicionarVerticesExponencialmente(grafo3, 9, 3);
    adicionarVerticesExponencialmente(grafo3, 10, 3);
    adicionarVerticesExponencialmente(grafo3, 11, 3);
    adicionarVerticesExponencialmente(grafo3, 12, 3);

    adicionarVerticesExponencialmente(grafo3, 13, 4);
    adicionarVerticesExponencialmente(grafo3, 14, 4);
    adicionarVerticesExponencialmente(grafo3, 15, 4);
    adicionarVerticesExponencialmente(grafo3, 16, 4);

    adicionarVerticesExponencialmente(grafo3, 17, 5);
    adicionarVerticesExponencialmente(grafo3, 18, 5);
    adicionarVerticesExponencialmente(grafo3, 19, 5);
    adicionarVerticesExponencialmente(grafo3, 20, 5);

    adicionarVerticesExponencialmente(grafo3, 21, 6);
    adicionarVerticesExponencialmente(grafo3, 22, 6);
    adicionarVerticesExponencialmente(grafo3, 23, 6);
    adicionarVerticesExponencialmente(grafo3, 24, 6);

    adicionarVerticesExponencialmente(grafo3, 25, 7);
    adicionarVerticesExponencialmente(grafo3, 26, 7);
    adicionarVerticesExponencialmente(grafo3, 27, 7);
    adicionarVerticesExponencialmente(grafo3, 28, 7);

    adicionarVerticesExponencialmente(grafo3, 29, 8);
    adicionarVerticesExponencialmente(grafo3, 30, 8);
    adicionarVerticesExponencialmente(grafo3, 31, 8);
    adicionarVerticesExponencialmente(grafo3, 32, 8);
    defineSaida(grafo3);

    // Grafo AREA CENTRAL:
    Grafo *grafo4 = criarGrafo(9, 0);
    adicionarAresta(grafo4, 0, 1, 0);
    adicionarAresta(grafo4, 0, 2, 0);

    adicionarAresta(grafo4, 1, 3, 0);
    adicionarAresta(grafo4, 1, 4, 0);
    adicionarAresta(grafo4, 1, 5, 0);

    adicionarAresta(grafo4, 2, 6, 0);
    adicionarAresta(grafo4, 2, 7, 0);
    adicionarAresta(grafo4, 2, 8, 0);

    // Criação da Arvore Binaria
    ArvoreBinaria *arvore = criarArvore();

    inserir(arvore, *grafo4, 1);
    inserir(arvore, *grafo3, 0);
    inserir(arvore, *grafo2, 0);
    inserir(arvore, *grafo1, 0);

    return arvore;
}

int JogarArea(Jogador *jogador, Grafo *grafo)
{
    int sair = 0, sala_atual = 0, vidas = 1, sala_anterior = 0;
    int op, i, pontos = 0;
    char tecla;
    int limiteTentativas = 0; // Número de tentativas sem sucesso antes de fornecer uma dica
    double tempo;
    struct timeval inicio, fim;
    if (!grafo->direcionado)
        gettimeofday(&inicio, NULL);
    do
    {
        srand(time(NULL));
        system("cls");
        print_logo();
        printf(ANSI_COLOR_GREEN);
        printf("-------=================< R O O M - %d >=================-------\n", sala_atual);
        printf(ANSI_COLOR_RESET);
        NoListaAdjacencia *percorre = grafo->array[sala_atual].cabeca;
        i = 0;
        while (percorre)
        {
            printf("Room %d       ", percorre->destino);
            percorre = percorre->proximo;
            i++;
            if (i % 5 == 0)
            {
                printf("\n");
            }
        }
        if (i % 5 != 0)
        {
            printf("\n");
        }
        if (!grafo->direcionado)
        {
            printf(ANSI_COLOR_GREEN);
            printf("-------================< L I F E S - %d >================-------\n", vidas);
            printf(ANSI_COLOR_RESET);
        }
        else
        {
            printf(ANSI_COLOR_GREEN);
            printf("-------================<***************>================-------\n");
            printf(ANSI_COLOR_RESET);
        }
        printf("\nSelect a Room (-1 to EXIT):");
        printf(ANSI_COLOR_YELLOW);
        setbuf(stdin, NULL);
        scanf("%d", &op);
        printf(ANSI_COLOR_RESET);
        if (op == -1) // Sair
        {
            sair = 1;
            break;
        }
        else
        {
            if (sala_atual != op)
            {
                i = retornaSala(grafo, sala_atual, op);
                if (i == -1)
                    continue;
                if (op == sala_anterior && !grafo->direcionado)
                    vidas--;
                sala_anterior = sala_atual;
                sala_atual = op;
                if (!grafo->direcionado) // Area Central
                {
                    if (vidas < 0) // Ficou sem vidas na area central, perdeu
                    {
                        printf(ANSI_COLOR_RED);
                        printf("\nYou have reached a room with no exit and you have no more lifes,\nyou have lost!\n");
                        printf(ANSI_COLOR_GREEN);
                        printf("\nPress 'Esc' to EXIT...\n\n");
                        printf(ANSI_COLOR_RESET);
                        while (1)
                        {
                            if (_kbhit())
                            {
                                tecla = _getch();
                                if (tecla == 27)
                                { // Verifica se a tecla pressionada é o código ASCII do "Esc"
                                    sair = 1;
                                    gettimeofday(&fim, NULL);
                                    tempo = (double)(fim.tv_sec - inicio.tv_sec) + (double)(fim.tv_usec - inicio.tv_usec) / 1000000.0;
                                    if (tempo > jogador->tempoAreaCentral)
                                        jogador->tempoAreaCentral = tempo;
                                    if (pontos > jogador->pontos)
                                        jogador->pontos = pontos;
                                    return 2; // Perdeu na area central
                                }
                            }
                        }
                    }
                    vidas += grafo->array[sala_atual].peso;
                    pontos += grafo->array[sala_atual].peso;
                    grafo->array[sala_atual].peso = 0;
                    grafo->array[sala_anterior].peso = 0;
                    // Aumentar salas do vetice
                    i = rand() % 11;
                    if (i < 7)
                    {
                        if (grafo->array[sala_atual].cabeca->proximo == NULL)
                            adicionarVerticesExponencialmente(grafo, sala_atual, sala_anterior);
                    }
                }
                else // AREA NORMAL
                {
                    if (grafo->array[sala_atual].ehSaida) // Proxima fase
                    {
                        printf(ANSI_COLOR_GREEN);
                        printf("\nYou have reached a room with an exit, you have won\n");
                        printf("\nPress 'Enter' to CONTINUE...\n\n");
                        printf(ANSI_COLOR_RESET);
                        while (1)
                        {
                            if (_kbhit())
                            {
                                tecla = _getch();
                                if (tecla == 13)
                                {             // Verifica se a tecla pressionada é o código ASCII do "Enter"
                                    return 1; // Venceu na aerea normal
                                }
                            }
                        }
                    }
                    if (!grafo->array[sala_atual].ehSaida && grafo->array[sala_atual].cabeca == NULL) // A Sala é um Sumidouro
                    {
                        printf(ANSI_COLOR_RED);
                        printf("\nYou have reached a room with no exit, you have lost\n");
                        printf("Try again!\n");
                        printf(ANSI_COLOR_GREEN);
                        printf("\nPress 'Enter' to PLAY or 'Esc' to EXIT...\n\n");
                        printf(ANSI_COLOR_RESET);
                        while (1)
                        {
                            if (_kbhit())
                            {
                                tecla = _getch();
                                if (tecla == 13)
                                { // Verifica se a tecla pressionada é o código ASCII do "Enter"
                                    limiteTentativas++;
                                    if (limiteTentativas > 3)
                                    {
                                        printf(ANSI_COLOR_GREEN);
                                        printf("Need help? Press 'Enter' for a hint or 'Esc' to SKIP...\n\n");
                                        printf(ANSI_COLOR_RESET);
                                        while (1)
                                        {
                                            if (_kbhit())
                                            {
                                                tecla = _getch();
                                                if (tecla == 13)
                                                { // Verifica se a tecla pressionada é o código ASCII do "Enter"
                                                    fornecerDica(grafo, sala_atual);
                                                    break;
                                                }
                                                if (tecla == 27)
                                                { // Verifica se a tecla pressionada é o código ASCII do "Esc"
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    sala_atual = 0;
                                    break;
                                }
                                if (tecla == 27)
                                { // Verifica se a tecla pressionada é o código ASCII do "Esc"
                                    sair = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (!sair);
    if (!grafo->direcionado)
    {
        gettimeofday(&fim, NULL);
        tempo = (double)(fim.tv_sec - inicio.tv_sec) + (double)(fim.tv_usec - inicio.tv_usec) / 1000000.0;
        if (tempo > jogador->tempoAreaCentral)
            jogador->tempoAreaCentral = tempo;
        if (pontos > jogador->pontos)
            jogador->pontos = pontos;
    }
    return 0; // Desistiu
}

int retornaSala(Grafo *grafo, int sala_atual, int num)
{
    if (num >= 0 && sala_atual >= 0)
    {
        NoListaAdjacencia *percorre = grafo->array[sala_atual].cabeca;
        while (percorre)
        {
            if (percorre->destino == num)
            {
                return num; // Sala existe
            }
            percorre = percorre->proximo;
        }
    }
    return -1; // Sala não existe
}

// Função para fornecer uma dica ao jogador
void fornecerDica(Grafo *grafo, int sala_atual)
{
    int *predecessor = (int *)malloc(grafo->V * sizeof(int));
    int saida = -1;

    // Encontra uma sala de saída
    for (int i = 0; i < grafo->V; i++)
    {
        if (grafo->array[i].ehSaida == 1)
        {
            saida = i;
            break;
        }
    }

    if (saida != -1)
    {
        encontrarCaminhoMaisCurto(grafo, sala_atual, saida, predecessor);
        printf(ANSI_COLOR_GREEN);
        printf("Tip: ");
        printf(ANSI_COLOR_RESET);
        printf("The shortest path to the exit is: ");
        printf(ANSI_COLOR_GREEN);
        imprimirCaminho(predecessor, sala_atual, saida);
        printf(ANSI_COLOR_RESET);
        printf("\n\n");
        system("pause");
    }
    else
    {
        printf("Não há saída definida no grafo.\n");
    }

    free(predecessor);
}