#include <stdio.h>
#include <stdlib.h>

#include "data_libs/data_io.h"
#include "data_process.h"

int main() {
    int n;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("n/a");
        return 0;
    }

    double *data = malloc(n * sizeof(double *));

    input(data, n);

    if (normalization(data, n))
        output(data, n);
    else
        printf("ERROR");
    free(data);
    return 0;
}
