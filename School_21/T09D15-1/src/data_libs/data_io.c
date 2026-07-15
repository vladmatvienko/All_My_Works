#include "data_io.h"

#include "stdio.h"

void input(double *a, int n) {
    for (int i = 0; i < n; i++) {
        char c = 'g';
        if (scanf("%lf%c", &a[i], &c) != 2 && c != ' ') {
            printf("n/a");
            return;
        }
    }
    return;
}

void output(double *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lf ", a[i]);
    }
    printf("\n");
}
