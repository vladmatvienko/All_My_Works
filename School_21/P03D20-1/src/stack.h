#ifndef STACK_H
#define STACK_H

typedef struct StackNode {
    char data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;

void init(Stack* stack);
char push(Stack* stack, char value);
char pop(Stack* stack, char* value);
void destroy(Stack* stack);

#endif
