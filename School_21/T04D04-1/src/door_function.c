#include <math.h>
#include <stdio.h>

double anezy(double x);
double bernully(double x);
double gyp(double x);

int main() {
    double pi;
    pi = (3.141592653589793238462643383279 * 2) / (42 - 1);

    for (double i = -3.141592653589793238462643383279; i <= 3.141592653589793238462643383279; i = i + pi) {
        printf("%.7lf | ", i);
        anezy(i);
        bernully(i);
        gyp(i);
    }

    return 0;
}

double anezy(double x) {
    double y;

    y = pow(1, 3) / (pow(1, 2) + pow(x, 2));

    printf("%.7lf | ", y);

    return 0;
}

double bernully(double x) {
    double y;

    y = sqrt(sqrt(pow(1, 4) + 4 * pow(x, 2) * pow(1, 2)) - pow(x, 2) - pow(1, 2));

    if (y > 0) {
        printf("%.7lf | ", y);
    } else {
        printf("- | ");
    }
    return 0;
}

double gyp(double x) {
    double y;

    y = 1 / pow(x, 2);

    printf("%.7lf \n", y);

    return 0;
}
