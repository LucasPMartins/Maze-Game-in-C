#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafo.h"

// Função para criar um novo nó na lista de adjacência
NoListaAdjacencia *novoNoListaAdjacencia(int destino)
{
    NoListaAdjacencia *novoNo = (NoListaAdjacencia *)malloc(sizeof(NoListaAdjacencia));
    novoNo->destino = destino;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para criar um grafo de V vértices
Grafo *criarGrafo(int V, int direcionado)
{
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->V = V;
    grafo->direcionado = direcionado;
    grafo->array = (ListaAdjacencia *)malloc(V * sizeof(ListaAdjacencia));

    // Inicializar cada lista de adjacência como vazia e definir ehSaida como 0
    for (int i = 0; i < V; ++i)
    {
        grafo->array[i].peso = 0;
        grafo->array[i].ehSaida = 0; // Define todas as salas inicialmente como não sendo saídas
        grafo->array[i].cabeca = NULL;
    }

    return grafo;
}

// Função para adicionar uma aresta no grafo
void adicionarAresta(Grafo *grafo, int origem, int destino, int peso)
{
    NoListaAdjacencia *novoNo = novoNoListaAdjacencia(destino);
    grafo->array[destino].peso = peso;
    novoNo->proximo = grafo->array[origem].cabeca;
    grafo->array[origem].cabeca = novoNo;

    if (!grafo->direcionado)
    {
        // Se o grafo não for direcionado, adicione a mesma aresta na direção contrária também
        novoNo = novoNoListaAdjacencia(origem);
        novoNo->proximo = grafo->array[destino].cabeca;
        grafo->array[destino].cabeca = novoNo;
    }
}

// Função para imprimir o grafo
void imprimirGrafo(Grafo *grafo)
{
    for (int v = 0; v < grafo->V; ++v)
    {
        NoListaAdjacencia *percorre = grafo->array[v].cabeca;
        printf("\n Lista de adjacencia do vertice %d (e saida: %d)\n cabeça ", v, grafo->array[v].ehSaida);
        while (percorre)
        {
            printf("-> %d", percorre->destino);
            percorre = percorre->proximo;
        }
        printf("\n");
    }
}

// Função para liberar a memória alocada para o grafo
void liberarGrafo(Grafo *grafo)
{
    for (int v = 0; v < grafo->V; ++v)
    {
        NoListaAdjacencia *percorre = grafo->array[v].cabeca;
        while (percorre)
        {
            NoListaAdjacencia *temp = percorre;
            percorre = percorre->proximo;
            free(temp);
        }
    }
    free(grafo->array);
    free(grafo);
}

// Função para adicionar vértices exponencialmente
void adicionarVerticesExponencialmente(Grafo *grafo, int sala_atual, int sala_anterior)
{
    srand(time(NULL));

    NoListaAdjacencia *percorre = grafo->array[sala_anterior].cabeca;
    int count = 0;
    while (percorre)
    {
        count++;
        percorre = percorre->proximo;
    }
    if (grafo->direcionado)
        count++;
    int novo_vertice = grafo->V; // Inicia a partir do próximo índice disponível

    // Realoca memória para o novo número total de vértices
    grafo->array = realloc(grafo->array, (novo_vertice + count) * sizeof(ListaAdjacencia));

    // Inicializa os novos vértices
    for (int i = 0; i < count; i++)
    {
        grafo->array[novo_vertice + i].cabeca = NULL;
        grafo->array[novo_vertice + i].peso = 0;
        grafo->array[novo_vertice + i].ehSaida = 0;
    }

    // Adiciona novas arestas
    for (int i = 0; i < count; i++)
    {
        adicionarAresta(grafo, sala_atual, novo_vertice, rand() % 5);
        novo_vertice++;
    }

    // Atualiza o número de vértices no grafo
    grafo->V = novo_vertice;
}

void defineSaida(Grafo *grafo)
{
    srand(time(NULL));

    int saida = 0;
    while (saida == 0)
    {
        saida = rand() % grafo->V;
    }

    // Define a sala sorteada como saída
    grafo->array[saida].ehSaida = 1;
}

// Função para encontrar o caminho mais curto (usando busca em largura, por exemplo)
void encontrarCaminhoMaisCurto(Grafo *grafo, int origem, int destino, int *predecessor)
{
    int *visitado = (int *)malloc(grafo->V * sizeof(int));
    int *distancia = (int *)malloc(grafo->V * sizeof(int));
    int *fila = (int *)malloc(grafo->V * sizeof(int));
    int frente = 0, traseira = 0;

    for (int i = 0; i < grafo->V; i++)
    {
        visitado[i] = 0;
        distancia[i] = -1;
        predecessor[i] = -1;
    }

    visitado[origem] = 1;
    distancia[origem] = 0;
    fila[traseira++] = origem;

    while (frente < traseira)
    {
        int atual = fila[frente++];
        NoListaAdjacencia *percorre = grafo->array[atual].cabeca;

        while (percorre)
        {
            int adj = percorre->destino;
            if (!visitado[adj])
            {
                visitado[adj] = 1;
                distancia[adj] = distancia[atual] + 1;
                predecessor[adj] = atual;
                fila[traseira++] = adj;
                if (adj == destino)
                {
                    free(visitado);
                    free(distancia);
                    free(fila);
                    return;
                }
            }
            percorre = percorre->proximo;
        }
    }

    free(visitado);
    free(distancia);
    free(fila);
}

// Função para imprimir o caminho da origem ao destino
void imprimirCaminho(int *predecessor, int origem, int destino)
{
    if (destino == -1)
    {
        // printf("No path exists\n");
        return;
    }

    if (destino == origem)
    {
        printf("%d", origem);
        return;
    }

    imprimirCaminho(predecessor, origem, predecessor[destino]);
    printf(" -> %d", destino);
}
