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
void displayClear(), changeDirection(), move(), displayPlayer(), addSegment(),die();
typedef struct
{
    int x, y;
} segment;
segment player[30] = {{3, 4}, {3, 5}, {3, 6}, {3, 7}};

int SegmentCount = 4;

typedef enum
{
    up = -1,
    down = 1,
    left = -2,
    right = 2
} direction;

direction current = left;

byte alive = 1;
byte score = 0;

int main(int argc, char const *argv[])
{

    system("cls");

    while (alive)
    {

        clearscreen();
        if (_kbhit())
        {
            changeDirection();
        }

        
        displayClear();
        displayPlayer();
        move();
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

    for (int i = SegmentCount - 1; i > 0; i--)
    {
        player[i].x = player[i - 1].x;
        player[i].y = player[i - 1].y;
    }

    switch (current)
    {
    case up:
        player[0].x -= 1;
        if (player[0].x<0)
        {
            die();
        }
        
        break;
    case down:
        player[0].x += 1;
        if (player[0].x>sizeX)
        {
            die();
        }
        break;
    case left:
        player[0].y -= 1;
        if (player[0].y<0)
        {
            die();
        }
        break;
    case right:
        player[0].y += 1;
        if (player[0].y>sizeY)
        {
            die();
        }
        break;

    default:
        break;
    }
}

void displayPlayer()
{

    for (int i = 0; i < SegmentCount; i++)
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
    case 'p':
        addSegment();
        break;
    default:
        break;
    }
}

void addSegment()
{
    if (SegmentCount == 30)
        return;

    segment lastCopy = player[SegmentCount - 1];
    move();
    player[SegmentCount] = lastCopy;
    SegmentCount++;
}

void die()
{
    
    alive = 0;
    clearscreen();
    system("cls");
    for(int i = 0;i<4;i++)
    {
        printf("--------------------\n");
    }
    printf("------Game Over-----\n");
        for(int i = 0;i<4;i++)
    {
        printf("--------------------\n");
    }
}

void killYourself()
{
    
    for(int i = 1;i<SegmentCount;i++)
    {
        
    }
}
