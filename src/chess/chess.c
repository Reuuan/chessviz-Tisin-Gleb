#include <libchess/libchess.h>

int main()
{
    char field[LENGTH][WIDTH];
    char backend[LENGTH][WIDTH];
    char buffer[16];
    create_field(field);
    create_field(backend);
    while (1)
    {
        show_field(field);
        move(buffer);
        if (move_proccess(buffer) == 0)
        {
            backend_field(field, backend, 0);
        }
        backend_field(field, backend, 1);
    }
}