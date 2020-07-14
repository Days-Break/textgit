#include "game.h"
#include <iostream>
#include <string>
#include <windows.h>
void gamer::Setname(string master)
{
    name = master;
}

void gamer::SetCode(string c)
{
    code = c;
}

void gamer::SetID(string i)
{
    ID = i;
}

void gamer::Setlogin(string i, string j)
{
    time = i + " " + j;
}

void gamer::Setlogin(string i)
{
    time = i;
}

void gamer::SetTimes(int a, int b)
{
    game1 = a;
    game2 = b;
}

void gamer::SetBest(int a, int b)
{
    best1 = a;
    best2 = b;
}

void gamer::AddTimes(int i)
{
    if (i == 1)
    {
        game1++;
    }
    else
        game2++;
}

string gamer::Getname()
{
    return name;
}

string gamer::GetCode()
{
    return code;
}

string gamer::GetID()
{
    return ID;
}

string gamer::Getlogin()
{
    return time;
}

int gamer::GetTimes(int i)
{
    if (i == 1)
        return game1;
    else if (i == 2)
        return game2;
    else if (i == 0)
        return (game1 + game2);
    else
        return 0;
}

int gamer::GetBest(int u)
{
    if (u == 1)
        return best1;
    else if (u == 2)
        return best2;
    else
        return 0;
}

void Game::Setgrade(int i)
{
    grade = i;
}

int Game::Getgrade()
{
    return grade;
}

void Game::gotoxy(int x, int y)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //获取句柄
    COORD poos = {(short)x, (short)y};
    SetConsoleCursorPosition(hOut, poos); //移动光标
}

void Game::cleanScreen()
{
    DWORD res;
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo(hOut, &bInfo);
    COORD home = {0, 0};
    WORD att = bInfo.wAttributes;
    unsigned long size = bInfo.dwSize.X * bInfo.dwSize.Y;
    FillConsoleOutputAttribute(hOut, att, size, home, &res);
    FillConsoleOutputCharacter(hOut, ' ', size, home, &res);
    SetConsoleCursorPosition(hOut, home);
}