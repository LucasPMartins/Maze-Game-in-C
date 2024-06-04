#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó na lista de adjacência
typedef struct NoListaAdjacencia
{
    int destino;                       // Vértice ao qual este nó está conectado
    struct NoListaAdjacencia *proximo; // Próximo nó na lista de adjacência
} NoListaAdjacencia;

// Estrutura para representar uma lista de adjacência
typedef struct ListaAdjacencia
{
    int peso;
    int ehSaida;               // 1 para saída e 0 para padrão
    NoListaAdjacencia *cabeca; // Cabeça da lista de nós adjacentes
} ListaAdjacencia;

// Estrutura para representar um grafo. O grafo é um array de listas de adjacência.
// O tamanho do array será V (número de vértices no grafo)
typedef struct Grafo
{
    int V;                  // Número de vértices no grafo
    ListaAdjacencia *array; // Array de listas de adjacência
    int direcionado;        // Flag para indicar se o grafo é direcionado (1) ou não (0)
} Grafo;

NoListaAdjacencia *novoNoListaAdjacencia(int destino);
Grafo *criarGrafo(int V, int direcionado);
void adicionarAresta(Grafo *grafo, int origem, int destino, int peso);
void imprimirGrafo(Grafo *grafo);
void liberarGrafo(Grafo *grafo);
