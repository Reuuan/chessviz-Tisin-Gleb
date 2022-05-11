#include <libchess/libchess.h>

int main()
{
    char field[LENGTH][WIDTH];
    char backend[LENGTH][WIDTH];
    create_field(field);
    create_field(backend);
    while (1)
    {
        show_field(field);
        if (move_proccess(field) == 1)
        {
            backend_field(field, backend, 0);
        }else{
            backend_field(field, backend, 1);
        }
    }
}