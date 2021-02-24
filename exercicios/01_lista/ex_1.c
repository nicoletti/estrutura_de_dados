#include <stdio.h>

int ConverteMinutos (int t, int *h, int *m){
    *h = t / 60;
    *m = (t % 60);
}

int main() {
    int totalMinutos, hr, min;

    printf("Digite o total de minutos:\n");
    scanf("%d", &totalMinutos);

    ConverteMinutos(totalMinutos, &hr, &min);

    printf("\nHoras/minutos:\n%02d:%02d", hr, min);
    return 0;
}