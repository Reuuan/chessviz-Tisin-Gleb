#include <libchess.h>

int main()
{
    char field[LENGTH][WIDTH];
    char backup[LENGTH][WIDTH];
    create_field(field);
    create_field(backup);
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