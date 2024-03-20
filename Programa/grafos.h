#define MAXNUMVERTICES 100
#define MAXNUMARESTAS 4500

typedef int TipoValorVertice;
typedef int TipoPeso;

typedef struct TipoItem {
    TipoValorVertice vertice;
    TipoPeso peso;
} TipoItem;

struct TipoCelula {
    TipoItem item;
    struct TipoCelula *prox;
};

typedef struct TipoCelula *TipoApontador;

typedef struct TipoLista {
    TipoApontador primeiro, ultimo;
} TipoLista;

typedef struct TipoGrafo {
    TipoLista adj[MAXNUMVERTICES];
    int numVertices;
    int numArestas;
} TipoGrafo;

void FGVazio(TipoGrafo *grafo);
void InsereAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoPeso *peso, TipoGrafo *grafo);
int ExisteAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoGrafo *grafo);
void RetiraAresta(TipoValorVertice *v1, TipoValorVertice *v2, TipoPeso *peso, TipoGrafo *grafo);
void ImprimeGrafo(TipoGrafo *grafo);
void LiberaGrafo(TipoGrafo *grafo);