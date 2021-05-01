#ifndef ArvoreAVL_h
#define ArvoreAVL_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/******************************************************************************/
/******************************************************************************/

// Tipos abstratos para Árvore AVL

typedef struct {
    int chave;
} Item;

typedef struct NoArvoreAVL *PtrArvoreAVL;

typedef struct NoArvoreAVL {
    Item elemento;
    PtrArvoreAVL direita;
    PtrArvoreAVL esquerda;
    int altura;
} NoArvoreAVL;

// Tipos abstratos para Fila Dinâmica (Usada na função de impressão em nível)
typedef struct NoFila *PtrNoFila;

typedef struct NoFila{
    PtrArvoreAVL no;
    PtrNoFila proximo;
} NoFila;

typedef struct {
    PtrNoFila inicio;
    PtrNoFila fim;
} Fila;

/******************************************************************************/
/******************************************************************************/

// Funções de manipulação para Árvore AVL
void iniciaArvoreAVL(PtrArvoreAVL *no);
bool estaVaziaArvoreAVL(PtrArvoreAVL *no);

void preOrdem(PtrArvoreAVL *no);
void posOrdem(PtrArvoreAVL *no);
void emOrdem(PtrArvoreAVL *no);

int alturaArvoreAVL(PtrArvoreAVL no);
int atualizaAlturaArvoreAVL(PtrArvoreAVL esquerda, PtrArvoreAVL direita);

bool pesquisaArvoreAVL(PtrArvoreAVL *no, int chave);
void destruirArvoreAVL(PtrArvoreAVL *no);

void aplicarRotacoes(PtrArvoreAVL *no);

void rotacaoSimplesEsquerda(PtrArvoreAVL *no);
void rotacaoSimplesDireita(PtrArvoreAVL *no);
void rotacaoDuplaEsquerda(PtrArvoreAVL *no);
void rotacaoDuplaDireita(PtrArvoreAVL *no);

bool inserirArvoreAVL(PtrArvoreAVL *no, Item x);

PtrArvoreAVL getMinAux(PtrArvoreAVL *no); // Usada na remoção
PtrArvoreAVL getMaxAux(PtrArvoreAVL *no); // Usada na remoção
bool removeItem(PtrArvoreAVL *no, int chave);

// Funções de manipulação para Fila Dinâmica (Usadas na função de impressão em nível)
void enfileira(PtrArvoreAVL *no, Fila *fila);
PtrArvoreAVL desenfileira(Fila *fila);

void impressaoEmNivel(PtrArvoreAVL *no);


/******************************************************************************/
/******************************************************************************/

#endif /* ArvoreAVL_h */