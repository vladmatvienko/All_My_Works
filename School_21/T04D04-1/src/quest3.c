#include <stdio.h>

int fib(int a, int b, int c);

int main() {
    int x, y, z, f;
    char c;

    x = 0;
    y = 1;

    if (scanf("%d%c", &z, &c) == 2 && c == '\n') {
        f = fib(x, y, z);
        printf("%d", f);
    } else {
        printf("n/a");
    }

    return 0;
}

int fib(int a, int b, int c) {
    if (c == 0) {
        return a;
    } else {
        return fib(b, a + b, c - 1);
    }
}
