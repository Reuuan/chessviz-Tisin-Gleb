#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <libchess/libchess.h>

int current_move = 1;

void clear (void)
{    
  while ( getchar() != '\n' );
}

void create_field(char field[][WIDTH])
{
    FILE *figures;
    if ((figures = fopen("figures.txt", "r")) == NULL)
    {
        puts("cringe");
        exit(1);
    }
    for (int i = 0; i < LENGTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            field[i][j] = fgetc(figures);
        }
    }
    fclose(figures);
}

void show_field(char field[][WIDTH])
{
    puts("");
    int row = 8;
    for (int i = LENGTH; i > 0; i--)
    {
        printf("%d ", row);
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c ", field[i - 1][j]);
        }
        printf("\n");
        row--;
    }
    printf("  ");
    for (int i = 0; i < WIDTH; i++)
    {
        printf("%c ", 'a' + i);
    }
    puts("\n");
    for (int i = 0; i < 15; i++)
    {
        printf("=");
    }
    puts("");
}

int move_proccess(char field[][WIDTH])
{
    //FILE *list_of_moves = fopen ("moves.txt","w");
    int cur_sym = 0;
    int shift = 0;
    int i = 0;
    char ch;
    char buffer[13];
    while (i < 2)
    {
        printf("Введите ход(пр. e2-e4)\n");
        printf("%d. ", current_move);
        // fscanf("");
        // fprintf(list_of_moves, "%s", buffer);
        int j = 0;
        while((ch = getchar()) != '\n')
        {
            buffer[j] = ch;
            if (j > 11)
            {
                clear();
                j = 0;
                return -1;
            }
            j++;
        }
        buffer[j + 1] = '\0';
        i++;

        if (field[number(buffer[cur_sym])][letter(buffer[cur_sym+1])] >= 'A' && \
                field[number(buffer[cur_sym])][letter(buffer[cur_sym+1])] <= 'H')
                    shift = 1;

        if (i == 1)
        {
            if (!isupper(field[number(buffer[shift+1])][letter(buffer[shift])]))
            {
                puts("Ошибка: Ход белых");
                return -1;
            }
        }
        else if (i == 2)
        {
            if (!islower(field[number(buffer[shift+1])][letter(buffer[shift])]))
            {
                puts("Ошибка: Ход черных");
                return -1;
            }
        }
        
        if (is_pawn(field, buffer, cur_sym) == 1)
        {
            if (type_of_figure(field, cur_sym, buffer, 'P') == 0)
                return 0;
        }
        else
        {
            if (type_of_figure(field, cur_sym, buffer, 0) == 0)
                return 0;
        }
    }
    current_move++;
    return 1;
}

// 2 - silence move; 1 - with attack; 0 mistake
int type_of_move(char field[][WIDTH], char buffer[], int cur_sym)
{  

    if (islower(field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])]) ^ \
        islower(field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])])   )
    {
        puts("Ошибка");
        return 0;
    }
    

    if (buffer[cur_sym + 2] == 'x')
    {
        return 1;
    }
    else if (buffer[cur_sym + 2] == '-')
    {
        return 2;
    }
    else
        return 0;
}

int proccess_type_of_move(char field[][WIDTH], int cur_sym, char buffer[])
{
    if (type_of_move(field, buffer, cur_sym) == 1 && (field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] == ' '))
    {
        puts("Ошибка: Ход с атакой, но нет взятия");
        return -1;
    }
    else if (type_of_move(field, buffer, cur_sym) == 2 && (field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] != ' '))
    {
        puts("Ошибка: Тихий ход, но есть взятие");
        return -1;
    }
    else if (type_of_move(field, buffer, cur_sym) == 0)
    {
        puts("Неккоректный ввод взятия");
        return -1;
    }
    return 1;
}

int is_pawn(char field[][WIDTH], char buffer[], int cur_sym)
{
    if (buffer[cur_sym] >= 'a' && buffer[cur_sym] <= 'h')
    {
        if (isdigit(buffer[cur_sym + 1]))
        {
            return 1;
        }
    }
    return -1;
}

int is_right_field_range(char field[][WIDTH], char buffer[], int cur_sym)
{
    if (number(buffer[cur_sym + 4]) >= LENGTH || letter(buffer[cur_sym + 3]) >= WIDTH)
    {
        puts("Ошибка: Выход за диапазон");
        return -1;
    }
    return 1;
}

unsigned int number(char symbol)
{
    unsigned int result = (unsigned int)symbol - 49;
    if (result > 7)
    {
        return 404;
    }
    return result;
}

unsigned int letter(char symbol)
{
    unsigned int result = (unsigned int)symbol - 97;
    if (result > 7)
    {
        return 404;
    }
    return result;
}

int is_correct_figure(char field[][WIDTH], char buffer[], int cur_sym, char figure)
{
    if (field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])] == figure ||
        field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])] == tolower(figure))
    {
        return 1;
    }
    else
    {
        puts("Ошибка несоответсвие фигур");
        return -1;
    }
}

int move_pawn(char field[][WIDTH], char buffer[], int cur_sym)
{
    static int white_pawns_first_move[WIDTH] = {0, 0, 0, 0, 0, 0, 0, 0};
    static int black_pawns_first_move[WIDTH] = {0, 0, 0, 0, 0, 0, 0, 0};
    char figure = field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])];
    int abs_num = abs(number(buffer[cur_sym + 4]) - number(buffer[cur_sym + 1]));
    //нельзя ходить пешкой назад + неккоректный ввод
    if ((number(buffer[cur_sym + 4]) - number(buffer[cur_sym + 1]) ) < 0 \
     || letter(buffer[cur_sym + 3]) - letter(buffer[cur_sym]) != 0)
        return -1;
    if (type_of_move(field, buffer, cur_sym) == 1) //attack peshki
    {
        if (field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] == ' ') return -1;
    }   
    else{
        if (figure == 'P')
        {
            if (abs_num == 2 && white_pawns_first_move[letter(buffer[cur_sym])] == 0 &&\
                (field[number(buffer[cur_sym + 1]) + 1][letter(buffer[cur_sym])] == ' ') &&\
                (field[number(buffer[cur_sym + 1]) + 2][letter(buffer[cur_sym])] == ' '))
            { // for white pawn
                white_pawns_first_move[letter(buffer[cur_sym])]++;
                field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])] = ' ';
                field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] = figure;
            }
            else if (abs_num == 1 && (field[number(buffer[cur_sym + 1]) + 1][letter(buffer[cur_sym])] == ' ') )
            {
                field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])] = ' ';
                field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] = figure;
            }
            else
            {
                puts("Ошибка: Неправильный ход пешки");
                return -1;
            }
        }
        else if (figure == 'p')
        {
            if (abs_num == 2 && black_pawns_first_move[letter(buffer[cur_sym])] == 0 &&\
                (field[number(buffer[cur_sym + 1]) - 1][letter(buffer[cur_sym])] == ' ') &&\
                (field[number(buffer[cur_sym + 1]) - 2][letter(buffer[cur_sym])] == ' '))
            { // for black pawn
                black_pawns_first_move[letter(buffer[cur_sym])]++;
                field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])] = ' ';
                field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] = figure;
            }
            else if (abs_num == 1 && (field[number(buffer[cur_sym + 1]) - 1][letter(buffer[cur_sym])] == ' ') )
            {
                field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])] = ' ';
                field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] = figure;
            }
            else
            {
                puts("Ошибка: Неправильный ход пешки");
                return -1;
            }
        }
    }
    field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])] = ' ';
    field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] = figure;
    return 1;
}

int move_knight(char field[][WIDTH], char buffer[], int cur_sym)
{
    cur_sym++;
    int abs_num = abs(number(buffer[cur_sym + 4]) - number(buffer[cur_sym + 1]));
    int abs_let = abs(letter(buffer[cur_sym + 3]) - letter(buffer[cur_sym]));
    char figure = field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])];
    if ((abs_let == 2 && abs_num == 1) || (abs_let == 1 && abs_num == 2))
    {
        if (proccess_type_of_move(field, cur_sym, buffer) == -1)
            return -1;
        field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])] = ' ';
        field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] = figure;
    }
    else
    {
        printf("Некорректный ход");
        return -1;
    }
    return 1;
}

int move_bishop(char field[][WIDTH], char buffer[], int cur_sym)
{
    cur_sym++; // cur sym = 1
    int abs_num = abs(number(buffer[cur_sym + 4]) - number(buffer[cur_sym + 1]));
    int abs_let = abs(letter(buffer[cur_sym + 3]) - letter(buffer[cur_sym]));
    char figure = field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])];

    if (abs_num == abs_let) // обработка возможности хода
    {
        //пр Bc1-f5
        int direction_num = number(buffer[cur_sym + 4]) - number(buffer[cur_sym + 1]);
        int direction_let = letter(buffer[cur_sym + 3]) - letter(buffer[cur_sym]);


        if (direction_let > 0 && direction_num > 0)
        {
            for (int i = 1; i <= abs_num; i++)
            {
                if (field[number(buffer[cur_sym + 1]) + i][letter(buffer[cur_sym]) + i] != ' ')
                {
                    puts("Ошибка на пути фигуры");
                    return -1;
                }
            }
        }
        else if (direction_let > 0 && direction_num < 0)
        {
            for (int i = 1; i <= abs_num; i++)
            {
                if (field[number(buffer[cur_sym + 1]) - i][letter(buffer[cur_sym]) + i] != ' ')
                {
                    puts("Ошибка на пути фигуры");
                    return -1;
                }
            }
        }
        else if (direction_let < 0 && direction_num < 0)
        {
            for (int i = 1; i <= abs_num; i++)
            {
                if (field[number(buffer[cur_sym + 1]) - i][letter(buffer[cur_sym]) - i] != ' ')
                {
                    puts("Ошибка на пути фигуры");
                    return -1;
                }
            }
        }
        else if (direction_let < 0 && direction_num > 0)
        {
            for (int i = 1; i <= abs_num; i++)
            {
                if (field[number(buffer[cur_sym + 1]) + i][letter(buffer[cur_sym]) - i] != ' ')
                {
                    puts("Ошибка на пути фигуры");
                    return -1;
                }
            }
        }

        if (proccess_type_of_move(field, cur_sym, buffer) == -1)
            return -1;

        field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])] = ' ';
        field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] = figure;
    }
    else
    {
        printf("Некорректный ход");
        return -1;
    }
    return 1;
}

int move_queen(char field[][WIDTH], char buffer[], int cur_sym)
{
    cur_sym++;
    int abs_num = abs(number(buffer[cur_sym + 4]) - number(buffer[cur_sym + 1]));
    int abs_let = abs(letter(buffer[cur_sym + 3]) - letter(buffer[cur_sym]));
    char figure = field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])];

    int direction_num = number(buffer[cur_sym + 4]) - number(buffer[cur_sym + 1]);
    int direction_let = letter(buffer[cur_sym + 3]) - letter(buffer[cur_sym]);
    
    if (abs_num == abs_let) // bishop
    {
        if (direction_let > 0 && direction_num > 0)
        {
            for (int i = 1; i <= abs_num; i++)
            {
                if (field[number(buffer[cur_sym + 1]) + i][letter(buffer[cur_sym]) + i] != ' ')
                {
                    puts("Ошибка на пути фигуры");
                    return -1;
                }
            }
        }
        else if (direction_let > 0 && direction_num < 0)
        {
            for (int i = 1; i <= abs_num; i++)
            {
                if (field[number(buffer[cur_sym + 1]) - i][letter(buffer[cur_sym]) + i] != ' ')
                {
                    puts("Ошибка на пути фигуры");
                    return -1;
                }
            }
        }
        else if (direction_let < 0 && direction_num < 0)
        {
            for (int i = 1; i <= abs_num; i++)
            {
                if (field[number(buffer[cur_sym + 1]) - i][letter(buffer[cur_sym]) - i] != ' ')
                {
                    puts("Ошибка на пути фигуры");
                    return -1;
                }
            }
        }
        else if (direction_let < 0 && direction_num > 0)
        {
            for (int i = 1; i <= abs_num; i++)
            {
                if (field[number(buffer[cur_sym + 1]) + i][letter(buffer[cur_sym]) - i] != ' ')
                {
                    puts("Ошибка на пути фигуры");
                    return -1;
                }
            }
        }
    }
    else if ((abs_num == 0 && abs_let != 0) || (abs_num != 0 && abs_let == 0))
    { // rock
        if (direction_num > 0)
        {
            for (int i = 1; i <= abs_num; i++)
            {
                if (field[number(buffer[cur_sym + 1]) + i][letter(buffer[cur_sym])] != ' ')
                {
                    puts("на пути фигуры");
                    return -1;
                }
            }
        }
        else if (direction_num < 0)
        {
            for (int i = 1; i <= abs_num; i++)
            {
                if (field[number(buffer[cur_sym + 1]) - i][letter(buffer[cur_sym])] != ' ')
                {
                    puts("на пути фигуры");
                    return -1;
                }
            }
        }
        else if (direction_let > 0)
        {
            for (int i = 1; i <= abs_let; i++)
            {
                if (field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym]) + i] != ' ')
                {
                    puts("на пути фигуры");
                    return -1;
                }
            }
        }
        else if (direction_let < 0)
        {
            for (int i = 1; i <= abs_let; i++)
            {
                if (field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym]) - i] != ' ')
                {
                    puts("на пути фигуры");
                    return -1;
                }
            }
        }
    }
    else if (abs_num <= 1 && abs_let <= 1) // king
    {
        if (field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] != ' ')
        {
            puts("Ошибка на пути фигуры");
            return -1;
        }
    }
    else
    {
        printf("Некорректный ход");
        return -1;
    }

    if (proccess_type_of_move(field, cur_sym, buffer) == -1)
        return -1;

    field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])] = ' ';
    field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] = figure;
    return 1;
}

int move_king(char field[][WIDTH], char buffer[], int cur_sym)
{
    cur_sym++;
    int abs_num = abs(number(buffer[cur_sym + 4]) - number(buffer[cur_sym + 1]));
    int abs_let = abs(letter(buffer[cur_sym + 3]) - letter(buffer[cur_sym]));
    char figure = field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])];
    if (abs_num <= 1 && abs_let <= 1)
    {
        if (field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] != ' ')
        {
            puts("Ошибка на пути фигуры");
            return -1;
        }

        if (proccess_type_of_move(field, cur_sym, buffer) == -1)
            return -1;

        field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])] = ' ';
        field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] = figure;
    }
    else
    {
        printf("Некорректный ход");
        return -1;
    }
    return 1;
}

int move_rock(char field[][WIDTH], char buffer[], int cur_sym)
{
    cur_sym++;
    int abs_num = abs(number(buffer[cur_sym + 4]) - number(buffer[cur_sym + 1]));
    int abs_let = abs(letter(buffer[cur_sym + 3]) - letter(buffer[cur_sym]));
    char figure = field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])];
    if ((abs_num == 0 && abs_let != 0) || (abs_num != 0 && abs_let == 0))
    {
        int direction_num = number(buffer[cur_sym + 4]) - number(buffer[cur_sym + 1]);
        int direction_let = letter(buffer[cur_sym + 3]) - letter(buffer[cur_sym]);
        if (direction_num > 0)
        {
            for (int i = 1; i <= abs_num; i++)
            {
                if (field[number(buffer[cur_sym + 1]) + i][letter(buffer[cur_sym])] != ' ')
                {
                    puts("на пути фигуры");
                    return -1;
                }
            }
        }
        else if (direction_num < 0)
        {
            for (int i = 1; i <= abs_num; i++)
            {
                if (field[number(buffer[cur_sym + 1]) - i][letter(buffer[cur_sym])] != ' ')
                {
                    puts("на пути фигуры");
                    return -1;
                }
            }
        }
        else if (direction_let > 0)
        {
            for (int i = 1; i <= abs_let; i++)
            {
                if (field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym]) + i] != ' ')
                {
                    puts("на пути фигуры");
                    return -1;
                }
            }
        }
        else if (direction_let < 0)
        {
            for (int i = 1; i <= abs_let; i++)
            {
                if (field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym]) - i] != ' ')
                {
                    puts("на пути фигуры");
                    return -1;
                }
            }
        }

        if (proccess_type_of_move(field, cur_sym, buffer) == -1)
            return -1;

        field[number(buffer[cur_sym + 1])][letter(buffer[cur_sym])] = ' ';
        field[number(buffer[cur_sym + 4])][letter(buffer[cur_sym + 3])] = figure;
    }
    else
    {
        printf("Некорректный ход");
        return -1;
    }
    return 1;
}

int type_of_figure(char field[][WIDTH], int cur_sym, char buffer[], char pawn)
{
    char figure = buffer[cur_sym];
    if (pawn == 'P')
    {
        move_pawn(field, buffer, cur_sym);
    }
    else
    {
        if (is_correct_figure(field, buffer, cur_sym + 1, figure) != 1)
            return -1;

        switch (buffer[cur_sym])
        {
        case 'N':
            if (move_knight(field, buffer, cur_sym) == -1)
                return -1;
            break;
        case 'B':
            if (move_bishop(field, buffer, cur_sym) == -1)
                return -1;
            break;
        case 'Q':
            if (move_queen(field, buffer, cur_sym) == -1)
                return -1;
            break;
        case 'R':
            if (move_rock(field, buffer, cur_sym) == -1)
                return -1;
            break;
        case 'K':
            if (move_king(field, buffer, cur_sym) == -1)
                return -1;
            break;
        case 'P':
            break;

        default:
            printf("Фигура отсутствует\n");
            return -1;
        }
    }
    return 1;
}
// turn status 1 = need backend
// turn status 0 = no need backend
void backend_field(char field[][WIDTH], char backend[][WIDTH], int turn_status)
{
    if (turn_status == 1)
    {
        field = backend;
    }
    else
    {
        backend = field;
    }
}
