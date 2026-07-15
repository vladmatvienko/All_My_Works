#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(struct door* doors);
void sort(struct door* array, int size);
void output(const struct door* a, int n);

int main() {
    struct door* doors = malloc(DOORS_COUNT * sizeof(struct door));

    initialize_doors(doors);

    sort(doors, DOORS_COUNT);

    output(doors, DOORS_COUNT);

    free(doors);
    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!

void initialize_doors(struct door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void sort(struct door* array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j].id > array[j + 1].id) {
                int temp = array[j].id;
                array[j].id = array[j + 1].id;
                array[j + 1].id = temp;
                array[j].status = 0;
                array[j + 1].status = 0;
            }
        }
    }
}

void output(const struct door* a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d, %d", a[i].id, a[i].status);
        printf("\n");
    }
    printf("\n");
}
