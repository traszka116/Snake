#define sizeX 9
#define sizeY 18
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "math.h"
#include "Windows.h"

void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}
char display[sizeX][sizeY];
void displayClear(), changeDirection(), move(), displayPlayer();
typedef struct
{
    int x, y;
} segment;
segment player[4] = {{3, 4}, {3, 5}, {3, 6}, {3, 7}};
typedef enum
{
    up = -1,
    down = 1,
    left = -2,
    right = 2
} direction;

typedef struct {
    int x,y;
}coin;





direction current = left;

byte alive = 1;
byte score = 0;



int main(int argc, char const *argv[])
{   
    system("cls");

    while (1)
    {

        clearscreen();
        if (_kbhit())
        {
            changeDirection();
            move();
            displayClear();
            displayPlayer();
        }
        else
        {
            move();
            displayClear();
            displayPlayer();
        }
        Sleep(300);
    }

    return 0;
}

void displayClear()
{
    for (int i = 0; i < sizeX; i++)
    {
        for (int j = 0; j < sizeY; j++)
        {
            display[i][j] = '#';
        }
    }
}

void move()
{

    for (int i = 3; i > 0; i--)
    {
        player[i].x = player[i - 1].x;
        player[i].y = player[i - 1].y;
    }

    switch (current)
    {
    case up:
        player[0].x -= 1;
        break;
    case down:
        player[0].x += 1;
        break;
    case left:
        player[0].y -= 1;
        break;
    case right:
        player[0].y += 1;
        break;

    default:
        break;
    }
}

void displayPlayer()
{

    for (int i = 0; i < 4; i++)
    {
        display[player[i].x][player[i].y] = '@';
    }

    for (int i = 0; i < sizeX; i++)
    {
        for (int j = 0; j < sizeY; j++)
        {
            printf("%c", display[i][j]);
        }
        printf("\n");
    }
}

void changeDirection()
{
    char y = _getch();
    switch (y)
    {
    case 'w':
        if (abs(current) == abs(up))
        {
            break;
        }
        current = up;

        break;
    case 'a':
        if (abs(current) == abs(left))
        {
            break;
        }
        current = left;
        break;
    case 's':
        if (abs(current) == abs(down))
        {
            break;
        }
        current = down;
        break;
    case 'd':
        if (abs(current) == abs(right))
        {
            break;
        }
        current = right;
        break;

    default:
        break;
    }
}
