/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/

#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
int find_answer(int *a, int n, double mid, double disp);

int main() {
    int n, data[NMAX];
    double middle, dispersia;
    if (!input(data, &n)) {
        printf("n/a\n");
        return 1;
    }
    middle = mean(data, n);
    dispersia = variance(data, n);
    int answer = find_answer(data, n, middle, dispersia);
    printf("%d \n", answer);
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

int find_answer(int *a, int n, double mid, double disp) {
    for (int i = 0; i < n; i++) {
        if (a[i] >= mid && a[i] <= mid + 3 * sqrt(disp) && a[i] % 2 == 0 && a[i] != 0) {
            return a[i];
        }
    }
    return 0;
}
