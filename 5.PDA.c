#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef struct {
    char stack[MAX_STACK_SIZE];
    int top;
} Stack;

void initialize_stack(Stack *stack) {
    stack->top = -1;
}

int is_empty(Stack *stack) {
    return stack->top == -1;
}

int is_full(Stack *stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

void push(Stack *stack, char symbol) {
    if (!is_full(stack)) {
        stack->stack[++stack->top] = symbol;
    } else {
        printf("Error: Stack overflow\n");
        exit(1);
    }
}

char pop(Stack *stack) {
    if (!is_empty(stack)) {
        return stack->stack[stack->top--];
    } else {
        printf("Error: Stack underflow\n");
        exit(1);
    }
}

char peek(Stack *stack) {
    if (!is_empty(stack)) {
        return stack->stack[stack->top];
    } else {
        return '\0'; 
    }
}

     int simulate

