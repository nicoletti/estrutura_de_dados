#include <stdio.h>

int ConverteMinutos (int t, int *h, int *m){
    *h = t / 60;
    *m = (t % 60);
}

int main() {
    int totalMinutos, hr, min, *p1, *p2;

    p1 = &hr;
    p2 = &min;

    printf("Digite o total de minutos:\n");
    scanf("%d", &totalMinutos);

    ConverteMinutos(totalMinutos, p1, p2);

    printf("Horas/minutos: %02d:%02d", hr, min);
    return 0;
}
