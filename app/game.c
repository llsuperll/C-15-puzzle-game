#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "../include/stack.h"
#include "../include/game.h"

void generate_field(Field* field) {
    int number = 1;
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            field -> board[i][j] = number;
            number++;
        }
    }
    field -> board[FIELD_SIZE - 1][FIELD_SIZE - 1] = 0;
    field -> cur_row = FIELD_SIZE - 1, field -> cur_col = FIELD_SIZE - 1;
}

void print_field(const Field* field) {
    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int col = 0; col < FIELD_SIZE; col++) {
            if (field -> board[row][col] == 0) {
                printf(" X ");
            } else {
                printf("%2d ", field -> board[row][col]);
            }
        }
        printf("\n");
    }
}

void swap(int *a, int* b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void shuffle_board(Field* field) {
    srand(time(NULL));

    for (int i = 0; i < FIELD_SIZE * FIELD_SIZE; i++) {
        int row1 = rand() % FIELD_SIZE, col1 = rand() % FIELD_SIZE;
        int row2 = rand() % FIELD_SIZE, col2 = rand() % FIELD_SIZE;
        swap(&field -> board[row1][col1], &field -> board[row2][col2]);
    }

    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int col = 0; col < FIELD_SIZE; col++) {
            if (field -> board[row][col] == 0) {
                field -> cur_row = row;
                field -> cur_col = col;
                break;
            }
        }
    }
    
    if (!is_solvable(field)) {
        printf("swapped\n");
        if ((field -> cur_row != 0 || field -> cur_col != 0) && (field -> cur_row != 0 || field -> cur_col != 1)) {
            swap(&field -> board[0][0], &field -> board[0][1]);
        } else {
            swap(&field -> board[1][0], &field -> board[1][1]);
        }
    }
}

// пояснение по решаемости пятнашек вложил в файл с индивидуальным заданием
int is_solvable(const Field* field) {
    int inversions_count = 0;
    int numbers[FIELD_SIZE * FIELD_SIZE - 1];
    int idx = 0;

    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int col = 0; col < FIELD_SIZE; col++) {
            if (field -> board[row][col] != 0) {
                numbers[idx++] = field -> board[row][col];
            }
        }
    }

    for (int i = 0; i < FIELD_SIZE * FIELD_SIZE - 1; i++) {
        for (int j = i + 1; j < FIELD_SIZE * FIELD_SIZE - 1; j++) {
            if (numbers[i] > numbers[j]) {
                inversions_count++;
            }
        }
    }
    printf("%d\n", inversions_count);
    int empty_row_from_bottom = FIELD_SIZE - field -> cur_row;
    
    if ((FIELD_SIZE % 2 == 1) || (empty_row_from_bottom % 2 == 1)) {
        return inversions_count % 2 == 0;
    } else {
        return inversions_count % 2 == 1;
    }
}

int is_solved(Field* field) {
    int expected_value = 1;
    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int col = 0; col < FIELD_SIZE; col++) {
            if (row == FIELD_SIZE - 1 && col == FIELD_SIZE -1) {
                if (field -> board[row][col] != 0) {
                    return 0;
                }
            } else {
                if (field -> board[row][col] != expected_value++) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int move_panel(Field* field, int direction) {
    int new_row = field -> cur_row;
    int new_col = field -> cur_col;

    switch (direction) {
        case 0: 
            new_row--;
            break;
        case 1: 
            new_col--;
            break;
        case 2: 
            new_row++;
            break;
        case 3: 
            new_col++;
            break;
        default: 
            return 0;
    }

    if (new_row >= 0 && new_row < FIELD_SIZE && new_col >= 0 && new_col < FIELD_SIZE) {
        swap(&field -> board[field -> cur_row][field -> cur_col], &field -> board[new_row][new_col]);
        field -> cur_row = new_row;
        field -> cur_col = new_col;
        return 1;
    }
    return 0;
}

int get_reverse_move(const char move) {
    int direction;
    switch (toupper(move)) {
        case 'W':
            direction = 2;
            break;
        case 'A':
            direction = 3;
            break;
        case 'S':
            direction = 0;
            break;
        case 'D':
            direction = 1;
            break;
    }
    return direction;
}

void undo_move(Field* field, Stack* moves_history) {
    char move;
    move = pop(moves_history);
    if (move == '\0') {
        printf("Нет ходов для отмены!\n");
        return;
    }
    int direction = get_reverse_move(move);
    move_panel(field, direction);
}

void game(Field* field, Stack* moves_history) {
    char input;
    int retval, direction;
    printf("Добро пожаловать в игру пятнашки!\nПеремещение: WASD\nОтмена хода: U\nВыход из игры: Q\n");
    while (!is_solved(field)) {
        print_field(field);
        printf("Введите направление > ");
        retval = scanf("%c", &input);
        if (retval == -1) {
            printf("Вы вышли из игры.\n");
            return;
        } else if (getchar() != '\n') {
            printf("Неизвестная команда.\nПеремещение: WASD\nОтмена хода: U\nВыход из игры: Q\n");
            while (getchar() != '\n');
            continue;
        }
        switch (toupper(input)) {
            case 'W':
                direction = 0;
                break;
            case 'A':
                direction = 1;
                break;
            case 'S':
                direction = 2;
                break;
            case 'D':
                direction = 3;
                break;
            case 'U':
                undo_move(field, moves_history);
                continue;
            case 'Q':
                printf("Вы вышли из игры.\n");
                return;
            default:
                printf("Неизвестная команда.\nПеремещение: WASD\nОтмена хода: U\nВыход из игры: Q\n");
                continue;
        }
        if (!move_panel(field, direction)) {
            printf("Невозможный ход. Попробуйте снова!\n");
        } else {
            push(moves_history, toupper(input));
        }
    }
    print_field(field);
    printf("Ура! ПОБЕДА!\n");
}
