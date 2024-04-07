#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

#include "grafos.h"

typedef struct NoArvore {
  TipoGrafo dado;
  struct NoArvore *esquerda;
  struct NoArvore *direita;
} NoArvore;

typedef struct {
  NoArvore *raiz;
  NoArvore *areaCentral;
} ArvoreBinaria;

ArvoreBinaria criarArvore();
void inserir(ArvoreBinaria *arvore, TipoGrafo dado, int ehAreaCentral);
void percorrerEmOrdem(ArvoreBinaria *arvore);
void liberarArvore(ArvoreBinaria *arvore);
void liberarArvoreAux(NoArvore *raiz);
NoArvore *criarNo(TipoGrafo dado);
void percorrerEmOrdemAux(NoArvore *no);

void percorrerPosOrdemAux(NoArvore *no);
void percorrerPosOrdem(ArvoreBinaria *arvore);
void jogarFase(TipoGrafo *grafo, Jogador *jogador);
void iniciarJogoComPosOrdem(ArvoreBinaria *arvore, Jogador *jogador);
#endif // ARVORE_H_INCLUDED