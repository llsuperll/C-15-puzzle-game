#ifndef GAME_H
#define GAME_H

#include "stack.h"
#define FIELD_SIZE 4

typedef struct Field {
    int board[FIELD_SIZE][FIELD_SIZE];
    int cur_row;
    int cur_col;
} Field;

void generate_field(Field* field);
void print_field(const Field* field);
void shuffle_board(Field* field);

int is_solved(Field* field);
int is_solvable(const Field* field);

void swap(int *a, int* b);
int move_panel(Field* field, int direction);
int get_reverse_move(const char move);
void undo_move(Field* field, Stack* moves_history);

void game(Field* field, Stack* moves_history);

#endif
