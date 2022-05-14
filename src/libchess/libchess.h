#include <stdio.h>
#define WIDTH 8
#define LENGTH 8

int move_proccess(char field[][WIDTH]);
char field[LENGTH][WIDTH];
void create_field(char field[][WIDTH]);
void show_field(char field[][WIDTH]);
unsigned int number(char symbol);
unsigned int letter(char symbol);
int move_knight(char field[][WIDTH], char buffer[], int cur_sym);
int move_bishop(char field[][WIDTH], char buffer[], int cur_sym);
int move_queen(char field[][WIDTH], char buffer[], int cur_sym);
int move_king(char field[][WIDTH], char buffer[], int cur_sym);
int move_rock(char field[][WIDTH], char buffer[], int cur_sym);
int type_of_figure(char field[][WIDTH], int cur_sym, char buffer[], char pawn);
int type_of_move(char field[][WIDTH], char buffer[], int cur_sym);
int is_correct_figure(char field[][WIDTH], char buffer[], int cur_sym, char figure);
int is_pawn(char field[][WIDTH], char buffer[], int cur_sym);
int is_right_field_range(char buffer[], int cur_sym);
int is_correct_figure(char field[][WIDTH], char buffer[], int cur_sym, char figure);
int move_pawn(char field[][WIDTH], char buffer[], int cur_sym);
void backup_field(char field[][WIDTH], char backup[][WIDTH], int turn_status);
int check(char field[][WIDTH], char buffer[], char cur_sym);
int checkmate(char field[][WIDTH], char buffer[], char cur_sym);
