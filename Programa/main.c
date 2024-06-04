#include "arvore.h"
#include "grafo.h"
#include "ranking.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
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

int retornaSala(Grafo *grafo, int sala_atual, int num);

void imprimelento(char *p, int N);

int main()
{
    char *menuOptions[] = {" P L A Y\n", " R A N K I N G\n", " A B O U T\n", " E X I T\n"};
    int numOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
    int selectedIndex = 0, sair = 0;
    char input;

    Jogador *jogadores = (Jogador *)malloc(sizeof(Jogador));
    int numJogadores = 0;

    jogadores = lerRanking("ranking.txt", &numJogadores);

    int i;
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
                i = 3;
                while (i > 0)
                {
                    imprimelento("...", 250);
                    printf("\b\b\b   \b\b\b");
                    i--;
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
                if (selectedIndex == 2) // SOBRE
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
    //  Liberar a memória alocada para o vetor de jogadores
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
    Jogador *jogador = malloc(sizeof(Jogador));
    int i;

    print_logo();
    printf(ANSI_COLOR_GREEN);
    printf("------===================< P L A Y >===================------\n");
    printf(ANSI_COLOR_RESET);
    printf("\nEnter your name: ");
    printf(ANSI_COLOR_YELLOW);
    setbuf(stdin, NULL);
    scanf("%s", &nome);
    printf(ANSI_COLOR_RESET);
    nome[strcspn(nome, "\n")] = '\0';
    jogador = retornaJogador(jogadores, *numJogadores, nome);
    if (jogador == NULL) // NOVO JOGADOR
    {
        jogador = adicionarJogador(jogadores, numJogadores, nome);
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
    system("cls");
    printf(ANSI_COLOR_GREEN);
    printf("-----===============< B E S T  S C O R E >===============-----\n");
    printf(ANSI_COLOR_RESET);
    printf("NAME:      TOTAL TIME:    CENTRAL AREA TIME:     SCORE:\n");
    printf("%s\t     %.2f\t\t   %.2f\t\t   %d\n", jogador->nome, jogador->tempoTotal, jogador->tempoAreaCentral, jogador->pontos);
    printf(ANSI_COLOR_GREEN);
    printf("------===============<******************>===============------\n");
    printf(ANSI_COLOR_RESET);
    int retorno = JogarArea(jogador, grafo);
    if (retorno)
    {
    }
}

int inicializaAreas(ArvoreBinaria *arvore)
{
    srand(time(NULL));
}

int JogarArea(Jogador *jogador, Grafo *grafo)
{
    int sair = 0, sala_atual = 0, vidas = 0, sala_anterior = 0;
    int op, i;
    char tecla;
    do
    {
        system("cls");
        printf(ANSI_COLOR_GREEN);
        printf("-------=================< R O O M - %d >=================-------\n", sala_atual + 1);
        printf(ANSI_COLOR_RESET);
        NoListaAdjacencia *percorre = grafo->array[sala_atual].cabeca;
        i = 0;
        while (percorre)
        {
            printf("     Room %d\t", percorre->destino);
            percorre = percorre->proximo;
            i++;
            if (i % 4 == 0)
            {
                printf("\n");
            }
        }
        if (i % 4 != 0)
        {
            printf("\n");
        }
        printf(ANSI_COLOR_GREEN);
        printf("------===============<******************>===============------\n");
        printf(ANSI_COLOR_RESET);
        printf(ANSI_COLOR_RESET);
        printf("Select a Room (-1 to EXIT):");
        setbuf(stdin, NULL);
        printf(ANSI_COLOR_YELLOW);
        scanf("%d", &op);
        printf(ANSI_COLOR_RESET);
        if (op == -1) // Sair
        {
            sair = 1;
        }
        else
        {
            if (sala_atual != op)
            {
                i = retornaSala(grafo, sala_atual, op);
                if (i == -1)
                    continue;
                sala_anterior = sala_atual;
                sala_atual = op;
                if (grafo->direcionado) // Area Central
                {
                    vidas += grafo->array[sala_atual].peso;
                    jogador->pontos += grafo->array[sala_atual].peso;
                    grafo->array[sala_atual].peso = 0;
                }
                else // AREA NORMAL
                {
                    if (grafo->array[sala_atual].ehSaida) // Proxima fase
                    {
                        return 1; // Venceu
                    }
                    if (!grafo->array[sala_atual].ehSaida && grafo->array[sala_atual].cabeca == NULL) // A Sala é um Sumidouro
                    {
                        printf(ANSI_COLOR_RED);
                        printf("\nYou have reached a room with no exit, you have lost\n");
                        printf("Try again!\n");
                        printf(ANSI_COLOR_GREEN);
                        printf("\nPress 'Enter' to PLAY or 'Esc' to BACK...\n\n");
                        printf(ANSI_COLOR_RESET);
                        while (1)
                        {
                            if (_kbhit())
                            {
                                tecla = _getch();
                                if (tecla == 13)
                                { // Verifica se a tecla pressionada é o código ASCII do "Enter"
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
    return 0; // Desistiu
}

int retornaSala(Grafo *grafo, int sala_atual, int num)
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
    return -1; // Sala não existe
}