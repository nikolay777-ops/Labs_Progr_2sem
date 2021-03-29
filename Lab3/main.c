/*
 * 3.2 (5). Король и ферзи. На шахматной доске находятся король и несколько
  ферзей другого цвета. Проверить, находится ли король под угрозой и
  если да, кто ему угрожает. Положение фигур задано массивом k(8,
  8): 0 – клетка пуста, 1 – король, 2 – ферзь.
 * */

#include "main.h"

figure** init_board(void) {
  figure** board;
  int num_queens;
  int i, j;
  
  if (!(board = malloc(sizeof(figure*) * 8))) {
    fprintf(stderr, "Don't launch this on a calculator\n");
    exit(EXIT_FAILURE);
  }
  
  for (i = 0; i < 8; i++) {
    if (!(board[i] = malloc(sizeof(figure) * 8))) {
      fprintf(stderr, "Don't launch this on a calculator\n");
      exit(EXIT_FAILURE);
    }
    
    for (j = 0; j < 8; j++) {
      board[i][j] = EMPTY;
    }
  }
  
  num_queens = rand() % 8;
  
  for (i = 0; i < num_queens; i++) {
    board[rand() % 8][rand() % 8] = QUEEN;
  }
  
  board[rand() % 8][rand() % 8] = KING;
  
  return board;
}

void clear_board(figure** board) {
  int i;
  
  for (i = 0; i < 8; i++) {
    free(board[i]);
  }
  free(board);
}

bool is_queen_threatening(field queen_pos, field king_pos) {
  field delta;
  delta.x = queen_pos.x - king_pos.x;
  delta.y = queen_pos.y - king_pos.y;
  
  if (delta.x == 0 || delta.y == 0 || abs(delta.x) == abs(delta.y)) {
    return true;
  }
  
  return false;
}

field get_king(figure** board) {
  int i, j;
  field ret = {-1, -1};
  
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      if (board[i][j] == KING) {
        ret.x = i;
        ret.y = j;
        return ret;
      }
    }
  }
  return ret;
}

void red() {
  printf("\033[1;31m");
}

void yellow() {
  printf("\033[1;33m");
}

void reset() {
  printf("\033[0m");
}

void print_board(figure** board) {
  int row, column;
  field current_queen_field;
  
  for (row = 0; row < 8; row++) {
    for (column = 0; column < 8; column++) {
      if (board[row][column] == QUEEN) {
        current_queen_field.x = row;
        current_queen_field.y = column;
        
        if (is_queen_threatening(current_queen_field, get_king(board))) {
          red();
        }
      } else if (board[row][column] == KING) {
        yellow();
      }
      
      printf("%d ", board[row][column]);
      reset();
    }
    printf("\n");
  }
}

int main() {
  figure** board;
  
  srand((unsigned int)time(NULL));
  
  board = init_board();
  print_board(board);
  clear_board(board);
  
  return 0;
}
