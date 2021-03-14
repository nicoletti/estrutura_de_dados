#include "filaEstatica.h"

int main() {
    FilaEstatica f;
    Objeto obj;

    //Inicializar fila.
    iniciaFila(&f);

    //Verificar se a fila está vazia. Deverá retornar true.
    if (estaVazia(&f)) printf("A fila esta vazia.\n");
    else printf("A fila nao esta vazia.\n");

    //Verificar se a fila está cheia. Deverá retornar false.
    if (estaCheia(&f))  printf("A fila esta cheia.\n");
    else printf("A fila nao esta cheia.\n");

    //Imprimir a fila. Deverá imprimir a fila sem nenhum elemento.
    imprimeFila(&f);

    //Enfileirar os elementos 5, 10 e 15;
    obj.chave=5;
    enfileira(obj, &f);
    obj.chave=10;
    enfileira(obj, &f);
    obj.chave=15;
    enfileira(obj, &f);

    //Imprimir a fila. Deverá imprimir { 5 10 15 }
    imprimeFila(&f);

    //Remover o elemento do início (5) e armazenar na váriavel obj para impressão.
    printf("Elemento removido: %d\n", obj = desenfileira(&f));

    //Imprimir a fila. Deverá imprimir { 10 15 }
    imprimeFila(&f);

    //Inserir os elementos 20, 25 e 30. A fila ficará cheia.;
    obj.chave=20;
    enfileira(obj, &f);
    obj.chave=25;
    enfileira(obj, &f);
    obj.chave=30;
    enfileira(obj, &f);

    //Imprimir a fila. Deverá imprimir { 10 15 20 25 30 }
    imprimeFila(&f);

    //Tentar enfileirar mais um elemento. Deverá ser exibido um aviso de que a fila está cheia.
    obj.chave=35;
    enfileira(obj, &f);

    //Remover o elemento do início (10) e inserir um novo elemento.
    obj = desenfileira(&f);
    printf("Elemento removido: %d\n", obj.chave);
    obj.chave=35;
    enfileira(obj, &f);

    //Imprimir a fila. Deverá imprimir { 15 20 25 30 35 }
    imprimeFila(&f);

    //Verificar elemento do início da fila. Deverá retornar 15.
    printf("Elemento do inicio da fila: %d\n", obj=inicioFila(&f));

    //Verificar elemento do final da fila. Deverá retornar 35.
    printf("Elemento do final da fila: %d\n", obj=fimFila(&f));

    //Verificar tamanho da fila
    printf("Ha %d elementos na fila.\n", tamanhoFila(&f));

    //Verificar se a fila está cheia. Deverá retornar true.
    if (estaCheia(&f))  printf("A fila esta cheia.\n");
    else printf("A fila nao esta cheia.\n");

    return 0;
}
