#include "filaDinamica.h"

void iniciaFila(FilaDinamica *fila){
    //Início e fim apontam para nulo.
    fila->inicio = NULL;
    fila->fim = NULL;
    //Contator recebe 0.
    fila->tamanho=0;
}

void imprimeFila(FilaDinamica *fila){
    PtrNoFila temp;

    printf("Fila: {");
    for (temp = fila->inicio; temp != NULL; temp = temp->proximo){
        printf(" %d ", temp->obj);
    }
    printf("}\n");
}

void enfileira(Objeto x, FilaDinamica *fila){
    PtrNoFila aux;
    aux = (PtrNoFila) malloc(sizeof(PtrNoFila));
    aux->obj = x;

    //Se for 1a inserção:
    if (estaVazia(fila)) {
        //Início e fim apontam para o auxiliar
        fila->inicio = fila->fim = aux;
        //Próximo do auxiliar aponta para nulo
        aux->proximo = NULL;

        //Se não for a 1a inserção:
    } else {
        //Próximo do auxiliar aponta para o próximo do fim
        aux->proximo = fila->fim->proximo;
        //Próximo do fim recebe auxilar (novo nó)
        fila->fim->proximo = aux;
        //Fim aponta para o auxiliar
        fila->fim = aux;
    }
    //Incrementa contador
    fila->tamanho++;
}

void desenfileira(FilaDinamica *fila, Objeto *x){
    if(!estaVazia(fila)){
        PtrNoFila apagar;
        *x = fila->inicio->obj;
        apagar = fila->inicio;
        fila->inicio = fila->inicio->proximo;
        free(apagar);
        fila->tamanho--;
    } else {
        printf("Aviso: Fila vazia, nao foi possivel remover elemento.\n");
    }
}

bool estaVazia(FilaDinamica *fila){
     return (fila->tamanho==0);
}

int tamanhoFila(FilaDinamica *fila){
    return fila->tamanho;
}

Objeto inicioFila(FilaDinamica *fila){
    return fila->inicio->obj;
}

Objeto fimFila(FilaDinamica *fila){
    return fila->fim->obj;
}

void destruirFila(FilaDinamica *fila){
    PtrNoFila apagar;
    PtrNoFila temp = fila->inicio;

    while(temp!=NULL){
        apagar = temp;
        temp = temp->proximo;
        free(apagar);
    }

    fila->inicio = fila->fim = NULL;
}
