#define sizeX 18
#define sizeY 36
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "time.h"
#include "math.h"
#include "Windows.h"
#include "string.h"
typedef struct
{
    int x:6, y:6;
} segment;
typedef struct fruit
{
    int x:6, y:6;
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
direction current = right;
segment player[50] = {{3, 7}, {3, 6}, {3, 5}, {3, 4}};
char display[sizeX][sizeY];
int SegmentCount = 4;
byte alive = 1;
byte score = 0;
int timer = 100;
byte highscore = 0;
int wantToPlay = 1;

int main(int argc, char const *argv[])
{

start:
    alive = 1;
    score = 0;
    timer = 100;
    player[0].x = 3;
    player[0].y = 7;
    player[1].x = 3;
    player[1].y = 6;
    player[2].x = 3;
    player[2].y = 5;
    player[3].x = 3;
    player[3].y = 4;
    SegmentCount = 4;
    current = right;



    system("cls");
    spreadFruit();
    while (alive)
    {
        if (_kbhit())
        {
            changeDirection();
        }
        clearscreen();
        displayClear();
        displayPlayer();
        displayFruit();
        printGame();
        move();
        Sleep(50);
    }
    if (score > highscore)
    {
        highscore = score;
    }
    printf("highscore is: %i", highscore);
ask:

    printf("\nDo you want to Play agin?(y/n)\n");
    char c = _getch();
    if (c == 'y')
    {
        goto start;
    }
    else if (c == 'n')
    {
    }
    else
    {
        goto ask;
    }

    system("cls");

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

    default:
        break;
    }
}
void addSegment()
{
    if (SegmentCount == 50)
        return;
    segment secondLastCopy = player[SegmentCount - 2];
    segment lastCopy = player[SegmentCount - 1];
    int deltaX = lastCopy.x - secondLastCopy.x;
    int deltaY = lastCopy.y - secondLastCopy.y;
    segment newOne = {lastCopy.x + deltaX, lastCopy.y + deltaY};
    player[SegmentCount] = newOne;
    SegmentCount++;
}
void die()
{
    Sleep(300);
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
    printf("your score is: %i\n", score);
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
    if ((player[0].x < 0) || (player[0].x >= sizeX) || (player[0].y < 0) || (player[0].y >= sizeY))
    {
        die();
    }
}
void spreadFruit()
{
    srand(time(NULL));
    f.x = (rand() % (sizeX));
    srand(time(NULL));
    f.y = (rand() % (sizeY));
}
void gatherFruit()
{
    if (player[0].x == f.x && player[0].y == f.y)
    {
        score++;
        timer -= score / 10;
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
            char t[8];
            switch (display[i][j])
            {
            case '#':
                strcpy(t, "\033[1;37m");
                break;
            case '@':
                strcpy(t, "\033[0;32m");
                break;
            case '$':
                strcpy(t, "\033[0;31m");
                break;
            default:
                break;
            }
            printf("%s%c%c", t, 219, 219);
        }
        printf("\n");
    }
}