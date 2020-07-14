#include "game.h"
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

void Snake::init(int i)
{
    if (i == 1)
    {
        speed = 3, n = 9;
        pay = 1;
        SetConsoleTitle("贪吃蛇      简易难度");
    }
    else if (i == 2)
    {
        speed = 5, n = 25;
        pay = 1.5;
        SetConsoleTitle("贪吃蛇      正常难度");
    }
    else if (i == 3)
    {
        speed = 8, n = 40;
        pay = 2;
        SetConsoleTitle("贪吃蛇      专家难度");
    }
    // printf("那游戏开始啦!\n");
    // clock_t a = clock();
    // int i = 3;
    // cout << "倒计时：  ";
    // while (i > 0)
    // {
    //     Sleep(1000);
    //     printf("\b%d", i);
    //     i--;
    // }
    map = new where[(n + 2) * (n + 2)];
    vis = new int[(n + 2) * (n + 2)];
    memset(map, 0, sizeof(&map));
    for (int i = 0; i <= (n + 2) * (n + 2); i++)
    {
        if (i <= n + 1 || i > (n + 1) * (n + 2))
            vis[i] = -1;
        else if (i % (n + 2) == 0 || (i + 1) % (n + 2) == 0)
            vis[i] = -1;
        else
            vis[i] = 0;
    }
    int cc;
    while (1)
    {
        cc = rand() % ((n + 2) * (n - 2)) + 2 * n + 4; //非常易错
        if (vis[cc] == 0 && cc % (n + 2) > 1 && cc % (n + 2) < n)
            break;
    }
    tail = head = cc;
    vis[cc] = p = 1;
    map[cc] = (where)(rand() % 4 + 1);
    len = 0;
    cleanScreen();
}

void Snake::game_start()
{
    srand(time(0));
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rc = {0, 0, (short)(2 * n + 4), (short)(n + 3)};
    SetConsoleWindowInfo(hOut, true, &rc);
    WORD a3 = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE;
    draw_ground();
    new_seed();
    while (true)
    {
        if (_kbhit())
        {
            //如果有按键按下，则_kbhit()函数返回真
            int ch = _getch(); //使用_getch()函数获取按下的键值
            if (ch >= 'a')
                ch -= 32;
            turn(ch);
        }
        //draw();
        Sleep(1000 / (speed * p));
        {
            int text = go_ahead(head);
            gotoxy(2 * (head % (n + 2)), head / (n + 2));
            SetConsoleTextAttribute(hOut, a3);
            printf("■");
            if (text == 0)
            {
                SetConsoleTextAttribute(hOut, a3);
                gotoxy(0, n + 2);
                printf("请按任意键继续......");
                _getch();
                //COORD size = {120, 35};
                //SetConsoleScreenBufferSize(hOut, size);
                cleanScreen();
                Setgrade(len * (int)(10 * pay));
                SMALL_RECT rc = {1, 1, (short)120, (short)35};
                SetConsoleWindowInfo(hOut, true, &rc);
                printf("\n\n\n\n\n");
                printf("———————————————————————\n");
                printf("———————————————————————\n");
                printf("———                                  ———\n");
                printf("———                                  ———\n");
                printf("———       GAME OVER！嗷,你没了！     ———\n");
                printf("———                                  ———\n");
                printf("———                                  ———\n");
                printf("———————————————————————\n");
                printf("———————————————————————\n");
                Sleep(500);
                printf("\n\n\n\n\n");
                break;
            }
            else if (text == 1)
            {
                gotoxy(2 * (tail % (n + 2)), tail / (n + 2));
                cout << "  ";
                go_back();
            }
        }
        gotoxy(0, n + 2);
        SetConsoleTextAttribute(hOut, a3);
        printf("您的得分：%d", len * (int)(10 * pay));
        if (len == n * n)
        {
            SetConsoleTextAttribute(hOut, a3);
            gotoxy(0, n + 2);
            printf("请按任意键继续......");
            _getch();
            cleanScreen();
            //COORD size = {120, 35};
            //SetConsoleScreenBufferSize(hOut, size);
            Setgrade(len * (int)(10 * pay));
            SMALL_RECT rc = {1, 1, (short)120, (short)35};
            SetConsoleWindowInfo(hOut, true, &rc);
            printf("\n\n\n\n\n");
            printf("———————————————————————\n");
            printf("———————————————————————\n");
            printf("———                                  ———\n");
            printf("———                                  ———\n");
            printf("———       恭喜你！你胜利啦！！！     ———\n");
            printf("———                                  ———\n");
            printf("———                                  ———\n");
            printf("———————————————————————\n");
            printf("———————————————————————\n");
            Sleep(500);
            printf("\n\n\n\n\n");
            break;
        }
    }
}

void Snake::new_seed()
{
    int g;
    if (len == n * n)
        return;
    while (1)
    {
        g = rand() % (n * (n + 2) - 1) + n + 3;
        if (vis[g] == 0)
            break;
    }
    vis[g] = 2;
    gotoxy(2 * (g % (n + 2)), g / (n + 2));
    WORD a2 = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED;
    SetConsoleTextAttribute(hOut, a2);
    cout << "★";
}

int Snake::go_ahead(int &h)
{
    int ahead;
    switch (map[h])
    {
    case Up:
    {
        ahead = h - (n + 2);
        break;
    }
    case Down:
    {
        ahead = h + (n + 2);
        break;
    }
    case Left:
    {
        ahead = h - 1;
        break;
    }
    case Right:
    {
        ahead = h + 1;
        break;
    }
    default:
    {
        break;
    }
    }
    // cout << vis[ahead] << '\n';
    // _getch();
    if (vis[ahead] == 1 || vis[ahead] == -1)
        return 0;
    else if (vis[ahead] == 2)
    {
        vis[ahead] = 1;
        map[ahead] = map[h];
        h = ahead;
        len++;
        new_seed();
        return 2;
    }
    vis[ahead] = 1;
    map[ahead] = map[h];
    h = ahead;
    return 1;
}

void Snake::go_back()
{

    int behind;
    switch (map[tail])
    {
    case Up:
    {
        behind = tail - (n + 2);
        break;
    }
    case Down:
    {
        behind = tail + (n + 2);
        break;
    }
    case Left:
    {
        behind = tail - 1;
        break;
    }
    case Right:
    {
        behind = tail + 1;
        break;
    }
    default:
    {
        return;
        break;
    }
    }
    vis[tail] = 0;
    map[tail] = Null;
    tail = behind;
}

void Snake::turn(int ch)
{
    switch (ch)
    {
    case 'W':
    {
        if (map[head] == Down)
        {
            if (p != 1)
                p = 1;
        }
        else if (map[head] == Up)
            p = 2;
        else
            map[head] = Up;
        break;
    }
    case 'S':
    {
        if (map[head] == Up)
        {
            if (p != 1)
                p = 1;
        }
        else if (map[head] == Down)
            p = 2;
        else
            map[head] = Down;
        break;
    }
    case 'A':
    {
        if (map[head] == Right)
        {
            if (p != 1)
                p = 1;
        }
        else if (map[head] == Left)
            p = 2;
        else
            map[head] = Left;
        break;
    }
    case 'D':
    {
        if (map[head] == Left)
        {
            if (p != 1)
                p = 1;
        }
        else if (map[head] == Right)
            p = 2;
        else
            map[head] = Right;
        break;
    }
    default:
    {
        return;
        break;
    }
    }
}

void Snake::draw_ground()
{
    cleanScreen();
    WORD b1 = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    WORD b2 = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE;
    WORD b3 = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
    if (n == 9)
        SetConsoleTextAttribute(hOut, b1);
    if (n == 25)
        SetConsoleTextAttribute(hOut, b2);
    if (n == 40)
        SetConsoleTextAttribute(hOut, b3);
    for (int i = 0; i <= n + 1; i++)
    {
        if (i == 0 || i == n + 1)
        {
            for (int t = 0; t <= n + 1; t++)
                cout << "●";
            if (!i)
                printf("\n");
            continue;
        }
        cout << "●";
        gotoxy(2 * n + 2, i);
        cout << "●";
        printf("\n");
    }
}

// Snake::~Snake()
// {
//     delete[] vis;
//     delete[] map;
// }
