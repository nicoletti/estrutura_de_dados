#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nome[30];
  char genero[30];
  int integrantes;
  int ranking;
} Banda;

Banda banda[5];

void CriarBanda(Banda *banda){
  printf("Nome da banda: ");
  setbuf(stdin,NULL);
  fgets(banda->nome, 29, stdin);
  setbuf(stdin,NULL);
  printf("Genero: ");
  fgets(banda->genero, 29, stdin);
  setbuf(stdin,NULL);
  printf("Numero de integrantes: ");
  scanf("%d", &banda->integrantes);
  printf("Posicao no ranking: ");
  scanf("%d", &banda->ranking);
}

void Ranking(){
  int ranking = 0;
  printf("\nDigite uma posicao no ranking para pesquisa: ");
  scanf("%d", &ranking);

     for (int i=0; i<5; i++){
       if(banda[i].ranking == ranking){
       printf("\nBanda na posicao %d do ranking:\n", ranking);
       printf("Nome da banda: %s", banda[i].nome);
       printf("Genero: %s", banda[i].genero);
       printf("Numero de integrantes: %d\n", banda[i].integrantes);
 }
}}

int main(){

  printf("Preencha os dados das suas 5 bandas favoritas.\n");

  for (int i=0; i<5; i++){
    printf("\nBanda no. %d\n", i+1);
    CriarBanda(&banda[i]);
  }

  printf("\nSuas 5 bandas favoritas:\n");
  for (int i=0; i<5; i++){
    printf("\nNome da banda: %s", banda[i].nome);
    printf("Genero: %s", banda[i].genero);
    printf("Numero de integrantes: %d\n", banda[i].integrantes);
    printf("Posicao no ranking: %d\n", banda[i].ranking);
  }

  Ranking();

  printf("\nFim do programa!");

 return 0;
}
