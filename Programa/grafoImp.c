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

    // Inicializa a semente para geração de números aleatórios
    srand(time(NULL));

    // Gera um índice de vértice para ser a saída
    int saida = rand() % V;

    // Inicializar cada lista de adjacência como vazia e definir ehSaida como 0
    for (int i = 0; i < V; ++i)
    {
        grafo->array[i].ehSaida = 0; // Define todas as salas inicialmente como não sendo saídas
        if (i == saida)
        {
            grafo->array[i].ehSaida = 1; // Define a sala sorteada como saída
        }
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
