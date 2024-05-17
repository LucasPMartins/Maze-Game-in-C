#include "arvore.h"
#include "grafos.h"
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

void imprimelento(char *p, int N);

int main()
{
    char *menuOptions[] = {" J O G A R\n", " R A N K I N G\n", " S O B R E\n", " S A I R\n"};
    int numOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
    int selectedIndex = 0, sair = 0;
    char input;

    Jogador *jogadores = (Jogador *)malloc(sizeof(Jogador));
    Jogador *jogador = malloc(sizeof(Jogador));
    int numJogadores = 0;

    jogadores = lerRanking("ranking.txt", &numJogadores);

    int i;
    do
    {
        print_logo();
        printf("\nSelecione um OPCAO:\n\n");
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
                printf("Saindo do jogo");
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
    free(jogador);
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
            printf("-------==================< S O B R E >=================------\n\n");
            printf("(!) SOBRE:\n");
            printf(ANSI_COLOR_RESET);
            printf("O jogo eh um labirinto interativo onde o jogador deve navegar\n");
            printf("por diferentes areas, utilizando conceitos de Grafos, Arvores\n");
            printf("Binarias e Ordenacao. Projeto feito para um  trabalho de con-\n");
            printf("clusao de disciplina (Algoritmo e Estrutura de Dados 2).\n\n");
            printf("Criado por: Lucas Martins, Caue Grassi e Pedro Trevisan\n");
            printf(ANSI_COLOR_GREEN);
            printf("\n(?) COMO JOGAR:\n");
            printf("1 - Areas do Labirinto:");
            printf(ANSI_COLOR_RESET);
            printf(" O jogador interage diretamente esco-\n");
            printf("lhendo caminhos para sair do labirinto. Se escolher  um cami-\n");
            printf("nho sem saida, volta a sala inicial (derrota). Encontrar a \n");
            printf("saida leva a uma nova area (avanco de fase).\n");
            printf(ANSI_COLOR_GREEN);
            printf("2 - Area  Central: ");
            printf(ANSI_COLOR_RESET);
            printf("Sala especial com pontuacao para avancos.\n");
            printf("Permite ao jogador retroceder uma sala, sacrificando pontos.\n");
            printf("A derrota ocorre se encontrar uma sala sem saida e o jogador\n");
            printf("estiver sem pontos.\n");
            printf(ANSI_COLOR_GREEN);
            printf("3 - Dificuldade Progressiva: ");
            printf(ANSI_COLOR_RESET);
            printf("O numero de salas aumenta a ca-\n");
            printf("da fase, tornando o percurso mais dificil.\n");
            printf(ANSI_COLOR_GREEN);
            printf("4 - Mapa do Labirinto: ");
            printf(ANSI_COLOR_RESET);
            printf("Caminhos levam  a Area Central.O pro-\n");
            printf("gresso eh feito completando areas sucessivas. Todas as areas\n");
            printf("levam a Area Central.\n");
            printf(ANSI_COLOR_GREEN);
            printf("5 - Sistema de Ranking: ");
            printf(ANSI_COLOR_RESET);
            printf("Baseado no tempo e na pontuacao na\n");
            printf("Area Central. Armazena as ultimas 10 vitorias, classificando\n");
            printf("os jogadores tempo por area e pontuacao.\n\n");
            printf(ANSI_COLOR_GREEN);
            printf("Pressione a tecla 'ESC' para SAIR...");
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
    char *menuOptions[] = {" RANKING POR PONTUACAO\n", " RANKING POR TEMPO\n", " VOLTAR\n"};
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
        printf("\nSelecione um OPCAO:\n\n");
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
                    printf("-----=============< RANKING POR PONTUACAO >=============-----\n\n");
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
                    printf("-----===============< RANKING POR TEMPO >===============-----\n\n");
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
    char *menuOptions[] = {" L O G I N\n", " C A D A S T R A R\n", " V O L T A R\n"};
    int numOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
    int selectedIndex = 0, sair = 0;
    char input;

    char nome[50], senha[10];
    Jogador *jogador = malloc(sizeof(Jogador));

    int i;
    do
    {
        print_logo();
        printf(ANSI_COLOR_GREEN);
        printf("------==================< J O G A R >==================------\n");
        printf(ANSI_COLOR_RESET);
        printf("\nSelecione um OPCAO:\n\n");
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
                if (selectedIndex == 0) // JOGAR LOGIN
                {
                    print_logo();
                    printf(ANSI_COLOR_GREEN);
                    printf("-------=================< L O G I N >=================-------\n\n");
                    printf(ANSI_COLOR_RESET);
                    i = 3;
                    do
                    {
                        printf("\nDigite seu nome: ");
                        printf(ANSI_COLOR_YELLOW);
                        setbuf(stdin, NULL);
                        scanf("%s", &nome);
                        printf(ANSI_COLOR_RESET);
                        printf("\nDigite sua senha: ");
                        printf(ANSI_COLOR_YELLOW);
                        setbuf(stdin, NULL);
                        scanf("%s", &senha);
                        printf(ANSI_COLOR_RESET);
                        senha[strcspn(senha, "\n")] = '\0';
                        nome[strcspn(nome, "\n")] = '\0';
                        jogador = retornaJogador(jogadores, *numJogadores, nome, senha);
                        if (jogador == NULL) // Usuario não encontrado
                        {
                            printf(ANSI_COLOR_RED);
                            printf("\nNome de Usuario ou Senha Invalidos! Tentativas: %d\n", i - 1);
                            printf(ANSI_COLOR_RESET);
                            i--;
                        }
                        else // Usuario encontrado e senha correta
                        {
                            break;
                        }
                    } while (i > 0); // Encontrou o jogador
                    if (jogador != NULL)
                    {
                        printf(ANSI_COLOR_YELLOW);
                        printf("\nCARREGANDO");
                        i = 3;
                        while (i > 0)
                        {
                            imprimelento("...", 250);
                            printf("\b\b\b   \b\b\b");
                            i--;
                        }
                        printf(ANSI_COLOR_RESET);
                        iniciarJogo(jogador);
                    }
                    else
                    {
                        printf(ANSI_COLOR_RED);
                        printf("\nJogador nao encontrado!\n");
                        printf(ANSI_COLOR_RESET);
                    }
                }
                else if (selectedIndex == 1) // JOGAR CADASTRO
                {
                    print_logo();
                    printf(ANSI_COLOR_GREEN);
                    printf("-----================< C A D A S T R O >================-----\n\n");
                    printf(ANSI_COLOR_RESET);
                    i = 3;
                    do
                    {
                        printf("\nDigite seu nome: ");
                        printf(ANSI_COLOR_YELLOW);
                        setbuf(stdin, NULL);
                        scanf("%s", &nome);
                        printf(ANSI_COLOR_RESET);
                        nome[strcspn(nome, "\n")] = '\0';
                        jogador = retornaJogador(jogadores, *numJogadores, nome, NULL);
                        if (jogador != NULL) // Existe um jogador com esse nome
                        {
                            printf(ANSI_COLOR_RED);
                            printf("\nNome de Usuario em uso, tente usar outro! Tentativas: %d\n", i - 1);
                            printf(ANSI_COLOR_RESET);
                            i--;
                        }
                        else // Não existe um jogador com o nome digitado
                        {
                            printf("\nDigite sua senha: ");
                            printf(ANSI_COLOR_YELLOW);
                            setbuf(stdin, NULL);
                            scanf("%s", &senha);
                            printf(ANSI_COLOR_RESET);
                            senha[strcspn(senha, "\n")] = '\0';
                            // Aumentar o tamanho do vetor de jogadores
                        }
                    } while (i > 0);
                    jogador = adicionarJogador(jogadores, &numJogadores, nome, senha);
                    if (jogador != NULL) // Jogador criado com sucesso
                    {
                        printf(ANSI_COLOR_YELLOW);
                        printf("\nSALVANDO");
                        i = 3;
                        while (i > 0)
                        {
                            imprimelento("...", 250);
                            printf("\b\b\b   \b\b\b");
                            i--;
                        }
                        printf(ANSI_COLOR_RESET);
                        iniciarJogo(jogador);
                    }
                    else
                    {
                        printf(ANSI_COLOR_RED);
                        printf("\nErro na criacao de usuario!\n");
                        printf(ANSI_COLOR_RESET);
                    }
                }
            }
            break;
        default:
            break;
        }
    } while (sair != 1); // Loop até que a opção "Sair" seja selecionada
}

void iniciarJogo(Jogador *jogador)
{
}