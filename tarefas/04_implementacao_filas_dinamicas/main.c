#include "filaDinamica.h"

int main(){
    FilaDinamica fd;
    Objeto obj;

    //Inicializar fila.
    iniciaFila(&fd);

    //Imprimir fila. Deverá exibir: Fila {}
    imprimeFila(&fd);

    //Verificar se a fila está vazia. Deverá retornar true.
    if (estaVazia(&fd)) printf("A Fila esta vazia.\n");
    else printf("A fila nao esta vazia.\n");

    //Tentar remover elemento da fila vazia. Deverá retornar aviso de que não foi possível.
    desenfileira(&fd, &obj);

    //Enfileirar 1, 2, 3 e 4;
    obj.chave = 1;
    enfileira(obj, &fd);
    obj.chave = 2;
    enfileira(obj, &fd);
    obj.chave = 3;
    enfileira(obj, &fd);
    obj.chave = 4;
    enfileira(obj, &fd);

    //Imprimir fila. Deverá exibir Fila { 1 2 3 4 }
    imprimeFila(&fd);

    //Verificar tamanho da fila. Deverá retornar 4.
    printf("Tamanho da fila: %d\n", tamanhoFila(&fd));

    //Desenfileirar um elemento do início (1).
    desenfileira(&fd, &obj);
    printf("Elemento removido da pilha: %d\n", obj.chave);

    //Imprimir fila. Deverá exibir: Fila { 2 3 4 }
    imprimeFila(&fd);

    //Verificar elemento do início da fila (2).
    printf("Elemento do inicio da fila: %d\n", inicioFila(&fd));

    //Verificar elemento do final da fila (4).
    printf("Elemento do final da fila: %d\n", fimFila(&fd));

    //Destruir fila e liberar memória
    destruirFila(&fd);

    // Imprimir fila. Deverá exibir novamente: Fila {}
    imprimeFila(&fd);

    return 0;
}