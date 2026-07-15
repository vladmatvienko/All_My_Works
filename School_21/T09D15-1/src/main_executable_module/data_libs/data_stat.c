#include "data_stat.h"

#include <stdio.h>

double variance(double *a, int n) {
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

double mean(double *a, int n) {
    double answer = 0;
    for (int i = 0; i < n; i++) {
        answer += a[i];
    }
    return answer / n;
}

double max(double *a, int n) {
    double max = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > max) max = a[i];
    }
    return max;
}
double min(double *a, int n) {
    double min = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min) min = a[i];
    }
    return min;
}
