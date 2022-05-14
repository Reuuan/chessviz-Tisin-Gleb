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

CTEST(chess_suite, bishop_move)
{
    int cur_sym = 0;
    char field[WIDTH][LENGTH] = {{'R', 'N', 'B', 'Q', 'K', ' ', 'N', 'R'},  //1
                                {'P', 'P', 'P', 'P', ' ', 'P', 'P', 'P'},   //2
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},   //3
                                {' ', ' ', ' ', 'B', 'P', ' ', ' ', ' '},   //4
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},   //5
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},   //6  
                                {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},   //7
                                {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};  //8
                                //h   g   f   e   d   c   b   a
    char move1_right[] = "Bd4-c5";
    
    char move_incorrect_impos_move[] = "Bd4-f3";
    char move2_incorrect_attack_owns_units[] = "Bd4-g2";
    char move5_incorrect_was_taken_another_figure[] = "Ng1-g5";
    
    int res_incoorect = move_bishop(field, move5_incorrect_was_taken_another_figure, cur_sym);
    int res1_right = move_bishop(field, move1_right, cur_sym);
    
    int res4_incorrect_impos_move = move_bishop(field, move_incorrect_impos_move, cur_sym);
    int res5 = move_bishop(field, move2_incorrect_attack_owns_units, cur_sym);

    const int exp = 1;
    ASSERT_NOT_EQUAL(exp, res_incoorect);
    ASSERT_EQUAL(exp, res1_right);
    ASSERT_NOT_EQUAL(exp, res4_incorrect_impos_move);
    ASSERT_NOT_EQUAL(exp, res5);
}  
