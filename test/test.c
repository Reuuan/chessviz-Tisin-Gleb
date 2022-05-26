#include <ctest.h>
#include <libchess.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

CTEST(chess_suite, knight_move) {
  int cur_sym = 0;
  char field[WIDTH][LENGTH] = {{'R', ' ', 'B', ' ', 'K', 'B', 'N', 'R'},  // 1
                               {'P', 'P', 'P', ' ', 'P', 'P', 'P', ' '},  // 2
                               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  // 3
                               {' ', ' ', ' ', 'N', ' ', ' ', 'p', 'P'},  // 4
                               {' ', 'p', ' ', ' ', ' ', 'Q', ' ', ' '},  // 5
                               {' ', ' ', 'p', 'p', ' ', ' ', ' ', ' '},  // 6
                               {'p', ' ', ' ', ' ', ' ', 'p', ' ', 'p'},  // 7
                               {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}}; // 8
  // h   g   f   e   d   c   b   a
  char knight_on_free_tile[] = "Nd4-b3";
  char knight_attack_ally[] = "Nd4-f2";
  char knight_attack_enemy[] = "Nd4xb5";

  int exp = 1;
  ASSERT_EQUAL(exp, move_knight(field, knight_on_free_tile, cur_sym));
  ASSERT_NOT_EQUAL(exp, move_knight(field, knight_attack_ally, cur_sym));
  ASSERT_NOT_EQUAL(exp, move_knight(field, knight_attack_enemy, cur_sym));
}

CTEST(chess_suite, bishop_move) {
  int cur_sym = 0;
  char field[WIDTH][LENGTH] = {{'R', 'N', 'B', 'Q', 'K', ' ', 'N', 'R'},  // 1
                               {'P', 'P', 'P', 'P', ' ', 'P', 'P', 'P'},  // 2
                               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  // 3
                               {' ', ' ', ' ', 'B', 'P', ' ', ' ', ' '},  // 4
                               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  // 5
                               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  // 6
                               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},  // 7
                               {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}}; // 8
  // h   g   f   e   d   c   b   a
  char move1_right[] = "Bd4-c5";

  char move_incorrect_impos_move[] = "Bd4-f3";
  char move2_incorrect_attack_owns_units[] = "Bd4-g2";
  char move5_incorrect_was_taken_another_figure[] = "Ng1-g5";

  int res_incoorect =
      move_bishop(field, move5_incorrect_was_taken_another_figure, cur_sym);
  int res1_right = move_bishop(field, move1_right, cur_sym);

  int res4_incorrect_impos_move =
      move_bishop(field, move_incorrect_impos_move, cur_sym);
  int res5 = move_bishop(field, move2_incorrect_attack_owns_units, cur_sym);

  const int exp = 1;
  ASSERT_NOT_EQUAL(exp, res_incoorect);
  ASSERT_EQUAL(exp, res1_right);
  ASSERT_NOT_EQUAL(exp, res4_incorrect_impos_move);
  ASSERT_NOT_EQUAL(exp, res5);
}

CTEST(chess_suite, pawn_move) {
  int cur_sym = 0;
  char field[WIDTH][LENGTH] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},  // 1
                               {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},  // 2
                               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  // 3
                               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  // 4
                               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  // 5
                               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  // 6
                               {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},  // 7
                               {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}}; // 8
  // h   g   f   e   d   c   b   a
  char move_pawn_white[] = "e2-e4";
  char move_pawn_black[] = "h7-h6";

  int exp = 1;
  ASSERT_EQUAL(exp, move_pawn(field, move_pawn_white, cur_sym));
  ASSERT_EQUAL(exp, move_pawn(field, move_pawn_black, cur_sym));
}

CTEST(chess_suite, queen) {
  int cur_sym = 0;
  char field[WIDTH][LENGTH] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', ' '},  // 1
                               {'P', 'P', 'P', 'P', 'P', 'P', 'P', ' '},  // 2
                               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  // 3
                               {' ', ' ', ' ', ' ', 'R', ' ', 'p', 'P'},  // 4
                               {' ', 'p', ' ', ' ', ' ', ' ', ' ', ' '},  // 5
                               {' ', ' ', 'p', ' ', ' ', ' ', ' ', ' '},  // 6
                               {'p', ' ', ' ', 'p', 'p', 'p', ' ', 'p'},  // 7
                               {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}}; // 8
  // h   g   f   e   d   c   b   a
  char rock_on_free_tile[] = "Re4-f4";
  char rock_attack_ally[] = "Re4-e2";
  char rock_attack_enemy[] = "Re4xe7";
  char rock_across_figure[] = "Re4-d1";

  int exp = 1;
  ASSERT_EQUAL(exp, move_rock(field, rock_on_free_tile, cur_sym));
  ASSERT_NOT_EQUAL(exp, move_rock(field, rock_attack_ally, cur_sym));
  ASSERT_NOT_EQUAL(exp, move_rock(field, rock_attack_enemy, cur_sym));
  ASSERT_NOT_EQUAL(exp, move_rock(field, rock_across_figure, cur_sym));
}

CTEST(chess_suite, queen_move) {
  int cur_sym = 0;
  char field[WIDTH][LENGTH] = {{'R', 'N', 'B', ' ', 'K', 'B', 'N', 'R'},  // 1
                               {'P', 'P', 'P', ' ', 'P', 'P', 'P', ' '},  // 2
                               {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},  // 3
                               {' ', ' ', ' ', ' ', ' ', ' ', 'p', 'P'},  // 4
                               {' ', 'p', ' ', ' ', ' ', 'Q', ' ', ' '},  // 5
                               {' ', ' ', 'p', 'p', ' ', ' ', ' ', ' '},  // 6
                               {'p', ' ', ' ', ' ', ' ', 'p', ' ', 'p'},  // 7
                               {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}}; // 8
  // h   g   f   e   d   c   b   a
  char queen_on_free_tile[] = "Qf5-c5";
  char queen_attack_ally[] = "Qf5-f2";
  char queen_attack_enemy[] = "Qf5xf7";
  char queen_across_figure[] = "Qf5-a5";

  int exp = 1;
  ASSERT_EQUAL(exp, move_queen(field, queen_on_free_tile, cur_sym));
  ASSERT_NOT_EQUAL(exp, move_queen(field, queen_attack_ally, cur_sym));
  ASSERT_NOT_EQUAL(exp, move_queen(field, queen_attack_enemy, cur_sym));
  ASSERT_NOT_EQUAL(exp, move_queen(field, queen_across_figure, cur_sym));
}
