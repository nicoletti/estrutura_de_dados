#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Tipos abstratos para Árvore AVL
typedef struct {
    int chave;
} Item;

typedef struct NoArvoreAVL *PtrArvoreAVL;

typedef struct NoArvoreAVL {
    Item elemento;
    PtrArvoreAVL direita;
    PtrArvoreAVL esquerda;
    int altura;
} NoArvoreAVL;

// Tipos abstratos para Fila Dinâmica (Usada na função de impressão em nível)
typedef struct NoFila *PtrNoFila;

typedef struct NoFila{
    PtrArvoreAVL no;
    PtrNoFila proximo;
} NoFila;

typedef struct {
    PtrNoFila inicio;
    PtrNoFila fim;
    int tamanho;
} Fila;

// Funções de manipulação para Fila Dinâmica
void enfileira(PtrArvoreAVL *no, Fila *fila);
PtrArvoreAVL desenfileira(Fila *fila);

// Funções de manipulação para Árvore AVL
void iniciaArvoreAVL(PtrArvoreAVL *no);
int alturaArvoreAVL(PtrArvoreAVL no);
int atualizaAlturaArvoreAVL(PtrArvoreAVL esquerda, PtrArvoreAVL direita);
void destruirArvoreAVL(PtrArvoreAVL *no);
void aplicarRotacoes(PtrArvoreAVL *no);
void rotacaoSimplesEsquerda(PtrArvoreAVL *no);
void rotacaoSimplesDireita(PtrArvoreAVL *no);
void rotacaoDuplaEsquerda(PtrArvoreAVL *no);
void rotacaoDuplaDireita(PtrArvoreAVL *no);
bool inserirArvoreAVL(PtrArvoreAVL *no, Item x);
PtrArvoreAVL getMinAux(PtrArvoreAVL *no);
PtrArvoreAVL getMaxAux(PtrArvoreAVL *no);
bool removeItem(PtrArvoreAVL *no, int chave, char metodoRemocao);
void impressaoEmNivel(PtrArvoreAVL *no, FILE *arqSaida);

int main(int argc, char *argv[]){

    if (argc != 3) {
        printf("Erro: Faltam arquivos de entrada!\n");
        system("pause");
        exit(1);
    }

    FILE *arqEntrada, *arqSaida;
    char string[200], *subString, metodoRemocao;
    Item elemento;
    PtrArvoreAVL raiz;

    arqEntrada = fopen(argv[1], "r");
    arqSaida = fopen(argv[2], "w+");

    // Testando abertura do arquivo
    if (arqEntrada == NULL || arqSaida == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    // Verificando se o arquivo está vazio
    fseek(arqEntrada, 0, SEEK_END);
    if (ftell(arqEntrada)>0){
        rewind(arqEntrada);
    } else {
        fprintf(arqSaida, "Aquivo de entrada vazio!\n");
        printf("Erro: Arquivo de entrada vazio!\n");
        exit(1);
    }

    iniciaArvoreAVL(&raiz);

    // Indentificando os valores da primeira linha do arquivo e inserindo na árvore
    fgets(string, 199, arqEntrada);
    subString = strtok(string, ",");
    while (subString != NULL){
        elemento.chave = atoi(subString);
        inserirArvoreAVL(&raiz, elemento);
        subString = strtok(NULL, ",");
    }

    fgets(string, 199, arqEntrada);
    fscanf(arqEntrada, "%c", &metodoRemocao);

    // Métodos de remoção: 'e' utiliza a substitui pelo maior valor da sub-árvore esquerda,
    // 'd' substitui pelo menor valor da sub-árvore direita
    if(metodoRemocao != 'e' && metodoRemocao != 'd'){
        destruirArvoreAVL(&raiz);
        printf("Erro: Arquivo fora do padrao esperado!\n");
        fprintf(arqSaida, "Arquivo fora do padrão esperado!");
        exit(1);
    }

    // Impressão da árvore antes das remoções
    fprintf(arqSaida, "[*]antes\n");
    impressaoEmNivel(&raiz, arqSaida);
    fprintf(arqSaida, "\n");

    // Indentificando os valores da segunda linha e fazendo a remoção do nó correspondente na árvore
    subString = strtok(string, ",");
    while (subString != NULL){
        elemento.chave = atoi(subString);
        removeItem(&raiz, elemento.chave, metodoRemocao);
        subString = strtok(NULL, ",");
    }

    // Impressão da árvore depois das remoções
    fprintf(arqSaida, "[*]depois\n");
    impressaoEmNivel(&raiz, arqSaida);

    destruirArvoreAVL(&raiz);

    fclose(arqEntrada);
    fclose(arqSaida);

    printf("Arquivo criado com sucesso!\n");

    return 0;
}

void iniciaArvoreAVL(PtrArvoreAVL *no){
    (*no) = NULL;
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
            rotacaoSimplesEsquerda(&(*no));
        } else {
            rotacaoDuplaEsquerda(&(*no));
        }
    } else { // Se altEsq > altDir, rotação para direita

        PtrArvoreAVL temp = (*no)->esquerda;

        int tempAltEsq = alturaArvoreAVL((*temp).esquerda);
        int tempAltDir = alturaArvoreAVL((*temp).direita);

        if (tempAltEsq >= tempAltDir) {
            rotacaoSimplesDireita(&(*no));
        } else {
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

bool removeItem(PtrArvoreAVL *no, int chave, char metodoRemocao){
    if((*no) == NULL) {
        // Elemento nao existe na arvore
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
            if(metodoRemocao == 'e') {
                temp = getMaxAux(&(*no)->esquerda);
            } else if (metodoRemocao == 'd') {
                temp = getMinAux(&(*no)->direita);
            }
            (*no)->elemento.chave = temp->elemento.chave;
            free(temp);
        }
        return(true);
    }

    bool auxiliar;

    if((*no)->elemento.chave>chave) {
        auxiliar = removeItem(&(*no)->esquerda, chave, metodoRemocao);
    } else {
        auxiliar = removeItem(&(*no)->direita, chave, metodoRemocao);
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

// Funções de manipulação para Fila Dinâmica (Usadas na função de impressaoEmOrdem)
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
    fila->tamanho++;
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
        fila->tamanho--;
        return temp;
    } else {
        return temp;
    }
}

void impressaoEmNivel(PtrArvoreAVL *no, FILE *arqSaida) {
    Fila fila;
    PtrArvoreAVL percorre = (*no);
    int altEsq, altDir;
    //Inicializando fila
    fila.inicio = fila.fim = NULL;
    fila.tamanho = 0;

    enfileira(&percorre, &fila);
    while (1) {
        int nosCont = fila.tamanho; // nosCont recebe o número de nós do nível atual
        if (nosCont == 0) break;

        while(nosCont > 0){
            // 1. Desenfileira elemento e imprime seu chave
            // 2. Enfileira filhos da esquerda e direita
            percorre = desenfileira(&fila);
            altEsq = alturaArvoreAVL(percorre->esquerda);
            altDir = alturaArvoreAVL(percorre->direita);
            // Impressão da chave e o fator de balancamento do nó (fB = hd - he)
            fprintf(arqSaida, "%d (%d),", percorre->elemento.chave, (altDir - altEsq));

            if (percorre->esquerda != NULL) {
                enfileira(&percorre->esquerda, &fila);
            }
            if (percorre->direita != NULL) {
                enfileira(&percorre->direita, &fila);
            }
            nosCont--;
        }
        // Ao final de cada nível, será impresso um quebra-linha
        fprintf(arqSaida, "\n");
    }
    fila.fim = NULL;
}
