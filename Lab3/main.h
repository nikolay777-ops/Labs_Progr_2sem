#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef enum {
  EMPTY, KING, QUEEN
} figure;

typedef struct {
  int x, y;
} field;

figure** init_board();
void clear_board(figure** board);
bool is_queen_threatening(field queen_pos, field king_pos);
field get_king(figure** board);
void red();
void yellow();
void reset();
void print_board(figure** board);

#endif
