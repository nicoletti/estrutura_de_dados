//  ArvoreBinaria.h

#ifndef ArvoreBinaria_h
#define ArvoreBinaria_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int chave;
} Objeto;

typedef struct NoArvore* PtrArvore;

typedef struct NoArvore {
    Objeto elemento;
    PtrArvore esquerda;
    PtrArvore direita;
} NoArvore;

int numeroNosArvore(PtrArvore *no);
int alturaArvore(PtrArvore *no);
void iniciaArvore(PtrArvore *no);
void destroiArvore(PtrArvore *no);
void preOrdem(PtrArvore *no);
void posOrdem(PtrArvore *no);
void EmOrdem(PtrArvore *no);
bool insereItem(PtrArvore *no, Objeto x);
bool procuraItem(PtrArvore *no, int chave);
bool estaVazia(PtrArvore *no);
PtrArvore getMinAux(PtrArvore *no); //usado na remoção
PtrArvore getMaxAux(PtrArvore *no); //usado na remoção
bool removeItem(PtrArvore *no, int chave);
PtrArvore maximo(PtrArvore *no);
PtrArvore maximoIterativo(PtrArvore *no);
PtrArvore minimo(PtrArvore *no);
PtrArvore minimoIterativo(PtrArvore *no);


#endif /* ArvoreBinaria_h */