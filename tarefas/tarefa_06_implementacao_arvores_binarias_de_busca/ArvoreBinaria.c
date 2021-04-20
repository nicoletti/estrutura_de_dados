#include "ArvoreBinaria.h"

int numeroNosArvore(PtrArvore *no){
    int contador = 1;

    if ((*no)->esquerda != NULL)
        contador += numeroNosArvore(&(*no)->esquerda);

    if ((*no)->direita != NULL)
        contador += numeroNosArvore(&(*no)->direita);

    return contador;
}

int alturaArvore(PtrArvore *no){
    if ((*no)==NULL){
        return -1;
    } else {
        int altEsquerda, altDireita;
        altEsquerda = alturaArvore(&(*no)->esquerda);
        altDireita = alturaArvore(&(*no)->direita);

    if(altEsquerda > altDireita)
        return altEsquerda + 1;
    else
        return altDireita + 1;
    }
}

void iniciaArvore(PtrArvore *no){
    *no = NULL;
}

void destroiArvore(PtrArvore *no){
    if((*no) != NULL){
        destroiArvore(&(*no)->esquerda);
        destroiArvore(&(*no)->direita);
        free(*no);
        (*no) = NULL;
    }
}

void preOrdem(PtrArvore *no){
    if((*no)==NULL) return;
    //1. Imprime o valor do nó corrente
    printf("%d ", (*no)->elemento.chave);
    //2. Chama recursivamente para o filho da esquerda
    preOrdem(&(*no)->esquerda);
    //3. Chama recursivamente para o filho da direita
    preOrdem(&(*no)->direita);
}

void posOrdem(PtrArvore *no){
    if((*no)==NULL) return;
    //1. Chama recursivamente para o filho da esquerda
    posOrdem(&(*no)->esquerda);
    //2. Chama recursivamente para o filho da direita
    posOrdem(&(*no)->direita);
    //3. Imprime o valor do nó corrente
    printf("%d ", (*no)->elemento.chave);
}

void EmOrdem(PtrArvore *no){
    if((*no)==NULL) return;
    //1. Chama recursivamente para o filho da esquerda
    EmOrdem(&(*no)->esquerda);
    //2. Imprime o valor do nó corrente
    printf("%d ", (*no)->elemento.chave);
    //3. Chama recursivamente para o filho da direita
    EmOrdem(&(*no)->direita);
}

bool insereItem(PtrArvore *raiz, Objeto x) {
    /*Criterio de parada 1: Se a raiz apontar para NULL (Ocorrerá quando a árvore estiver vazia, ou se for encontrando
    a folha de uma sub-árvore no processo recursivo.*/
    if (*raiz == NULL) {
        *raiz = malloc(sizeof(NoArvore));
        (*raiz)->direita = (*raiz)->esquerda = NULL;
        (*raiz)->elemento = x;
        return (true);
    }
    //Criterio de parada 2: Se o elemento x for igual ao elemento da raiz (Não ocorrerá inserção)
    if ((*raiz)->elemento.chave == x.chave) {
        return (false);
    }
    //Processo recursivo: Se o elemento x for menor que a raiz, será acessado o filho à esquerda
    if ((*raiz)->elemento.chave > x.chave) {
        return (insereItem(&(*raiz)->esquerda, x));

    //Processo recursivo: Se o elemento x for maior que o elemento da raiz, será acessado o filho à direita
    } else {
        if ((*raiz)->elemento.chave < x.chave) {
            return (insereItem(&(*raiz)->direita, x));
        }
    }
    return (false);
}

bool procuraItem(PtrArvore *no, int chave){
    if((*no)==NULL) return (false);
    if((*no)->elemento.chave == chave) return (true);

    if ((*no)->elemento.chave>chave){
        procuraItem(&(*no)->esquerda, chave);
    } else {
        procuraItem(&(*no)->direita, chave);
    }
}

bool estaVazia(PtrArvore *no){
    return (*no==NULL);
}

PtrArvore getMinAux(PtrArvore *no) {
    PtrArvore ret;

    //Critério de parada: Filho da esquerda do nó é igual a NULL
    if((*no)->esquerda==NULL) {
        ret = (*no);
        (*no) = (*no)->direita;
        return (ret);
    }

    return getMaxAux(&(*no)->esquerda);
}

PtrArvore getMaxAux(PtrArvore *no){
    PtrArvore ret;

    //Critério de parada: Filho da direita do nó é igual a NULL
    if((*no)->direita==NULL) {
        ret = (*no);
        (*no) = (*no)->esquerda;
        return (ret);
    }

    return getMaxAux(&(*no)->direita);
}

bool removeItem(PtrArvore *no, int chave){
    if((*no) == NULL) {
        printf("Elemento %d nao existe na arvore!\n", chave);
        return false;
    }
    if((*no)->elemento.chave == chave) {
        PtrArvore temp = (*no);

        //Caso 1: Somente a sub-arvore esquerda é nula
        if ((*no)->esquerda == NULL && (*no)->direita != NULL) {
            (*no) = (*no)->direita;
        }
            //Caso 2: Nó a ser removido é uma folha
        else if ((*no)->esquerda == NULL && (*no)->direita == NULL) {
            (*no) = NULL; //Poderia ser o mesmo código do primeiro caso
        }
            //Caso 3: Somente a sub-arvore direita é nula
        else if ((*no)->direita == NULL && (*no)->esquerda != NULL) {
            (*no) = (*no)->esquerda;
        }
            //Caso 4: Nenhuma sub-árvore é nula
        else {
            temp = getMaxAux(&(*no)->esquerda);
            (*no)->elemento.chave = temp->elemento.chave;
        }

        free(temp);
        return(true);
    }

    if((*no)->elemento.chave>chave) {
        return removeItem(&(*no)->esquerda, chave);
    } else {
        return removeItem(&(*no)->direita, chave);
    }
}

PtrArvore maximo(PtrArvore *no){

    if((*no)->direita == NULL) return (*no);

    return (maximo(&(*no)->direita));
}

PtrArvore maximoIterativo(PtrArvore *no){
    PtrArvore temp = (*no);

    while(temp->direita != NULL){
        temp = temp->direita;
    }

    return temp;
}

PtrArvore minimo(PtrArvore *no){
    if((*no)->esquerda == NULL) return (*no);

    return (minimo(&(*no)->esquerda));
}

PtrArvore minimoIterativo(PtrArvore *no){
    PtrArvore temp = (*no);

    while(temp->esquerda != NULL){
        temp = temp->esquerda;
    }

    return (temp);
}

