#include "ListaOrdenada.h"

int main(){
    Lista list;
    Objeto x;

    iniciaLista(&list);

    x.chave = 500;
    inserir(&list, x);
    x.chave = 12;
    inserir(&list, x);
    x.chave = -2;
    inserir(&list, x);
    x.chave = 999;
    inserir(&list, x);
    x.chave = 3;
    inserir(&list, x);

    imprimirLista(&list);

    //Imprimir tamanho da lista
    printf("Tamanho da lista: %d\n", tamanhoLista(&list));

    //Verificar primeiro elemento da lista (-2)
    x = primeiro(&list);
    printf("Primeiro elemento: %d\n", x.chave);

    //Remover primeiro elemento da lista (-2)
    removePrimeiro(&list, &x);
    printf("Primeiro elemento da lista (%d) foi removido.\n", x.chave);

    //Verificar primeiro elemento da lista (3)
    x = primeiro(&list);
    printf("Primeiro elemento: %d\n", x.chave);

    //Imprimir tamanho da lista (4 elementos)
    printf("Tamanho da lista: %d\n", tamanhoLista(&list));

    //Verificar o último elemento da lista
    x = ultimo(&list);
    printf("Ultimo elemento: %d\n", x.chave);

    // Remover o último elemento da lista (999)
    removeUltimo(&list, &x);
    printf("Ultimo elemento da lista (%d) foi removido.\n", x.chave);

    //Verificar o último elemento da lista
    x = ultimo(&list);
    printf("Ultimo elemento: %d\n", x.chave);

    //Pesquisar o elemento 999 que já foi removido da lista.
    if(pesquisar(&list, 999))
        printf("O elemento 999 foi encontrado!\n");
    else
        printf("O elemento 999 nao foi encontrado!\n");

    //Pesquisar um elemento que existe na lista (12)
    if(pesquisar(&list, 12))
        printf("O elemento 12 foi encontrado!\n");
    else
        printf("O elemento 12 nao foi encontrado!\n");

    //Remover elemento especifico que não existe na lista.
    removeElemento(&list, 200, &x);

    //Remover elemento especifico (12) que existe na lista.
    removeElemento(&list, 12, &x);

    imprimirLista(&list);

    //Destruir lista e liberar memória
    printf("Destruindo lista...\n");
    destruirLista(&list);

    //Verificar se a lista está vazia
    if(estaVazia(&list)) printf("Lista destruida com sucesso.\n");
    else printf("Erro: A lista ainda possui elementos.\n");

    return 0;
}
