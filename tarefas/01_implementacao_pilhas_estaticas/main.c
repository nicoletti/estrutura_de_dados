#include "pilhaEstatica.h"


int main(int argc, const char * argv[]){
  pilhaEstatica p;
  Objeto ob;
  int opcao=0, tamanho=0;

  printf(">> MENU <<\n");
  printf("1. Inicializar pilha\n"
         "2. Verificar se a pilha esta vazia\n"
         "3. Verificar se a pilha esta cheia\n"
         "4. Inserir elemento na pilha\n"
         "5. Remover elemento da pilha\n"
         "6. Verificar tamanho da pilha\n"
         "7. Verificar elemento do topo\n"
         "8. Imprimir pilha\n"
         "9. Sair do programa\n");

do {
   printf("\n>> Digite o numero da opcao desejada: ");
   scanf("%d", &opcao);
   printf("\n");

 switch(opcao){
   case 1:
   iniciaPilha(&p);
   printf("Pilha inicializada com sucesso.\n");
   break;

   case 2:
   if (estaVazia(&p)) printf("Pilha esta vazia.\n");
   else printf("Pilha nao esta vazia.\n");
   break;

   case 3:
   if (estaCheia(&p)) printf("Pilha esta cheia.\n");
   else printf("Pilha nao esta cheia.\n");
   break;

   case 4:
   printf("Digite o valor para inserir na pilha: ");
   scanf("%d", &ob.chave);
   empilha(ob, &p);
   break;

   case 5:
   desempilha(&ob, &p);
   printf("Elemento do topo foi removido.\n");
   break;

   case 6:
   tamanho = tamanhoPilha(&p);

   printf("A pilha possui %d elemento(s).\n", tamanho);
   break;

   case 7:
   ob = topo(&p);
   printf("O elemento do topo eh: %d\n", ob.chave);
   break;

   case 8:
   imprimePilha(&p);
   break;

   case 9:
   printf("Programa finalizado.\n");
   break;

   default:
   printf ("Opção invalida, tente novamente.\n");
   break;
 }
} while (opcao != 9);

return 0;
}
