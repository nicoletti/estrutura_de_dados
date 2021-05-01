//
// Created by Vitor on 26/04/2021.
//

#include "ArvoreAVL.h"

int main(){
    PtrArvoreAVL raiz;
    Item elemento;

    iniciaArvoreAVL(&raiz);

    printf("Inserindo o %d\n", elemento.chave = 5);
    inserirArvoreAVL(&raiz, elemento);
    printf("Inserindo o %d\n", elemento.chave = 40);
    inserirArvoreAVL(&raiz, elemento);
    printf("Inserindo o %d\n", elemento.chave = 35);
    inserirArvoreAVL(&raiz, elemento);
    // Apos inserir o 35, deverá ser realizada uma rotação dupla para esquerda no nó 5
    printf("Inserindo o %d\n", elemento.chave = 41);
    inserirArvoreAVL(&raiz, elemento);
    printf("Inserindo o %d\n", elemento.chave = 79);
    inserirArvoreAVL(&raiz, elemento);
    // Apos inserir o 79, deverá ser realizada uma rotação simples para esquerda no nó 40
    printf("Inserindo o %d\n", elemento.chave = 42);
    inserirArvoreAVL(&raiz, elemento);
    // Apos inserir o 42, deverá ser realizada uma rotação simples para esquerda no nó 35
    printf("Inserindo o %d\n", elemento.chave = 36);
    inserirArvoreAVL(&raiz, elemento);
    printf("Inserindo o %d\n", elemento.chave = 18);
    inserirArvoreAVL(&raiz, elemento);
    printf("Inserindo o %d\n", elemento.chave = 50);
    inserirArvoreAVL(&raiz, elemento);
    // Apos inserir o 50, deverá ser realizada uma rotação dupla para direita no nó 79
    printf("Inserindo o %d\n", elemento.chave = 12);
    inserirArvoreAVL(&raiz, elemento);

    removeItem(&raiz, 40);

    printf("Pre Ordem: ");
    preOrdem(&raiz);
    printf("\n");

    printf("Em Ordem: ");
    impressaoEmNivel(&raiz);
    printf("\n");

    printf("Removendo o 41\n");
    removeItem(&raiz, 41);

    printf("Em Ordem: ");
    impressaoEmNivel(&raiz);
    printf("\n");

    destruirArvoreAVL(&raiz);

    if (estaVaziaArvoreAVL(&raiz)) printf("A arvore foi destruida!\n");

    return 0;
}