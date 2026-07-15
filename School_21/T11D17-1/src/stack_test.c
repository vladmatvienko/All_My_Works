#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0

int test_push() {
    Stack stack;
    init(&stack);

    if (!push(&stack, 10)) return FAIL;
    if (!push(&stack, 20)) return FAIL;

    int value;
    if (!pop(&stack, &value) || value != 20) return FAIL;
    if (!pop(&stack, &value) || value != 10) return FAIL;

    destroy(&stack);
    return SUCCESS;
}

int test_pop() {
    Stack stack;
    init(&stack);

    if (!push(&stack, 100)) return FAIL;

    int value;
    if (!pop(&stack, &value) || value != 100) return FAIL;

    if (pop(&stack, &value)) return FAIL;

    destroy(&stack);
    return SUCCESS;
}

int main() {
    if (test_push() == SUCCESS) {
        printf("SUCCESS push\n");
    } else {
        printf("FAIL push\n");
    }

    if (test_pop() == SUCCESS) {
        printf("SUCCESS pop\n");
    } else {
        printf("FAIL pop\n");
    }
    return 0;
}
