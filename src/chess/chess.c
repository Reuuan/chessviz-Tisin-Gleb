#include <libchess.h>

int main()
{
    char field[LENGTH][WIDTH];
    char backup[LENGTH][WIDTH];
    create_field(field);
    create_field(backup);
    show_field(field);

    while (1)
    {
        if (move_proccess(field) == -1)
        {
            backup_field(field, backup, 1);
            puts("рестарт до хода белых");
            show_field(field);    
        }
        else
        {
            backup_field(field, backup, 0);
        }
    }
}