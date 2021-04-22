#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int cod;
    char nome[30];
    char sexo;
    float peso;
    float altura;
} Cadastro;

typedef struct NoLista *PtrNoLista;

typedef struct NoLista {
    Cadastro paciente;
    PtrNoLista proximo;
    PtrNoLista anterior;
} NoLista;

typedef struct {
    PtrNoLista primeiro;
    int tamanho;
} Lista;

//Protótipos das funções
void iniciaLista(Lista *sistema);
bool estaVazia(Lista *sistema);
void inserir(Lista *sistema, Cadastro Novopaciente);
void imprimirListaCresc(Lista *sistema, FILE* arqSaida);
void imprimirListaDecresc(Lista *sistema, FILE* arqSaida);
void destruirLista(Lista *sistema);
void pesquisar(Lista *sistema, int codPesquisa, FILE* arqSaida);

int main(int argc, char *argv[]){

    if (argc != 3) {
	     printf("Erro!\n");
       system("pause");
       exit(1);
    }

    Lista sistema;
    Cadastro paciente;
    FILE *arqEntrada, *arqSaida;
    char c;
    int codPesquisa;

    arqEntrada = fopen(argv[1], "r");
    arqSaida = fopen(argv[2], "w+");

    // Testando abertura do arquivo
    if (arqEntrada == NULL || arqSaida == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    iniciaLista(&sistema);

    c = fgetc(arqEntrada);

    if (c == EOF) {
        fprintf(arqSaida, "Aquivo de entrada vazio!\n");
        exit(1);
    }

    while(c != EOF) {
        switch (c) {
            case '{':
                fscanf(arqEntrada, "%d,", &paciente.cod);
                fscanf(arqEntrada, "%[^,]s,", paciente.nome);
                fscanf(arqEntrada, ",%c,", &paciente.sexo);
                fscanf(arqEntrada, "%f,", &paciente.peso);
                fscanf(arqEntrada, "%f", &paciente.altura);
                inserir(&sistema, paciente);
                //Gambiarra para não considerar o "}" e quebra de linha
                c = fgetc(arqEntrada);
                c = fgetc(arqEntrada);
                break;
            case '1':
                imprimirListaCresc(&sistema, arqSaida);
                c = fgetc(arqEntrada);
                break;
            case '2':
                imprimirListaDecresc(&sistema, arqSaida);
                c = fgetc(arqEntrada);
                break;
            case '3':
                fscanf(arqEntrada, "%d", &codPesquisa);
                pesquisar(&sistema, codPesquisa, arqSaida);
                //Gambiarra para não considerar a quebra de linha
                c = fgetc(arqEntrada);
                break;
            default :
                fprintf(arqSaida, "Arquivo de entrada fora do padrao esperado!\n");
                exit(1);
                break;
        }
        c = fgetc(arqEntrada);
    }

    fclose(arqEntrada);
    fclose(arqSaida);

    destruirLista(&sistema);

    return 0;
}

void iniciaLista(Lista *sistema){
    sistema->primeiro = NULL;
    sistema->tamanho = 0;
}

bool estaVazia(Lista *list){
    return (list->tamanho == 0);
}

void inserir(Lista *sistema, Cadastro novoPaciente){
    PtrNoLista aux;
    aux = (PtrNoLista)malloc(sizeof(NoLista));
    aux->paciente = novoPaciente;

    //É a primeira inserção, ou o elemento a ser inserido é menor que o primeiro
    if((estaVazia(sistema)) || (novoPaciente.cod < (sistema->primeiro->paciente.cod))){
        aux->proximo = sistema->primeiro;

        //Ajuste de ponteiro para caso não a lista não esteja vazia, e a inserção será feita no início
        if(!estaVazia(sistema)){
            sistema->primeiro->anterior = aux;
        }
        aux->anterior = NULL;
        sistema->primeiro = aux;

    } else {
        //Não é a 1a inserção e novo elemento é maior que o primeiro
        PtrNoLista percorre;
        percorre = sistema->primeiro;

        while ((percorre->proximo != NULL) && (novoPaciente.cod > percorre->proximo->paciente.cod)){
            percorre = percorre->proximo;
        }
        aux->proximo = percorre->proximo;
        aux->anterior = percorre;

        //Ajuste de ponteiro caso a inserção não ocorra na última posição
        if(percorre->proximo != NULL) {
            percorre->proximo->anterior = aux;
        }
        percorre->proximo = aux;
    }
    sistema->tamanho++;
}

void imprimirListaCresc(Lista *sistema, FILE* arqSaida){

    PtrNoLista percorre;
    //Imprimindo cadastros até que seja encontrando o ponteiro para nulo (fim da lista).
    for(percorre = sistema->primeiro; percorre != NULL; percorre = percorre->proximo){
        fprintf(arqSaida, "{%d,", percorre->paciente.cod);
        fprintf(arqSaida, "%s,", percorre->paciente.nome);
        fprintf(arqSaida, "%c,", percorre->paciente.sexo);
        fprintf(arqSaida, "%.1f,", percorre->paciente.peso);
        fprintf(arqSaida, "%03.0f}\n", percorre->paciente.altura);
    }
}

void imprimirListaDecresc(Lista *sistema, FILE* arqSaida){
    PtrNoLista percorre = sistema->primeiro;

    //Percorrendo até o último cadastro
    while(percorre->proximo != NULL){
        percorre = percorre->proximo;
    }

    //Após chegar no último cadastro, será impresso de trás para frente utilizando o ponteiro "anterior"
    while (percorre != NULL){
        fprintf(arqSaida,"{%d,", percorre->paciente.cod);
        fprintf(arqSaida,"%s,", percorre->paciente.nome);
        fprintf(arqSaida,"%c,", percorre->paciente.sexo);
        fprintf(arqSaida,"%.1f,", percorre->paciente.peso);
        fprintf(arqSaida,"%03.0f}\n", percorre->paciente.altura);
        percorre = percorre->anterior;
    }
}

void destruirLista(Lista *sistema) {

    if (!estaVazia(sistema)) {
        PtrNoLista apagar;
        PtrNoLista aux = sistema->primeiro;

        while (aux != NULL) {
            apagar = aux;
            aux = aux->proximo;
            free(apagar);
        }
    } else {
        exit(1);
    }
    sistema->primeiro = NULL;
    sistema->tamanho = 0;
}

void pesquisar(Lista *sistema, int codPesquisa, FILE* arqSaida){

    if(estaVazia(sistema)) {
        fprintf(arqSaida, "Arquivo de entrada fora do padrao esperado\n");
        exit(1);
    }
    PtrNoLista percorre=sistema->primeiro;

    while(percorre != NULL && codPesquisa > percorre->paciente.cod) {
        percorre = percorre->proximo;
    }

    if((percorre == NULL) || percorre->paciente.cod > codPesquisa) {
        fprintf(arqSaida, "Código não existe/não foi encontrado!\n");
        exit(1);
    }
    fprintf(arqSaida, "{%d,", percorre->paciente.cod);
    fprintf(arqSaida, "%s,", percorre->paciente.nome);
    fprintf(arqSaida, "%c,", percorre->paciente.sexo);
    fprintf(arqSaida, "%.1f,", percorre->paciente.peso);
    fprintf(arqSaida, "%3.0f}", percorre->paciente.altura);
}
