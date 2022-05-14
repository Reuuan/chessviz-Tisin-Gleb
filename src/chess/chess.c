#include <libchess.h>

int main()
{
    //char field[LENGTH][WIDTH];
    char backup[LENGTH][WIDTH];
    //create_field(field);
    create_field(backup);
    char field[WIDTH][LENGTH] ={{'R', ' ', 'B', ' ', 'K', 'B', 'N', 'R'},  //1
                                {'P', 'P', 'P', ' ', 'P', 'P', 'P', ' '},   //2
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},   //3
                                {' ', ' ', ' ', 'N', ' ', ' ', 'p', 'P'},   //4
                                {' ', 'p', ' ', ' ', ' ', 'Q', ' ', ' '},   //5
                                {' ', ' ', 'p', 'p', ' ', ' ', ' ', ' '},   //6  
                                {'p', ' ', ' ', ' ', ' ', 'p', ' ', 'p'},   //7
                                {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};  //8
                                //h   g   f   e   d   c   b   a
    show_field(field);
    int i = 0;
    while (1)
    {
        if ( move_proccess(field) == -1)
        {
            backup_field(field, backup, 1);
            puts("рестарт до хода белых");
            show_field(field);
            i = 0;
            continue;
        }
        i++;
        if (i == 1)
        {
            backup_field(field, backup, 0);
            i = 0;
        }
    }
}