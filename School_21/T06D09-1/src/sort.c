#include <stdio.h>

#define ARRAY_SIZE 10

int read_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &array[i]) != 1) {
            return 0;
        }
    }
    return 1;
}

void sort_array(int *array, int size) {  // bubble
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void print_array(const int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[ARRAY_SIZE];

    if (!read_array(array, ARRAY_SIZE)) {
        printf("n/a\n");
        return 1;
    }

    sort_array(array, ARRAY_SIZE);

    print_array(array, ARRAY_SIZE);

    return 0;
}
