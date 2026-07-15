#include <stdio.h>

int del(int x);

int main() {
    int a;
    int div;
    char c;

    if (scanf("%d%c", &a, &c) == 2 && c == '\n' && a != 0 && a != 1 && a != -1) {
        div = del(a);
        printf("%d", div);
    } else {
        printf("n/a");
    }
    return 0;
}
int del(int x) {
    if (x >= 0) {
        for (int i = x - 1; i > 1; i--) {
            int key;
            key = 0;
            for (int a = i - 1; a > 1; a--) {
                for (int b = i - 1; b > 1; b--) {
                    if (a * b == i) {
                        key = 1;
                        break;
                    }
                }
                if (key == 1) {
                    break;
                }
            }
            if (key == 0) {
                for (int c = 0; c <= x; c++) {
                    if (c * i == x) {
                        return i;
                    }
                }
            }
        }
        return x;
    } else {
        x = x * -1;
        for (int i = x - 1; i >= 0; i--) {
            int key;
            key = 0;
            for (int a = i - 1; a > 1; a--) {
                for (int b = i - 1; b > 1; b--) {
                    if (a * b == i) {
                        key = 1;
                        break;
                    }
                }
                if (key == 1) {
                    break;
                }
            }
            if (key == 0) {
                for (int c = 0; c <= x; c++) {
                    if (c * i == x) {
                        return i;
                    }
                }
            }
        }
        return x;
    }
}
