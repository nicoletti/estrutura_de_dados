#include "pilhaDinamica.h"

void iniciaPilha(PilhaDinamica *p){
    p->topo = NULL;
    p->tamanho = 0;
}

bool estaVazia(PilhaDinamica *p){
    if (p->tamanho==0) return true;
    else return false;
}

void empilha(Objeto obj, PilhaDinamica *p){
    PtrNoPilha Aux;
    Aux = (PtrNoPilha) malloc(sizeof(PtrNoPilha));
    Aux->obj = obj;
    Aux->proximo = p->topo;
    p->topo = Aux;
    p->tamanho++;
}

void desempilha(PilhaDinamica *p, Objeto *obj){
    if(estaVazia(p)==true) {
        printf("Atencao: Pilha vazia!\n");
    } else {
        PtrNoPilha Apagar;
        Apagar = p->topo;
        *obj = p->topo->obj;
        p->topo = Apagar->proximo;
        free(Apagar);
        p->tamanho--;
    }
}

int tamanhoPilha(PilhaDinamica *p){
    return p->tamanho;
}

void topo(PilhaDinamica *p, Objeto *obj){
    *obj = p->topo->obj;
}

void imprimePilha(PilhaDinamica *p){
    PtrNoPilha temp;

    printf("Pilha: {");
    for(temp = p->topo; temp != NULL; temp = temp->proximo){
        printf(" %d", temp->obj);
    }
    printf(" }\n");
}

void destruirPilha(PilhaDinamica *p){
    PtrNoPilha apagar;
    PtrNoPilha temp = p->topo;

    while(temp!=NULL){
        apagar=temp;
        temp=temp->proximo;
        free(apagar);
    }

    p->topo = NULL;
}