#ifndef STACK_H
#define STACK_H

#ifndef USE_STACK_LIST
#define USE_STACK_VECTOR
#endif

#ifdef USE_STACK_VECTOR

#define STACK_SIZE 3
typedef struct Stack {
    char* data;
    int size;
} Stack;

#else
typedef struct Item {
    char value;
    struct Item* next;
} Item;

typedef struct Stack {
    Item* top;
} Stack;
#endif

int push(Stack*, const char);
char pop(Stack*);
void free_stack(Stack*);
Stack* init_stack();

#endif
