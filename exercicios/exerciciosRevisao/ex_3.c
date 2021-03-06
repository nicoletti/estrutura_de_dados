#include <stdio.h>

int Potenciacao(int x, int y){

   if (y==0)
        return 1;
   else
        return x * Potenciacao(x, y-1);
    }

int main(){
    int x, y;
    printf("Digite o valor da base: ");
    scanf("%d", &x);
    printf("Digite o valor do expoente: ");
    scanf("%d", &y);

    printf("\nResultado: %d", Potenciacao(x,y));

    return 0;
}
