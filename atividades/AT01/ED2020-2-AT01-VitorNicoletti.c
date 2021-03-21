#include <stdio.h>
#include <stdlib.h>

#define MAXTAM 100
#define SEPARADOR -999 // Separador para organizar os números dentro da pilha

// Tipo abstrato de dados
typedef struct {
    int chave;
} Objeto;

// Tipo abstrato para pilha estática
typedef struct {
    Objeto array[MAXTAM];
    int topo;
} pilhaEstatica;

// Tipos abstratos para pilha dinâmica
typedef struct NoPilha *PtrNoPilha;

typedef struct NoPilha{
    Objeto obj;
    PtrNoPilha proximo;
} NoPilha;

typedef struct {
    PtrNoPilha topo;
    int tamanho;
} pilhaDinamica;

// Protótipos das funções para pilha estática
void iniciaPilhaE(pilhaEstatica *pilha);
void empilhaE(Objeto *obj, pilhaEstatica *pilha);
void desempilhaE(Objeto *obj, pilhaEstatica *pilha);
int tamanhoPilhaE(pilhaEstatica *pilha);
void converteDecBinE(pilhaEstatica *pilha, Objeto *obj, int decimal);

//  Protótipos das funções para pilha dinâmica
void iniciaPilhaD(pilhaDinamica *pilha);
void empilhaD(Objeto *obj, pilhaDinamica *pilha);
void desempilhaD(Objeto *obj, pilhaDinamica *pilha);
int tamanhoPilhaD(pilhaDinamica *pilha);
void converteDecBinD(pilhaDinamica *pilha, Objeto *obj, int decimal);

// Prótotipo da função para verificar se o número lido é inteiro
void verificaInt(int retornoLeitura, FILE *arqSaida);

int main(int argc, char *argv[]){
    pilhaEstatica pilhaE;
    pilhaDinamica pilhaD;
    Objeto obj;
    int decimal;
    int retornoLeitura; // Para receber o valor de retorno da função fscanf
    char tipoPilha;
    FILE *arqEntrada, *arqSaida;

    arqEntrada = fopen(argv[1], "r");
    arqSaida = fopen(argv[2], "w+");

    // Testando abertura do arquivo
    if (arqEntrada == NULL || arqSaida == NULL){
        printf("Erro ao abrir o arquivo!\n");
        system("pause");
        exit(1);
    }

    tipoPilha = fgetc(arqEntrada);

    // Se fgtc retornar a constante "End of file", é por que o arquivo está vazio
    if (tipoPilha == EOF){
        printf("Aquivo de entrada vazio!\n");
        system("pause");
        exit(1);

    } else if (tipoPilha == 'e') {
        iniciaPilhaE(&pilhaE);
        do {
            /* retornoLeitura armazena o retorno da função fscanf, e depois chama
            a próxima função que irá verificar se o número lido é um número inteiro.
            Caso não for, o programa será encerrado com o aviso "Arquivo fora
            do padrão" */
            retornoLeitura = fscanf(arqEntrada, "%d", &decimal);
            verificaInt(retornoLeitura, arqSaida);
            converteDecBinE(&pilhaE, &obj, decimal);
        } while (!feof(arqEntrada));

        /* Desempilhando o elemento do topo, que é um SEPARADOR, para não ser
        impresso uma quebra de linha no começo do arquivo */
        desempilhaE(&obj, &pilhaE);

        /* Desempilhando cada elemento e imprimindo no arquivo. E se for
        encontrado um separador, será impresso a quebra de linha */
        for (int i = tamanhoPilhaE(&pilhaE); i > 0; i--){
          desempilhaE(&obj, &pilhaE);

          if (obj.chave==SEPARADOR)
              fprintf(arqSaida, "\n");
          else
              fprintf(arqSaida, "%d", obj.chave);
        }
      // Convertendo Decimal para Binário utilizando pilha dinâmica (pilhaD).
    } else if (tipoPilha == 'd'){
        iniciaPilhaD(&pilhaD);
        do {
            retornoLeitura = fscanf(arqEntrada, "%d", &decimal);
            verificaInt(retornoLeitura, arqSaida);
            converteDecBinD(&pilhaD, &obj, decimal);
        } while (!feof(arqEntrada));

        desempilhaD(&obj, &pilhaD);

        for (int i = tamanhoPilhaD(&pilhaD); i > 0; i--){
            desempilhaD(&obj, &pilhaD);
            if (obj.chave==SEPARADOR)
                fprintf(arqSaida, "\n");
            else
                fprintf(arqSaida, "%d", obj.chave);
        }
      /* Não usei a função DestruirPilha, pois todos os elementos já são
      desempilhados dentro do for. */

    } else {
        printf("Arquivo fora do padrao esperado!\n");
        fprintf(arqSaida, "Arquivo inválido!");
    }

    fclose(arqEntrada);
    fclose(arqSaida);

    return 0;
}

/* ==================== Funções para pilha estática ==================== */

void iniciaPilhaE(pilhaEstatica *pilha) {
    pilha->topo = 0;
}

void empilhaE(Objeto *obj, pilhaEstatica *pilha) {
    if (pilha->topo==MAXTAM)
        printf("Atencao: Pilha cheia, nao foi possivel inserir o elemento.\n");
    else
        pilha->array[pilha->topo]=*obj;
    pilha->topo++;
}

void desempilhaE(Objeto *obj, pilhaEstatica *pilha) {
    if (pilha->topo==0)
        printf("Atencao: Pilha vazia, nao foi possivel remover elemento.\n");
    else
        *obj = pilha->array[pilha->topo-1];
    pilha->topo--;
}

int tamanhoPilhaE(pilhaEstatica *pilha) {
    return pilha->topo;
}

void converteDecBinE(pilhaEstatica *pilhaE, Objeto *obj, int decimal){
  /* Enquanto 'decimal' for diferente de 0, será empilhado o resto da divisão de 'decimal'
  por 2, e 'decimal' reberá o quociente da divisão por 2 sucessivamente. */
    do {
        obj->chave = decimal % 2;
        decimal = decimal / 2;
        empilhaE(obj, pilhaE);
    } while(decimal!=0);

  /* Empilhando a constante SEPARADOR, para organizar os números dentro da
  pilha */
    obj->chave = SEPARADOR;
    empilhaE(obj, pilhaE);
}

/* ==================== Funções para pilha dinâmica ==================== */

void iniciaPilhaD(pilhaDinamica *pilha){
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

void empilhaD(Objeto *obj, pilhaDinamica *pilha){
    PtrNoPilha Aux;
    Aux = (PtrNoPilha) malloc(sizeof(PtrNoPilha));
    Aux->obj = *obj;
    Aux->proximo = pilha->topo;
    pilha->topo = Aux;
    pilha->tamanho++;
}

void desempilhaD(Objeto *obj, pilhaDinamica *pilha){
    if (pilha->topo==NULL) {
        printf("Atencao: Pilha vazia!\n");
    } else {
        PtrNoPilha Apagar;
        Apagar = pilha->topo;
        *obj = pilha->topo->obj;
        pilha->topo = Apagar->proximo;
        free(Apagar);
        pilha->tamanho--;
    }
}

int tamanhoPilhaD(pilhaDinamica *pilha){
    return pilha->tamanho;
}

void converteDecBinD(pilhaDinamica *pilhaD, Objeto *obj, int decimal){
  /* Enquanto 'decimal' for diferente de 0, será empilhado o resto da divisão de 'decimal'
  por 2, e 'decimal' reberá o quociente da divisão por 2, assim sucessivamente. */
    do {
      obj->chave = decimal % 2;
      decimal = decimal / 2;
      empilhaD(obj, pilhaD);
    } while (decimal != 0);

    /* Empilhando a constante SEPARADOR, para organizar os números dentro da
    pilha */
    obj->chave = SEPARADOR;
    empilhaD(obj, pilhaD);
}

/* retornoLeitura contém o valor de retorno da função fscanf. Em caso de sucesso
na leitura de um número inteiro, a função retornará 1. Caso contrário, retornará
0, e então o programa deverá encerrado */
void verificaInt(int retornoLeitura, FILE *arqSaida){
    if (retornoLeitura==0){
        printf("Arquivo fora do padrao esperado!\n");
        /* Rewind para o indicador de posição voltar ao início e o arquivo de
        saída exibir apenas "Arquivo inválido", caso anteriormente tenha sido
        impresso algum número */
        rewind(arqSaida);
        fprintf(arqSaida, "Arquivo inválido!");
        exit(1);
    }
}
