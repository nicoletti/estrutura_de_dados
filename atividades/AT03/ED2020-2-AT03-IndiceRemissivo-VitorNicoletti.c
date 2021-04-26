// Ativida 03 - Manipulação de Árvores Binárias de Busca
// Objetivo: Criar um Índice Remissivo à partir dos arquivos de entrada

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Tipos abstratos de lista ordenada (P/ Armazenar números das páginas onde os termos foram encontrados)
typedef struct NoLista *PtrNoLista;

typedef struct NoLista {
    int numPag;
    PtrNoLista proximo;
} NoLista;

typedef struct {
    PtrNoLista primeiro;
    PtrNoLista ultimo;
} Lista;

//Tipos abstratos de Arvore Binaria de Busca (P/ armazenar os termos a serem pesquisados no livro)
typedef struct NoArvore* PtrArvore;

typedef struct NoArvore {
    char palavra[40];
    Lista paginas;
    PtrArvore esquerda;
    PtrArvore direita;
} NoArvore;

// Protótipos das funções de listas ordenadas
void insereLista(Lista *lista, int x);
void destruirLista(Lista *lista);

// Protótipos das funções de Arvore Binaria de Busca
void iniciaArvore(PtrArvore *no);
void destroiArvore(PtrArvore *no);
void impressaoEmOrdem(PtrArvore *no, FILE *arqSaida);
bool insereArvore(PtrArvore *no, char palavra[]);
bool procuraPalavra(PtrArvore *no, char palavra[], int numPag);

int main(int argc, char *argv[]){

    if (argc != 3) {
        printf("Erro: Faltam arquivos de entrada!\n");
        system("pause");
        exit(1);
    }

    PtrArvore raiz;
    FILE *arqEntrada, *arqSaida;
    char linha[200], *palavra;
    char delimit[15] = {">.,;: '\n'()"}; // Estes delimitadores serão usados para dividir as strings em sub-strings
    int numPag; //Armazenar o número da página corrente da varredura

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

    iniciaArvore(&raiz);

    // Lendo a 1a linha do arquivo, e caso ela iniciar com "<termos", as palavras a seguir serão inseridas na árvore.
    // Caso contrário, o programa será finalizado por estar fora do padrão
    fgets(linha, 199, arqEntrada);
    palavra = strtok(linha, delimit);
    if (strcmp(palavra, "<termos") == 0) {
        palavra = strtok(NULL, delimit);
        while (palavra != NULL) {
            insereArvore(&raiz, palavra);
            palavra = strtok(NULL, delimit);
        }
    } else {
        printf("Erro: Arquivo fora do padrao esperado!\n");
        fprintf(arqSaida, "Arquivo fora do padrão esperado!\n");
        exit(1);
    }

    // Lendo a 2a linha do arquivo, e caso ela iniciar com "<page", a variável numPag irá receber este valor para
    // o programa posteriormente utilizar este valor para criar o índice remissivo.
    // OBS: Deixei este código duplicado fora do while que aparece logo abaixo, para recusar arquivos que não passem
    // uma página como tag antes de percorrer pelo livro
    fgets(linha, 199, arqEntrada);
    palavra = strtok(linha, delimit);
    if (strcmp(palavra, "<page") == 0) {
        palavra = strtok(NULL, delimit);
        numPag = atoi(palavra);
    } else {
        printf("Erro: Arquivo fora do padrao esperado!\n");
        fprintf(arqSaida, "Arquivo fora do padrão esperado!\n");
        destroiArvore(&raiz);
        exit(1);
    }

    // Processando cada palavra do arquivo e verificando se há algum termo correspondente na árvore, se houver
    // a função 'procuraPalavra' adiciona o número da página atual na 'Lista Paginas' dentro do nó onde está o termo.
    while(fgets(linha, 199, arqEntrada) != NULL ) {
        if (linha[0] != '\n'){
            palavra = strtok(linha, delimit);
            if (strcmp(palavra, "<page") == 0) {
                palavra = strtok(NULL, delimit);
                numPag = atoi(palavra);
            }
            while (palavra != NULL) {
                procuraPalavra(&raiz, palavra, numPag);
                palavra = strtok(NULL, delimit);
            }
        } else {
            continue;
        }
    }

    // Imprimindo no arquivo os termos de busca, seguidos dos números das páginas onde foram encontrados
    impressaoEmOrdem(&raiz, arqSaida);
    printf("Indice remissivo criado com sucesso!\n");

    // Liberando memória da árvore binária.
    // OBS: Na destruição de cada nó, há também a liberação de memória da 'Lista Paginas' que cada um possui
    destroiArvore(&raiz);

    fclose(arqEntrada);
    fclose(arqSaida);

    return 0;
}

void insereLista(Lista *lista, int x) {
    PtrNoLista novo;
    novo = (PtrNoLista) malloc(sizeof(PtrNoLista));
    novo->numPag = x;

    // É a primeira inserção, ou o elemento a ser inserido é menor que o primeiro
    if (lista->primeiro == NULL || (x < lista->primeiro->numPag)) {
        novo->proximo = lista->primeiro;
        lista->primeiro = novo;
        lista->ultimo = novo;
    } else if (lista->ultimo->numPag == x) {
        return;
    } else {
        // Não é a 1a inserção e novo elemento é maior que o primeiro
        PtrNoLista percorre;
        percorre = lista->primeiro;

        while ((percorre->proximo != NULL) && (x > percorre->proximo->numPag)){
            percorre = percorre->proximo;
        }
        if (percorre->proximo == NULL){
            lista->ultimo = novo;
        }
        novo->proximo = percorre->proximo;
        percorre->proximo = novo;
    }
}

void destruirLista(Lista *lista) {
    if (lista->primeiro != NULL) {
        PtrNoLista apagar;
        PtrNoLista aux = lista->primeiro;

        while (aux != NULL) {
            apagar = aux;
            aux = aux->proximo;
            free(apagar);
        }
    } else {
        return;
    }

    lista->primeiro = lista->ultimo = NULL;
}

void iniciaArvore(PtrArvore *no){
    *no = NULL;
}

void destroiArvore(PtrArvore *no){

    if((*no) != NULL){
        destroiArvore(&(*no)->esquerda);
        destroiArvore(&(*no)->direita);
        destruirLista(&(*no)->paginas);
        free(*no);
        (*no) = NULL;
    }
}

void impressaoEmOrdem(PtrArvore *no, FILE *arqSaida){
    if((*no)==NULL) return;
    // 1. Chama recursivamente para o filho da esquerda
    impressaoEmOrdem(&(*no)->esquerda, arqSaida);
    // 2. Imprime a palavra do nó corrente. E percorre a 'Lista Paginas' imprimindo o número de cada pág. onde o termo
    // foi encontrado
    fprintf(arqSaida, "%s", (*no)->palavra);
    PtrNoLista percorre;
    for(percorre = (*no)->paginas.primeiro; percorre != NULL; percorre = percorre->proximo){
        fprintf(arqSaida, ",%d", percorre->numPag);
    }
    fprintf(arqSaida, "\n");
    // 3. Chama recursivamente para o filho da direita
    impressaoEmOrdem(&(*no)->direita, arqSaida);
}

bool insereArvore(PtrArvore *raiz, char palavra[]) {
    // Criterio de parada 1: Se a raiz apontar para NULL (Ocorrerá quando a árvore estiver vazia, ou se for encontrando
    // a folha de uma sub-árvore no processo recursivo.
    if (*raiz == NULL) {
        *raiz = malloc(sizeof(NoArvore));
        (*raiz)->direita = (*raiz)->esquerda = NULL;
        strcpy((*raiz)->palavra, palavra);
        (*raiz)->paginas.primeiro = (*raiz)->paginas.ultimo = NULL;
        return (true);
    }
    // Criterio de parada 2: Se o elemento x for igual ao elemento da raiz (Não ocorrerá inserção)
    if (strcasecmp((*raiz)->palavra, palavra) == 0) {
        return (false);
    }
    // Processo recursivo: Se o elemento x for menor que a raiz, será acessado o filho à esquerda
    if (strcasecmp((*raiz)->palavra, palavra) > 0) {
        return (insereArvore(&(*raiz)->esquerda, palavra));

    // Processo recursivo: Se o elemento x for maior que o elemento da raiz, será acessado o filho à direita
    } else {
            return (insereArvore(&(*raiz)->direita, palavra));
        }
}

bool procuraPalavra(PtrArvore *no, char palavra[], int numPag){
    if((*no) == NULL) return (false);
    if(strcasecmp((*no)->palavra, palavra) == 0) {
        // Se o termo for encontrado na página atual, a função insere o número correspondente na 'Lista Paginas' do nó
        insereLista(&(*no)->paginas, numPag);
        return (true);
    }

    if (strcasecmp((*no)->palavra, palavra) > 0){
        procuraPalavra(&(*no)->esquerda, palavra, numPag);
    } else {
        procuraPalavra(&(*no)->direita, palavra, numPag);
    }

    return(false);
}
