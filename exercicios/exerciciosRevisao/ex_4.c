#include <stdio.h>
#include <stdlib.h>

void LerVetor(int *vet, int N){
  for(int i=0; i<N; i++){
    printf("Digite o valor para a %da posicao do vetor: ", i+1);
    scanf("%d", &vet[i]);
  }
}

int main(){
  int N, *vet;

  printf("Digite o numero de elementos para o vetor: ");
  scanf("%d", &N);

  vet = (int *) malloc(N*sizeof(int));

  LerVetor(vet, N);

//Imprimir vetor
 printf("\nVetor criado: {");
for(int i=0; i<N; i++){
  printf(" |%d|", vet[i]);
}
  printf(" }");
  free(vet);
return 0;
}
