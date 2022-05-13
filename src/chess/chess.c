#include <libchess/libchess.h>

int main()
{
    char field[LENGTH][WIDTH];
    char backend[LENGTH][WIDTH];
    create_field(field);
    create_field(backend);
    show_field(field);
    while (1)
    {
        if (move_proccess(field) == 1)
        {
            backend_field(field, backend, 0);
        }else{
            backend_field(field, backend, 1);
        }
        show_field(field);
    }
}