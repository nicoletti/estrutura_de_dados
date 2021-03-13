#include "pilhaEstatica.h"

void iniciaPilha(pilhaEstatica *pilha) {
  pilha->topo = 0;
}

bool estaVazia(pilhaEstatica *pilha) {
  return (pilha->topo==0);
}

bool estaCheia(pilhaEstatica *pilha) {
  return (pilha->topo==MAXTAM);
}

void empilha(Objeto item, pilhaEstatica *pilha) {
  if (estaCheia(pilha))
  printf("Atencao: Nao foi possivel inserir o elemento, pois a pilha esta cheia.\n");

  else
  pilha->array[pilha->topo]=item;
  pilha->topo++;
}

void desempilha(Objeto *item, pilhaEstatica *pilha) {
  if (estaVazia(pilha))
  printf("Atencao: Nao foi possivel remover elemento, pois a pilha esta vazia.\n");

  else
  item->chave = pilha->topo;
  pilha->topo--;
}

int tamanhoPilha(pilhaEstatica *pilha) {
  return pilha->topo;
}

Objeto topo(pilhaEstatica *pilha) {
  return pilha->array[pilha->topo-1];
}

void imprimePilha(pilhaEstatica *pilha) {
  if (estaVazia(pilha))
  printf("Pilha vazia.\n");
  else
    printf("Pilha: { ");
    for(int i=0; i<pilha->topo; i++){
      printf("|%d| ", pilha->array[i]);
    }
    printf("}\n");
}
