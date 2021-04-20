#include "ArvoreBinaria.h"

int main(){
    PtrArvore raiz, noTeste;
    Objeto obj;

    iniciaArvore(&raiz);

    obj.chave = 15;
    insereItem(&raiz, obj);
    obj.chave = 8;
    insereItem(&raiz, obj);
    obj.chave = 23;
    insereItem(&raiz, obj);
    obj.chave = 4;
    insereItem(&raiz, obj);
    obj.chave = 16;
    insereItem(&raiz, obj);
    obj.chave = 42;
    insereItem(&raiz, obj);

    // Representação da árvore:
    //          15
    //        /    \
    //       8     23
    //      /      / \
    //     4      16 42

    //Há elementos na árvore
    if (estaVazia(&raiz)) printf("A arvore esta vazia!\n");
    else printf("Ha elementos na arvore.\n");

    //Altura: 2
    printf("Altura da arvore: %d\n", alturaArvore(&raiz));
    //Número de nós: 6
    printf("Numero de nos na arvore: %d\n", numeroNosArvore(&raiz));

    //Em-Ordem: {4, 8, 15, 16, 23, 42}
    printf("Percurso Em-Ordem: { ");
    EmOrdem(&raiz);
    printf("}\n");

    //Pre-Ordem: {15, 8, 4, 23, 16, 42}
    printf("Percurso Pre-Ordem: { ");
    preOrdem(&raiz);
    printf("}\n");

    //Pos-Ordem: {4, 8, 16, 42, 23, 15}
    printf("Percurso Pos-Ordem: { ");
    posOrdem(&raiz);
    printf("}\n");

    //Elemento 16 existe na árvore
    printf("Procurando pelo elemento 16... ");
    if(procuraItem(&raiz, 16))
        printf("Foi encontrado!\n");
    else
        printf("Nao foi encontrado!\n");

    //Elemento 0 não existe na árvore
    printf("Procurando pelo elemento 0... ");
    if(procuraItem(&raiz, 0))
        printf("Foi encontrado!\n");
    else
        printf("Nao foi encontrado!\n");

    //Menor valor da árvore: 4
    noTeste = minimoIterativo(&raiz);
    printf("Minimo (Funcao iterativa): %d\n", noTeste->elemento.chave);

    noTeste = minimo(&raiz);
    printf("Minimo (Funcao recursiva): %d\n", noTeste->elemento.chave);

    //Maior valor da árvore: 42
    noTeste = maximoIterativo(&raiz);
    printf("Maximo (Funcao iterativa): %d\n", noTeste->elemento.chave);

    noTeste = maximo(&raiz);
    printf("Maximo (Funcao recursiva): %d\n", noTeste->elemento.chave);

    // -------------------------------------------------
    // Testes dos 4 casos da função de remoção
    // -------------------------------------------------

    //Caso 1: Nó a ser removido é uma folha
    printf("Removendo o 16... ");
    removeItem(&raiz, 16);
    printf("Pre-Ordem: { ");
    preOrdem(&raiz);
    printf("}\n");

    // Resultado:
    //          15
    //        /    \
    //       8     23
    //      /        \
    //     4         42
    //
    // Pre-Ordem: {15, 8, 4, 23, 42}

    //Caso 2: Somente a sub-arvore esquerda é nula
    printf("Removendo o 23... ");
    removeItem(&raiz, 23);
    printf("Pre-Ordem: { ");
    preOrdem(&raiz);
    printf("}\n");

    // Resultado:
    //          15
    //        /    \
    //       8     42
    //      /
    //     4
    //
    // Pre-Ordem: {15, 8, 4, 42}

    //Caso 3: Somente a sub-arvore direita é nula
    printf("Removendo o 08... ");
    removeItem(&raiz, 8);
    printf("Pre-Ordem: { ");
    preOrdem(&raiz);
    printf("}\n");

    // Resultado:
    //          15
    //        /    \
    //       4     42
    //
    // Pre-Ordem: {15, 4, 42}

    //Caso 4: Nenhuma sub-árvore é nula
    printf("Removendo o 15... ");
    removeItem(&raiz, 15);
    printf("Pre-Ordem: { ");
    preOrdem(&raiz);
    printf("}\n");

    // Resultado:
    //          4
    //           \
    //            42
    //
    // Pre-Ordem: {4, 42}

    // -------------------------------------------------
    // -------------------------------------------------

    printf("Destruindo a arvore...\n");
    destroiArvore(&raiz);

    //Árvore vazia, pois foi destruída
    if (estaVazia(&raiz)) printf("A arvore esta vazia!\n");
    else printf("Ha elementos na arvore.\n");


    return 0;
}
