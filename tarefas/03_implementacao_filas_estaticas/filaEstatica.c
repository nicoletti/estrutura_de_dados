#include "filaEstatica.h"

void iniciaFila(FilaEstatica *fila){
    fila->inicio=0;
    fila->fim=-1;
    fila->tamanho=0;
}

bool estaVazia(FilaEstatica *fila){
    return (fila->tamanho==0);
}

bool estaCheia(FilaEstatica *fila){
    return (fila->tamanho==MAXTAM);
}

int tamanhoFila(FilaEstatica *fila){
    return fila->tamanho;
}

int incrementaIndice(int i){
    i = (i + 1) % MAXTAM;
}

void enfileira(Objeto x, FilaEstatica *fila){
    if(!estaCheia(fila)){
        fila->fim = incrementaIndice(fila->fim);
        fila->array[fila->fim] = x;
        fila->tamanho++;
    } else {
        printf("Aviso: Fila cheia, nao foi possivel inserir o elemento.\n");
    }
}

void imprimeFila(FilaEstatica *fila){
    int N = fila->tamanho;

    printf("Fila: {");
    for(int i=0; i<N; i++){
        int indice = (fila->inicio + i) % MAXTAM;
        printf(" %d ", fila->array[indice]);
    }
    printf("}\n");
}


Objeto desenfileira(FilaEstatica *fila){
    Objeto aux;
    if(!estaVazia(fila)){
        aux = fila->array[fila->inicio];
        fila->inicio=incrementaIndice(fila->inicio);
        fila->tamanho--;
        return aux;
    } else {
        printf("Aviso: Fila vazia, nao foi possivel remover elemento.\n");
    }
}

Objeto inicioFila(FilaEstatica *fila){
    return fila->array[fila->inicio];
}

Objeto fimFila(FilaEstatica *fila){
    return fila->array[fila->fim];
}
