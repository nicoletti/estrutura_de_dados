#include "ListaOrdenada.h"

void iniciaLista(Lista *list){
    list->primeiro = NULL;
    list->tamanho = 0;
}

void inserir(Lista *list, Objeto x){
    PtrNoLista novo;
    novo = (PtrNoLista)malloc(sizeof(PtrNoLista));
    novo->elemento = x;

    //É a primeira inserção, ou o elemento a ser inserido é menor que o primeiro
    if((estaVazia(list)) || (x.chave < list->primeiro->elemento.chave)){
        novo->proximo = list->primeiro;
        list->primeiro = novo;
    } else {
        //Não é a 1a inserção e novo elemento é maior que o primeiro
        PtrNoLista percorre;
        percorre = list->primeiro;

        while ((percorre->proximo != NULL) && (x.chave > percorre->proximo->elemento.chave)){
                percorre = percorre->proximo;
        }
        novo->proximo = percorre->proximo;
        percorre->proximo = novo;
        }
    list->tamanho++;
}

void imprimirLista(Lista *list){
    printf("Lista: {");

    PtrNoLista percorre;
    for(percorre = list->primeiro; percorre != NULL; percorre = percorre->proximo){
        printf(" %d", percorre->elemento.chave);
    }

    printf(" }\n");
}


void destruirLista(Lista *list) {

    if (!estaVazia(list)) {
        PtrNoLista apagar;
        PtrNoLista aux = list->primeiro;

        while (aux != NULL) {
            apagar = aux;
            aux = aux->proximo;
            free(apagar);
        }
    } else {
        printf("Aviso: A lista ja esta vazia.\n");
    }

    list->primeiro = NULL;
    list->tamanho = 0;
}

bool estaVazia(Lista *list){
    return (list->tamanho == 0);
}


bool pesquisar(Lista *list, int key){

    if(estaVazia(list)) {
        return false;
    }

    PtrNoLista percorre=list->primeiro;

    while(percorre != NULL && key > percorre->elemento.chave) {
        percorre = percorre->proximo;
    }

    if((percorre == NULL) || percorre->elemento.chave > key) {
        return false;
    }

    return true;
}


int tamanhoLista(Lista *list){
    return (list->tamanho);
}

void removeElemento(Lista *list, int key, Objeto *item){

    if(estaVazia(list)) {
        printf("Aviso: A lista esta vazia.\n");
    }

    PtrNoLista percorre=list->primeiro;
    PtrNoLista apagar;

    while(percorre->proximo != NULL && key > percorre->proximo->elemento.chave) {
        percorre = percorre->proximo;
    }

    if((percorre->proximo == NULL) || percorre->proximo->elemento.chave > key) {
        printf("Aviso: Nao foi possivel remover o elemento %d, pois nao foi encontrado na lista.\n", key);
    } else {
        apagar = percorre->proximo;
        *item = percorre->proximo->elemento;
        percorre->proximo = percorre->proximo->proximo;
        free(apagar);
        printf("O elemento %d foi removido da lista.\n", item->chave);
        list->tamanho--;
    }

}


void removePrimeiro(Lista *list, Objeto *item){

    if (!estaVazia(list)) {
        PtrNoLista apagar;
        apagar = list->primeiro;
        *item = list->primeiro->elemento;
        list->primeiro = list->primeiro->proximo;
        free(apagar);
        list->tamanho--;
    } else {
        printf("Aviso: A lista esta vazia.\n");
    }
}

void removeUltimo(Lista *list, Objeto *item){
    PtrNoLista percorre = list->primeiro;
    PtrNoLista apagar;

    //Encontrar o penúltimo elemento
    while(percorre->proximo->proximo!=NULL){
        percorre = percorre->proximo;
    }

    //Apagar recebe o próximo do penúltimo elemento (último).
    apagar = percorre->proximo;
    *item = percorre->proximo->elemento;
    free(apagar);
    percorre->proximo = NULL;
    list->tamanho--;
}

Objeto primeiro(Lista *list){
    return list->primeiro->elemento;
}

Objeto ultimo(Lista *list){
    PtrNoLista percorre = list->primeiro;

    while(percorre->proximo!=NULL){
        percorre = percorre->proximo;
    }
    return percorre->elemento;
}