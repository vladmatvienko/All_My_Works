#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (!input(data, &n)) {
        printf("n/a\n");
        return 1;
    }
    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1 || *n <= 0 || *n > NMAX) {
        return 0;
    }
    for (int i = 0; i < *n; i++) {
        char c = 'g';
        if (scanf("%d%c", a + i, &c) != 2 && c != ' ') {
            return 0;
        }
    }
    return 1;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf \n", max_v, min_v, mean_v, variance_v);
}

int max(int *a, int n) {
    int *m = a;
    for (int i = 1; i < n; i++) {
        if (a[i] > *m) {
            *m = a[i];
        }
    }
    return *m;
}

int min(int *a, int n) {
    int *m = a;
    for (int i = 1; i < n; i++) {
        if (a[i] < *m) {
            *m = a[i];
        }
    }
    return *m;
}

double mean(int *a, int n) {
    double answer = 0;
    for (int i = 0; i < n; i++) {
        answer += a[i];
    }
    return answer / n;
}

double variance(int *a, int n) {
    double sum = 0;
    double mid = 0;
    double answer = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    mid = sum / n;
    sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (a[i] - mid) * (a[i] - mid);
    }
    answer = sum / n;
    return answer;
}
