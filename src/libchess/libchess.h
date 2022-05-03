#include <stdio.h>
#define WIDTH 8
#define LENGTH 8

char field[LENGTH][WIDTH];
void create_field(char field[][WIDTH]);
void show_field(char field[][WIDTH]);
void move(char buffer[]);
int move_proccess(char buffer[]);
unsigned int number(char symbol);
unsigned int letter(char symbol);
void move_knight(char field[][WIDTH], char buffer[], int cur_sym);
int type_of_figure(char field[][WIDTH], int cur_sym, char buffer[], char pawn);
char type_of_move(char type);
int is_correct_figure(char field[][WIDTH], char buffer[], int cur_sym, char figure);
int is_pawn(char field[][WIDTH], char buffer[], int cur_sym);
int black_turn(char buffer[]);
int is_right_field_range(char field[][WIDTH], char buffer[], int cur_sym);
int is_correct_figure(char field[][WIDTH], char buffer[], int cur_sym, char figure);
void move_pawn(char field[][WIDTH], char buffer[], int cur_sym);
void backend_field(char field[][WIDTH], char backend[][WIDTH], int turn_status);
