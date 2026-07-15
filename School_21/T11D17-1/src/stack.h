#ifndef STACK_H
#define STACK_H

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;

void init(Stack* stack);
int push(Stack* stack, int value);
int pop(Stack* stack, int* value);
void destroy(Stack* stack);

#endif
