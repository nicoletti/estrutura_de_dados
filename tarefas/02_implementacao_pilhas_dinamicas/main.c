#include "pilhaDinamica.h"

int main (){
    PilhaDinamica p;
    Objeto obj;

    //Inicializar pilha
    iniciaPilha(&p);

    //Verificar se a pilha está vazia. Deverá retornar true.
    if (estaVazia(&p)==true) printf("Pilha esta vazia.\n");
    else printf("Pilha nao esta vazia.\n");

    //Imprimir a pilha. Deverá exibir a pilha vazia.
    imprimePilha(&p);

    //Empilhar número 5, 10 e 15.
    obj.chave = 5;
    empilha(obj, &p);
    obj.chave = 10;
    empilha(obj, &p);
    obj.chave = 15;
    empilha(obj, &p);

    //Imprimir a pilha. Deverá exibir 5, 10 e 15.
    imprimePilha(&p);

    //Verificar tamanho da pilha. Deverá retornar 3.
    printf("A pilha possui %d elementos.\n", tamanhoPilha(&p));

    //Desempilhar o elemento do topo (15).
    desempilha(&p, &obj);

    //Imprimir a pilha. Deverá exibir 5 e 10.
    imprimePilha(&p);

    //Verificar elemento do topo. Deverá retornar 10.
    topo(&p, &obj);
    printf("Elemento do topo: %d\n", obj.chave);

    //Verificar tamanho da pilha. Deverá retornar 2.
    printf("A pilha possui %d elementos.\n", tamanhoPilha(&p));

    //Destruir pilha e liberar memória.
    destruirPilha(&p);

    //Imprimir a pilha. Deverá exibir a pilha vazia novamente.
    imprimePilha(&p);

    return 0;
}