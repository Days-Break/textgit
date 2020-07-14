#include "game.h"
#include <conio.h>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <queue>
#include <string>
#include <windows.h>
using namespace std;

// Mine::~Mine()
// {
//     for (int i = 0; i <= wid + 1; i++)
//     {
//         delete[] pos[i];
//         delete[] vis[i];
//         pos[i] = NULL;
//         vis[i] = NULL;
//     }
//     delete[] pos;
//     delete[] vis;
//     pos = NULL;
//     vis = NULL;
// }

void Mine::init(int i)
{
    if (i == 1)
    {
        len = 8;
        wid = 5;
        num = 10;
        pay = 1;
        SetConsoleTitle("扫雷      难度：青铜");
    }
    else if (i == 2)
    {
        len = 20;
        wid = 12;
        num = 50;
        pay = 1.5;
        SetConsoleTitle("扫雷      难度：铂金");
    }
    else if (i == 3)
    {
        len = 30;
        wid = 16;
        num = 101;
        pay = 2;
        SetConsoleTitle("扫雷      难度：王者");
    }
    pos = new int *[wid + 2];
    vis = new int *[wid + 2];
    for (int i = 0; i <= wid + 1; i++)
    {
        pos[i] = new int[len + 2];
        vis[i] = new int[len + 2];
        memset(pos[i], 0, (len + 2) * sizeof(int));
        memset(vis[i], 0, (len + 2) * sizeof(int));
    }
    for (int i = 0, boom = 0; i < num;)
    {
        boom = rand() % (wid * len);
        if (!vis[boom / len + 1][boom - (boom / len) * len + 1])
        {
            vis[boom / len + 1][boom - (boom / len) * len + 1] = 1;
            i++;
        }
    }
    for (int i = 0; i <= wid + 1; i++)
    {
        for (int j = 0; j <= len + 1; j++)
        {
            if (vis[i][j])
                pos[i][j] = -1;
            else if (i == 0 || i == wid + 1 || j == 0 || j == len + 1)
                pos[i][j] = -2;
            else
            {
                if (i == 1 && j == 1)
                {
                    pos[i][j] = vis[i][j + 1] + vis[i + 1][j] + vis[i + 1][j + 1];
                }
                else if (i == 1 && j == len)
                {
                    pos[i][j] = vis[i][j - 1] + vis[i + 1][j] + vis[i + 1][j - 1];
                }
                else if (i == wid && j == 1)
                {
                    pos[i][j] = vis[i][j + 1] + vis[i - 1][j] + vis[i - 1][j + 1];
                }
                else if (i == wid && j == len)
                {
                    pos[i][j] = vis[i][j - 1] + vis[i - 1][j] + vis[i - 1][j - 1];
                }
                else if (j == 1)
                {
                    pos[i][j] = vis[i - 1][j] + vis[i + 1][j] + vis[i - 1][j + 1] + vis[i][j + 1] + vis[i + 1][j + 1];
                }
                else if (j == len)
                {
                    pos[i][j] = vis[i - 1][j] + vis[i + 1][j] + vis[i - 1][j - 1] + vis[i][j - 1] + vis[i + 1][j - 1];
                }
                else if (i == 1)
                {
                    pos[i][j] = vis[i][j - 1] + vis[i][j + 1] + vis[i + 1][j - 1] + vis[i + 1][j] + vis[i + 1][j + 1];
                }
                else if (i == wid)
                {
                    pos[i][j] = vis[i][j - 1] + vis[i][j + 1] + vis[i - 1][j - 1] + vis[i - 1][j] + vis[i - 1][j + 1];
                }
                else
                {
                    pos[i][j] = vis[i - 1][j - 1] + vis[i - 1][j] + vis[i - 1][j + 1] + vis[i][j - 1] + vis[i][j + 1] + vis[i + 1][j - 1] + vis[i + 1][j] + vis[i + 1][j + 1];
                }
            }
        }
    }
    for (int i = 0; i <= wid + 1; i++)
        memset(vis[i], 0, (wid + 2) * sizeof(vis));
    solve = 0;
    // printf("那游戏开始啦!\n");
    // int i = 3;
    // cout << "倒计时：  ";
    // while (i > 0)
    // {
    //     Sleep(1000);
    //     printf("\b%d", i);
    //     i--;
    // }
    cleanScreen();
}

void Mine::game_start()
{
    srand(time(NULL));
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo(hOut, &bInfo);
    SetConsoleOutputCP(437);
    //COORD size = {(short)(2 * len + 2), (short)(wid + 3)};
    //SetConsoleScreenBufferSize(hOut, size);
    SMALL_RECT rc = {0, 0, (short)(2 * len + 2), (short)(wid + 4)};
    SetConsoleWindowInfo(hOut, true, &rc);
    COORD apos = {0, 0};
    INPUT_RECORD mouse;
    DWORD res;
    int count = 3;
    WORD att10 = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
    WORD at0 = BACKGROUND_INTENSITY;
    WORD at1 = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    WORD at2 = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    WORD at3 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    WORD at4 = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE;
    WORD at5 = FOREGROUND_RED | FOREGROUND_INTENSITY;
    WORD at6 = FOREGROUND_RED;
    WORD at7 = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    WORD at8 = FOREGROUND_RED | FOREGROUND_GREEN;
    //cleanScreen();
    char Box[6];
    Box[0] = (char)0xda; // 左上角点
    Box[1] = (char)0xbf; // 右上角点
    Box[2] = (char)0xc0; // 左下角点
    Box[3] = (char)0xd9; // 右下角点
    Box[4] = (char)0xc4; // 水平
    Box[5] = (char)0xb3; // 坚直
    SetConsoleTextAttribute(hOut, at7);
    for (apos.X = 1; apos.X <= 2 * len; apos.X++)
    {
        apos.Y = 0;
        FillConsoleOutputCharacter(hOut, Box[4], 1, apos, &res);
        if (apos.X == 1)
        {
            apos.X--;
            FillConsoleOutputCharacter(hOut, Box[0], 1, apos, &res);
            apos.X++;
        }
        else if (apos.X == 2 * len)
        {
            apos.X++;
            FillConsoleOutputCharacter(hOut, Box[1], 1, apos, &res);
            apos.X--;
        }
        apos.Y = wid + 1;
        FillConsoleOutputCharacter(hOut, Box[4], 1, apos, &res);
        if (apos.X == 1)
        {
            apos.X--;
            FillConsoleOutputCharacter(hOut, Box[2], 1, apos, &res);
            apos.X++;
        }
        else if (apos.X == 2 * len)
        {
            apos.X++;
            FillConsoleOutputCharacter(hOut, Box[3], 1, apos, &res);
            apos.X--;
        }
    }
    for (apos.Y = 1; apos.Y <= wid; apos.Y++)
    {
        apos.X = 0;
        FillConsoleOutputCharacter(hOut, Box[5], 1, apos, &res);
        apos.X = 2 * len + 1;
        FillConsoleOutputCharacter(hOut, Box[5], 1, apos, &res);
    }
    SetConsoleOutputCP(936);
    SetConsoleTextAttribute(hOut, att10);
    for (int i = 1; i <= wid; i++)
    {
        for (int j = 1; j <= len; j++)
        {
            SetConsoleTextAttribute(hOut, at1);
            gotoxy(2 * j - 1, i);
            cout << "■";
        }
    }
    while (1)
    {
        if (num == solve)
        {
            cleanScreen();
            Setgrade(solve * (int)(10 * pay));
            SetConsoleTextAttribute(hOut, att10);
            //COORD size = {120, 35};
            //SetConsoleScreenBufferSize(hOut, size);
            SMALL_RECT rw = {1, 1, 120, 35};
            SetConsoleWindowInfo(hOut, true, &rw);
            Sleep(2000);
            printf("\n\n\n\n\n");
            CloseHandle(hIn);
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
        ReadConsoleInput(hIn, &mouse, 1, &res);
        if (mouse.EventType == MOUSE_EVENT)
        {
            apos = mouse.Event.MouseEvent.dwMousePosition;
            int i, j = apos.Y;
            if (apos.X % 2 == 0)
                i = apos.X / 2;
            else
                i = (apos.X + 1) / 2;
            if (mouse.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                if (mouse.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
                {
                    if (count != 0)
                    {
                        SetConsoleTextAttribute(hOut, at8);
                        tip(i, j);
                        count--;
                        num--;
                        // SetConsoleTextAttribute(hOut, at1);
                        // gotoxy(2 * i - 1, j);
                        // cout << "■";
                        // vis[j][i] = 0;
                        // if (pos[j][i] == -3)
                        // {
                        //     solve--;
                        //     pos[j][i] = -1;
                        // }
                        // printf("[Cursor Position] X: %2u  Y: %2u\n", apos.X, apos.Y);
                        SetConsoleTextAttribute(hOut, att10);
                        gotoxy(0, wid + 2);
                        printf("您的得分：%d", solve * (int)(10 * pay));
                        printf("\n提示次数：%d", count);
                        continue;
                    }
                }
                else if (pos[j][i] == -1)
                {
                    Setgrade(solve * (int)(10 * pay));
                    SetConsoleTextAttribute(hOut, at6);
                    showclear();
                    cleanScreen();
                    //COORD size = {120, 35};
                    //SetConsoleScreenBufferSize(hOut, size);
                    SMALL_RECT rt = {1, 1, 120, 35};
                    SetConsoleWindowInfo(hOut, true, &rt);
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
                else if (pos[j][i] == 0)
                {
                    clear(i, j);
                    FillConsoleOutputAttribute(hOut, at0, 1, apos, &res);
                    gotoxy(2 * i - 1, j);
                    cout << "  ";
                }
                else if (pos[j][i] != -2 && pos[j][i] != -3 && vis[j][i] == 0)
                {
                    int k = pos[j][i];
                    if (k == 1)
                        SetConsoleTextAttribute(hOut, at1);
                    else if (k == 2)
                        SetConsoleTextAttribute(hOut, at2);
                    else if (k == 3)
                        SetConsoleTextAttribute(hOut, at3);
                    else if (k == 4)
                        SetConsoleTextAttribute(hOut, at4);
                    else if (k == 5)
                        SetConsoleTextAttribute(hOut, at5);
                    else if (k == 6)
                        SetConsoleTextAttribute(hOut, at6);
                    gotoxy(2 * i - 1, j);
                    printf(" %d", k);
                    //FillConsoleOutputCharacter(hOut, (char)(48 + k), 1, apos, &res);
                }
            }
            else if (mouse.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
            {
                if (vis[j][i] == 0)
                {
                    vis[j][i] = 1;
                    SetConsoleTextAttribute(hOut, at6);
                    gotoxy(2 * i - 1, j);
                    printf("√");
                    if (pos[j][i] == -1)
                    {
                        solve++;
                        pos[j][i] = -3;
                    }
                }
                else if (vis[j][i] == 1)
                {
                    vis[j][i] = 2;
                    SetConsoleTextAttribute(hOut, att10);
                    gotoxy(2 * i - 1, j);
                    cout << "？";
                    if (pos[j][i] == -3)
                    {
                        solve--;
                        pos[j][i] = -1;
                    }
                }
                else if (vis[j][i] == 2)
                {
                    vis[j][i] = 0;
                    SetConsoleTextAttribute(hOut, at1);
                    gotoxy(2 * i - 1, j);
                    cout << "■";
                }
            }
            gotoxy(0, wid + 2);
            SetConsoleTextAttribute(hOut, att10);
            // printf("[Cursor Position] X: %2u  Y: %2u\n", apos.X, apos.Y);
            printf("您的得分：%d", solve * (int)(10 * pay));
            printf("\n提示次数：%d", count);
        }
    }
}

void Mine::showclear()
{
    for (int i = 1; i <= wid; i++)
    {
        for (int j = 1; j <= len; j++)
        {
            if (pos[i][j] == -1)
            {
                gotoxy(2 * j - 1, i);
                cout << "¤";
            }
        }
    }
    gotoxy(0, wid + 2);
    WORD att10 = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
    SetConsoleTextAttribute(hOut, att10);
    printf("请按任意键继续....");
    _getch();
}

void Mine::clear(int x, int y)
{
    if (y <= 0 || y >= wid + 1 || x <= 0 || x >= len + 1)
    {
        return;
    }
    if (pos[y][x] == -3)
        return;
    gotoxy(2 * x - 1, y);
    if (pos[y][x] > 0)
    {
        WORD at1 = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        WORD at2 = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        WORD at3 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        WORD at4 = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE;
        WORD at5 = FOREGROUND_RED | FOREGROUND_INTENSITY;
        WORD at6 = FOREGROUND_RED;
        int k = pos[y][x];
        pos[y][x] = -3;
        if (k == 1)
            SetConsoleTextAttribute(hOut, at1);
        else if (k == 2)
            SetConsoleTextAttribute(hOut, at2);
        else if (k == 3)
            SetConsoleTextAttribute(hOut, at3);
        else if (k == 4)
            SetConsoleTextAttribute(hOut, at4);
        else if (k == 5)
            SetConsoleTextAttribute(hOut, at5);
        else if (k == 6)
            SetConsoleTextAttribute(hOut, at6);
        printf(" %d", k);
        return;
    }
    cout << "  ";
    pos[y][x] = -3;
    clear(x - 1, y);
    clear(x - 1, y - 1);
    clear(x - 1, y + 1);
    clear(x, y - 1);
    clear(x, y + 1);
    clear(x + 1, y);
    clear(x + 1, y - 1);
    clear(x + 1, y + 1);
}

void Mine::tip(int x, int y)
{
    cor t0(x, y);
    cor now[4], cnt;
    queue<cor> a;
    a.push(t0);
    while (!a.empty())
    {
        cnt = a.front();
        a.pop();
        if (pos[cnt.y][cnt.x] == -1)
        {
            gotoxy(2 * cnt.x - 1, cnt.y);
            cout << "¤";
            pos[cnt.y][cnt.x] = -3;
            return;
        }
        now[0] = now[1] = now[2] = now[3] = cnt;
        now[0].x--;
        now[1].x++;
        now[2].y--;
        now[3].y++;
        for (int i = 0; i <= 3; i++)
        {
            if (now[i].x > 0 && now[i].x <= len && now[i].y > 0 && now[i].y <= wid)
            {
                a.push(now[i]); //将满足的点都入队
            }
        }
    }
}