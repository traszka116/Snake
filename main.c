#define sizeX 9
#define sizeY 18
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "time.h"
#include "math.h"
#include "Windows.h"

typedef struct
{
    int x, y;
} segment;


typedef struct fruit
{
    int x, y;
} fruit;
fruit f = {5, 7};

typedef enum
{
    up = -1,
    down = 1,
    left = -2,
    right = 2
} direction;

void displayClear(), changeDirection(), move(), clearscreen(), displayPlayer(), addSegment(), die(), killYourself(), hitBorder(), displayFruit(), gatherFruit(), spreadFruit(), printGame();
direction current = left;
segment player[30] = {{3, 4}, {3, 5}, {3, 6}, {3, 7}};
char display[sizeX][sizeY];
int SegmentCount = 4;
byte alive = 1;
byte score = 0;
int timer = 300;

int main(int argc, char const *argv[])
{
    
        system("cls");

        spreadFruit();
        while (alive)
        {

            clearscreen();
            if (_kbhit())
            {
                changeDirection();
            }
            displayClear();
            displayPlayer();
            displayFruit();
            printGame();
            move();
            Sleep(timer);
        }

        _getch();

        return 0;
}
void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
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
    hitBorder();
    killYourself();
    gatherFruit();
}
void displayPlayer()
{

    for (int i = 0; i < SegmentCount; i++)
    {
        display[player[i].x][player[i].y] = '@';
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
    Sleep(500);
    alive = 0;
    clearscreen();
    system("cls");
    printf("\033[1;37m");
    for (int i = 0; i < 4; i++)
    {
        printf("--------------------\n");
    }
    printf("------Game Over-----\n");
    for (int i = 0; i < 4; i++)
    {
        printf("--------------------\n");
    }
    printf("your score is: %i", score);

    

}
void killYourself()
{

    for (int i = 1; i < SegmentCount; i++)
    {
        if ((player[0].x == player[i].x) && (player[0].y == player[i].y))
        {
            die();
        }
    }
}
void hitBorder()
{
    if ((player[0].x < 0) || (player[0].x > sizeX) || (player[0].y < 0) || (player[0].y > sizeY))
    {
        die();
    }
}
void spreadFruit()
{
    srand(time(NULL));
    f.x = rand() % sizeX;
    srand(time(NULL));
    f.y = rand() % sizeY;
}
void gatherFruit()
{

    if (player[0].x == f.x && player[0].y == f.y)
    {

        score++;
        timer -= score;
        spreadFruit();
        addSegment();
    }
}
void displayFruit()
{
    display[f.x][f.y] = '$';
}
void printGame()
{
    for (int i = 0; i < sizeX; i++)
    {
        for (int j = 0; j < sizeY; j++)
        {
            
            switch (display[i][j])
            {
            case '#':
                printf("\033[1;37m%c",219);    
                 break;
            
            case '@':
                printf("\033[0;32m%c",219);    
               
                break;
            
            case '$':
                printf("\033[0;31m%c",219);
                break;
            
            default:
                break;
            }
        }
        printf("\n");
    }
}