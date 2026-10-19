#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"

int push(Stack* stack, char value) {
    Item* new_item = malloc(sizeof(Item));
    if (new_item == NULL) {
        return 0;
    }
    new_item -> value = value;
    new_item -> next = stack -> top;
    stack -> top = new_item;
    return 1;
}

char pop(Stack* stack) {
    if (stack -> top == NULL) {
        return '\0';
    }
    Item* item = stack -> top;
    char elem = item -> value;
    stack -> top = item -> next;
    free(item);
    return elem;
}

void free_stack(Stack* stack) {
    while (stack -> top != NULL) {
        pop(stack);
    }
    free(stack);
}

Stack* init_stack() {
    Stack* stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        return NULL;
    }
    stack -> top = NULL;
    return stack;
}