#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

void init(Stack* stack) { stack->top = NULL; }

int push(Stack* stack, int value) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        return 0;
    }
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    return 1;
}

int pop(Stack* stack, int* value) {
    if (stack->top == NULL) {
        return 0;
    }
    StackNode* temp = stack->top;
    *value = temp->data;
    stack->top = temp->next;
    free(temp);
    return 1;
}

void destroy(Stack* stack) {
    while (stack->top != NULL) {
        StackNode* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}
