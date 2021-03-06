#include <stdio.h>
#include <stdlib.h>

int main(){
  char c;
  int linhas = 0;
  FILE *arq1, *arq2;

  arq1 = fopen("arquivo.txt", "r");
  arq2 = fopen("arquivo_final.txt", "w");

  if ((arq1 == NULL) || (arq2 == NULL)){
    printf("Erro ao abrir o arquivo.");
    system("pause");
    exit(1);
}

  c = fgetc(arq1);
  while (c!=EOF){
  if ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u') ||
  (c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U'))
    fputc('*',arq2);
  else if (c=='\n'){
    linhas++;
    fputc(c,arq2);
  }
    else
    fputc(c,arq2);
  c = fgetc(arq1);}

  printf("Ha %d linhas no arquivo.", linhas+1);

  fclose(arq1);
  fclose(arq2);

  return 0;
  }
