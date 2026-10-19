#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"

int push(Stack* stack, const char item) {
    if (stack -> size >= STACK_SIZE) {
        for (int i = 0; i < STACK_SIZE - 1; i++) {
            stack -> data[i] = stack -> data[i + 1];
        }
        stack -> size -= 1;
    }
    stack -> data[stack -> size] = item;
    stack -> size++;
    return 1;
}

char pop(Stack* stack) {
    if (stack -> size == 0) {
        return '\0';
    }
    stack -> size--;
    return stack -> data[stack -> size];
}

void free_stack(Stack* stack) {
    if (stack -> data) {
        free(stack -> data);
        stack -> data = NULL;
    }
    free(stack);
    stack = NULL;
}

Stack* init_stack() {
    Stack* stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        return NULL;
    }
    stack -> data = malloc(sizeof(char) * STACK_SIZE);
    if (stack -> data == NULL) {
        return NULL;
    }
    stack -> size = 0;
    return stack;
}

