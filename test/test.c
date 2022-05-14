#include <libchess.h>
#include <ctest.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


CTEST(chess_suite, knight_move)
{
    char field[LENGTH][WIDTH];
    create_field(field);
    
    char move_right[] = "Ng1-f3";
    char move1_right[] = "Ng1-h3";
    char move2_incorrect[] = "Ng1-";
    char move3_incorrect[] = "Ng1-e2";
    char move5_incorrect[] = "Ng1-g5"; 
    int current_symbol = 0;
    
    int res = move_knight(field, move_right, current_symbol);
    int res1 = move_knight(field, move1_right, current_symbol);
    int res_incorrect_input = move_knight(field, move2_incorrect, current_symbol);
    int res_array_index_out = move_knight(field, move3_incorrect, current_symbol);
    int res_incorrect_move = move_knight(field, move5_incorrect, current_symbol);

    const int exp = 1;
    ASSERT_EQUAL(exp, res);
    ASSERT_EQUAL(exp, res1);
    ASSERT_NOT_EQUAL(exp, res_incorrect_input);
    ASSERT_NOT_EQUAL(exp, res_array_index_out);
    ASSERT_NOT_EQUAL(exp, res_incorrect_move);
}