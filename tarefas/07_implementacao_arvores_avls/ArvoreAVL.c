#include "ArvoreAVL.h"

void iniciaArvoreAVL(PtrArvoreAVL *no){
    (*no) = NULL;
}

bool estaVaziaArvoreAVL(PtrArvoreAVL *no){
    return ((*no) == NULL);
}

void preOrdem(PtrArvoreAVL *no){
    if((*no) == NULL) return;
    // 1. Imprime nó corrente
    printf("%d ", (*no)->elemento.chave);
    // 2. Acessa sub-árvore esquerda
    preOrdem(&(*no)->esquerda);
    // 3. Acessa sub-árvore direita
    preOrdem(&(*no)->direita);
}

void posOrdem(PtrArvoreAVL *no){
    if((*no) == NULL) return;
    // 1. Acessa sub-árvore esquerda
    posOrdem(&(*no)->esquerda);
    // 2. Acessa sub-árvore direita
    posOrdem(&(*no)->direita);
    // 3. Imprime nó corrente
    printf("%d ", (*no)->elemento.chave);
}

void emOrdem(PtrArvoreAVL *no){
    if((*no) == NULL) return;
    // 1. Acessa sub-árvore esquerda
    emOrdem(&(*no)->esquerda);
    // 2. Imprime nó corrente
    printf("%d ", (*no)->elemento.chave);
    // 3. Acessa sub-árvore direita
    emOrdem(&(*no)->direita);
}

int alturaArvoreAVL(PtrArvoreAVL no){
    if((no) == NULL)
        return 0;
    else {
        return ((no)->altura);
    }
}

int atualizaAlturaArvoreAVL(PtrArvoreAVL esquerda, PtrArvoreAVL direita){
    int altEsq = alturaArvoreAVL(esquerda);
    int altDir = alturaArvoreAVL(direita);

    if (altEsq > altDir){
        return (altEsq + 1);
    } else {
        return (altDir + 1);
    }
}

bool pesquisaArvoreAVL(PtrArvoreAVL *no, int chave){
    if((*no)==NULL) return (false);
    if((*no)->elemento.chave == chave) return (true);

    if ((*no)->elemento.chave>chave){
        pesquisaArvoreAVL(&(*no)->esquerda, chave);
    } else {
        pesquisaArvoreAVL(&(*no)->direita, chave);
    }
}

void destruirArvoreAVL(PtrArvoreAVL *no){
    if((*no) != NULL){
        destruirArvoreAVL(&(*no)->esquerda);
        destruirArvoreAVL(&(*no)->direita);
        free(*no);
        (*no) = NULL;
    }
}

void aplicarRotacoes(PtrArvoreAVL *no){
    int altEsq = alturaArvoreAVL((*no)->esquerda);
    int altDir = alturaArvoreAVL((*no)->direita);

    // Se a sub-árvore direita for maior que a esquerda, a rotação é para esquerda
    if (altDir > altEsq){
        PtrArvoreAVL temp = (*no)->direita;

        int tempAltEsq = alturaArvoreAVL(temp->esquerda);
        int tempAltDir = alturaArvoreAVL(temp->direita);

        if (tempAltDir >= tempAltEsq) {
            printf("Rotacao simples para esquerda, com o no %d\n", (*no)->elemento.chave);
            rotacaoSimplesEsquerda(&(*no));
        } else {
            printf("Rotacao dupla para esquerda, com o no %d\n", (*no)->elemento.chave);
            rotacaoDuplaEsquerda(&(*no));
        }
    } else { // Se altEsq > altDir, rotação para direita

        PtrArvoreAVL temp = (*no)->esquerda;

        int tempAltEsq = alturaArvoreAVL((*temp).esquerda);
        int tempAltDir = alturaArvoreAVL((*temp).direita);

        if (tempAltEsq >= tempAltDir) {
            printf("Rotacao simples para direita, com o no %d\n", (*no)->elemento.chave);
            rotacaoSimplesDireita(&(*no));
        } else {
            printf("Rotacao dupla para direita, com o no %d\n", (*no)->elemento.chave);
            rotacaoDuplaDireita(&(*no));
        }
    }
}

void rotacaoSimplesEsquerda(PtrArvoreAVL *no){
    PtrArvoreAVL u;
    u = (*no)->direita;
    (*no)->direita = u->esquerda;
    u->esquerda = (*no);

    // Atualizando a altura dos nós modificados
    (*no)->altura = atualizaAlturaArvoreAVL((*no)->esquerda, (*no)->direita);
    u->altura = atualizaAlturaArvoreAVL(u->esquerda, u->direita);

    // Atualizando a refência do nó
    (*no) = u;
}

void rotacaoSimplesDireita(PtrArvoreAVL *no){
    PtrArvoreAVL u;

    u = (*no)->esquerda;
    (*no)->esquerda = u->direita;
    u->direita = (*no);

    // Atualizando a altura dos nós modificados
    (*no)->altura = atualizaAlturaArvoreAVL((*no)->esquerda, (*no)->direita);
    u->altura = atualizaAlturaArvoreAVL(u->esquerda, u->direita);

    // Atualizando a refência do nó
    (*no) = u;
}

void rotacaoDuplaEsquerda(PtrArvoreAVL *no){
    PtrArvoreAVL u, v;

    u = (*no)->direita;
    v = u->esquerda;
    (*no)->direita = v->esquerda;
    u->esquerda = v->direita;
    v->direita = u;
    v->esquerda = (*no);

    // Atualizando a altura dos nós modificados
    (*no)->altura = atualizaAlturaArvoreAVL((*no)->esquerda, (*no)->direita);
    u->altura = atualizaAlturaArvoreAVL(u->esquerda, u->direita);
    v->altura = atualizaAlturaArvoreAVL(v->esquerda, v->direita);

    // Atualizando a refência do nó
    (*no) = v;
}

void rotacaoDuplaDireita(PtrArvoreAVL *no){
    PtrArvoreAVL u, v;

    u = (*no)->esquerda;
    v = u->direita;
    (*no)->esquerda = v->direita;
    u->direita = v->esquerda;
    v->esquerda = u;
    v->direita = (*no);

    // Atualizando a altura dos nós modificados
    (*no)->altura = atualizaAlturaArvoreAVL((*no)->esquerda, (*no)->direita);
    u->altura = atualizaAlturaArvoreAVL(u->esquerda, u->direita);
    v->altura = atualizaAlturaArvoreAVL(v->esquerda, v->direita);

    // Atualizando a refência do nó
    (*no) = v;
}

bool inserirArvoreAVL(PtrArvoreAVL *no, Item x){
    // Criterio de parada 1: Se a raiz apontar para NULL (Ocorrerá quando a árvore estiver vazia, ou se for encontrando
    // a folha de uma sub-árvore no processo recursivo.
    if (*no == NULL) {
        *no = malloc(sizeof(NoArvoreAVL));
        (*no)->direita = (*no)->esquerda = NULL;
        (*no)->elemento = x;
        (*no)->altura = 1;
        return (true);
    }
    // Criterio de parada 2: Se o elemento x for igual ao elemento da raiz (Não ocorrerá inserção)
    if ((*no)->elemento.chave == x.chave) {
        return (false);
    }

    bool auxiliar;

    // Processo recursivo: Se o elemento x for menor que a raiz, será acessado o filho à esquerda
    if ((*no)->elemento.chave > x.chave) {
        auxiliar = inserirArvoreAVL(&(*no)->esquerda, x);

    // Processo recursivo: Se o elemento x for maior que o elemento da raiz, será acessado o filho à direita
    } else {
        auxiliar = (inserirArvoreAVL(&(*no)->direita, x));
    }

    // Se auxiliar for falso, não houve inserção na árvore
    if (!auxiliar) return (false);

    // Se houve inserção, checar o desbalanceamento
    int altEsq, altDir;

    // Calculanto altura das sub-arvores
    altEsq = alturaArvoreAVL((*no)->esquerda);
    altDir = alturaArvoreAVL((*no)->direita);

    // Verificando desbalanceamento
    if((altDir - altEsq) < -1 || (altDir - altEsq) > 1){
        aplicarRotacoes(&(*no));
    }

    // Atualizar altura do nó
    (*no)->altura = atualizaAlturaArvoreAVL((*no)->esquerda, (*no)->direita);

    return (true);
}

PtrArvoreAVL getMinAux(PtrArvoreAVL *no) {
    PtrArvoreAVL minAux;

    //Critério de parada: Filho da esquerda do nó é igual a NULL
    if((*no)->esquerda==NULL) {
        minAux = (*no);
        (*no) = (*no)->direita;
        return (minAux);
    }

    return getMaxAux(&(*no)->esquerda);
}

PtrArvoreAVL getMaxAux(PtrArvoreAVL *no){
    PtrArvoreAVL maxAux;

    //Critério de parada: Filho da direita do nó é igual a NULL
    if((*no)->direita==NULL) {
        maxAux = (*no);
        (*no) = (*no)->esquerda;
        return (maxAux);
    }

    return getMaxAux(&(*no)->direita);
}

bool removeItem(PtrArvoreAVL *no, int chave){
    if((*no) == NULL) {
        printf("Elemento %d nao existe na arvore!\n", chave);
        return false;
    }
    if((*no)->elemento.chave == chave) {
        PtrArvoreAVL temp = (*no);

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
            free(temp);
        }
        return(true);
    }

    bool auxiliar;

    if((*no)->elemento.chave>chave) {
        auxiliar = removeItem(&(*no)->esquerda, chave);
    } else {
        auxiliar = removeItem(&(*no)->direita, chave);
    }

    // Se auxiliar for falso, não houve remoção na árvore
    if (!auxiliar) return (false);

    // Se houve remoção, checar o desbalanceamento
    int altEsq, altDir;

    // Calculanto altura das sub-arvores
    altEsq = alturaArvoreAVL((*no)->esquerda);
    altDir = alturaArvoreAVL((*no)->direita);

    // Verificando desbalanceamento
    if((altDir - altEsq) < -1 || (altDir - altEsq) > 1){
        aplicarRotacoes(&(*no));
    }
    // Atualizar altura do nó
    (*no)->altura = atualizaAlturaArvoreAVL((*no)->esquerda, (*no)->direita);

    return (true);
}

// Funções de manipulação para Fila Dinâmica (Usadas na função de impressão em nível)
void enfileira(PtrArvoreAVL *no, Fila *fila){
    PtrNoFila aux;
    aux = (PtrNoFila) malloc(sizeof(NoFila));
    aux->no = (*no);

    if (fila->inicio == NULL) {
        fila->inicio = fila->fim = aux;
        aux->proximo = NULL;
    } else {
        aux->proximo = fila->fim->proximo;
        fila->fim->proximo = aux;
        fila->fim = aux;
    }
}

PtrArvoreAVL desenfileira(Fila *fila){
    PtrArvoreAVL temp;
    temp = fila->inicio->no;

    if(fila->inicio != NULL){
        temp = fila->inicio->no;
        PtrNoFila apagar;
        apagar = fila->inicio;
        fila->inicio = fila->inicio->proximo;
        free(apagar);
        return temp;
    } else {
        return temp;
    }
}

void impressaoEmNivel(PtrArvoreAVL *no) {
    Fila fila;
    Item x;
    PtrArvoreAVL percorre = (*no);
    fila.inicio = fila.fim = NULL;

    //printf("Enfileirando o %d\n", (*no)->elemento.chave);
    enfileira(&percorre, &fila);
    while (fila.inicio != NULL) {
        percorre = desenfileira(&fila);
        printf("%d ", percorre->elemento.chave);
        if (percorre->esquerda != NULL) {
            enfileira(&percorre->esquerda, &fila);
        }
        if (percorre->direita != NULL) {
            enfileira(&percorre->direita, &fila);
        }
    }
    fila.fim = NULL;
}
