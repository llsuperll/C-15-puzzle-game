#include <stdio.h>
#include "../include/stack.h"
#include "../include/game.h"


int main() {
    Field field;
    Stack* moves = init_stack();
    if (!moves) {
        printf("Не удалось инициализировать стек.\n");
        return 1;
    }
    generate_field(&field);
    shuffle_board(&field);
    game(&field, moves);
    free_stack(moves);
    return 0;
}
