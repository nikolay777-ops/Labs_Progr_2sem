#include <assert.h>

#include "main.h"

figure** init_test_board() {
  int i, j;
  
  assert(figure** test_board = malloc(sizeof(figure*) * 8));
  
  for (i = 0; i < 8; i++) {
    assert(test_board[i] = malloc(sizeof(figure) * 8));
  }
  
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      test_board[i][j] = EMPTY;
    }
  }
  
  test_board[0][0] = KING;
  test_board[3][0] = QUEEN;
  test_board[5][5] = QUEEN;
  test_board[2][1] = QUEEN;
  return test_board;
}

void test_get_king(figure** board) {
  field king_pos = get_king(board);
  
  assert(king_pos.x == 0);
  assert(king_pos.y == 0);
}

void test_is_queen_threatening() {
  field test_king1 = {0, 0}, 
        test_king2 = {5, 5};
  field test_queen1 = {3, 3}, 
        test_queen2 = {0, 0}, 
        test_queen3 = {7, 8};
        
  assert(is_queen_threatening(test_king1, test_queen1) == true);
  assert(is_queen_threatening(test_king1, test_queen3) == false);
  assert(is_queen_threatening(test_king2, test_queen2) == true);
  assert(is_queen_threatening(test_king2, test_queen3) == false);
}

#undef main
int main() {
  int i;
  figure** test_board = init_test_board();
  
  test_get_king(test_board);
  test_is_queen_threatening();
  
  printf("All tests passed successfully\n");
  
  for (i = 0; i < 8; i++) {
    free(test_board[i]);
  }  
  free(test_board);
  return 0;
}
