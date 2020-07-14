#include "game.h"
#include <algorithm>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
bool online;
int counter;
struct Rank
{
    int grade;
    string name;
    bool operator>(Rank &a)
    {
        return grade > a.grade;
    }
    void Set(int a, string b)
    {
        grade = a;
        name = b;
    }
};
bool cmp(Rank a, Rank b)
{
    return a > b;
}
vector<Rank> q1, q2;
char tu[1024], tmp[256];
gamer preson;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO bInfo;
CONSOLE_CURSOR_INFO CursoleInfo;
void HideCursor()
{
    GetConsoleCursorInfo(hOut, &CursoleInfo);
    CursoleInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &CursoleInfo);
}
void ShowCursor()
{
    GetConsoleCursorInfo(hOut, &CursoleInfo);
    CursoleInfo.bVisible = true;
    SetConsoleCursorInfo(hOut, &CursoleInfo);
}
void cleanScreen()
{

    GetConsoleScreenBufferInfo(hOut, &bInfo);
    COORD home = {0, 0};
    DWORD res;
    WORD att = bInfo.wAttributes;
    unsigned long size = bInfo.dwSize.X * bInfo.dwSize.Y;
    FillConsoleOutputAttribute(hOut, att, size, home, &res);
    FillConsoleOutputCharacter(hOut, ' ', size, home, &res);
    SetConsoleCursorPosition(hOut, home);
}
string CharToStr(char *yy)
{
    string tempStr;
    for (int i = 0; yy[i] != '\0'; i++)
    {
        tempStr += yy[i];
    }
    return tempStr;
}

int main()
{
    GetConsoleScreenBufferInfo(hOut, &bInfo);
    // COORD size = {120, 35};
    // SetConsoleScreenBufferSize(hOut, size);
    SMALL_RECT rc = {0, 1, 120, 35};
    WORD att2 = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    WORD att3 = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    WORD att4 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    HideCursor();
    fstream my_file, yourfile, history, infile;
    my_file.open("E:\\testgit\\practical_training\\login.txt", ios::in | ios::app);
    yourfile.open("E:\\testgit\\practical_training\\message.txt", ios::in | ios::out);
    history.open("E:\\testgit\\practical_training\\history.txt", ios::in | ios::app);
    infile.open("E:\\testgit\\practical_training\\readme.txt", ios::in);
    while (1)
    {
        SetConsoleTitle("C++游戏盒 ver1.1");
        SetConsoleWindowInfo(hOut, true, &rc);
        SetConsoleTextAttribute(hOut, att2);
        printf("\n\n\n\n\n\n———————————————————————欢迎来到ZKHの游戏盒！！————————————————————\n\n");
        printf("———————————————————— 本游戏盒中有贪吃蛇，扫雷两款游戏！—————————————————\n\n");
        printf("————————————————————————— 请你选择—————————————————————————\n\n");
        printf("—————————————————————————1.开始游戏 ————————————————————————\n\n");
        printf("—————————————————————————2.用户登录 ————————————————————————\n\n");
        printf("—————————————————————————3.游戏说明 ————————————————————————\n\n");
        printf("—————————————————————————4.信息查看 ————————————————————————\n\n");
        printf("—————————————————————————5.退出游戏 ————————————————————————\n\n\n\n\n\n\n");
        char ch = _getch();
        cleanScreen();
        if (ch == '1')
        {
            printf("—————————————————选择你想玩的游戏吧！(A.贪吃蛇 B.扫雷) ————————————————\n\n");
            ch = _getch();
            if (ch == 'A' || ch == 'a')
            {
                printf("—————————————————————那让我们愉悦地开始吧！————————————————————\n");
                printf("\n\n请按任意键确认QAQ\n");
                _getch();
                cleanScreen();
                while (1)
                {
                    SetConsoleTitle("贪吃蛇");
                    Snake she;
                    while (1)
                    {

                        printf("\n\n\n\n\n————————————————— 哈啰！你现在玩的是贪吃蛇游戏哦!————————————————\n\n");
                        printf("———————————————————请使用WSAD控制小蛇运动！——————————————————\n\n");
                        printf("———————————选择你想要的难度吧：(A:简易难度 B : 正常难度 C : 专家难度)————————— \n ");
                        ch = _getch();
                        if (ch == 'A' || ch == 'a')
                        {
                            she.init(1);
                            break;
                        }
                        else if (ch == 'B' || ch == 'b')
                        {
                            if (online == 0)
                            {
                                printf("\n\n\n\n\n——————————————————很抱歉，游客没有权限进入喔！—————————————————\n\n");
                                printf("—————————————————————请登录后再来吧^^————————————————————\n\n\n\n\n\n");
                                _getch();
                            }
                            else if (preson.GetBest(1) < 200)
                            {
                                printf("\n\n\n\n\n——————————————————很抱歉，您的最高分数不够喔！—————————————————\n\n");
                                printf("—————————————————— 请达成200分的小目标再来吧^^—————————————————\n\n\n\n\n\n");
                                _getch();
                            }
                            else
                            {
                                she.init(2);
                                break;
                            }
                        }
                        else if (ch == 'C' || ch == 'c')
                        {
                            if (online == 0)
                            {
                                printf("\n\n\n\n\n——————————————————很抱歉，游客没有权限进入喔！—————————————————\n\n");
                                printf("—————————————————————请登录后再来吧^^————————————————————\n\n\n\n\n\n");
                                _getch();
                            }
                            else if (preson.GetBest(1) < 400)
                            {
                                printf("\n\n\n\n\n——————————————————很抱歉，您的最高分数不够喔！—————————————————\n\n");
                                printf("—————————————————— 请达成400分的小目标再来吧^^—————————————————\n\n\n\n\n\n");
                                _getch();
                            }
                            else
                            {
                                she.init(3);
                                break;
                            }
                        }
                        cleanScreen();
                    }
                    cleanScreen();
                    she.game_start();
                    if (online == 1)
                    {
                        preson.AddTimes(1);
                        if (she.Getgrade() > preson.GetBest(1))
                        {
                            preson.SetBest(she.Getgrade(), preson.GetBest(2));
                        }
                        time_t timep;
                        time(&timep);
                        memset(tmp, 0, sizeof(tmp));
                        strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
                        history.clear();
                        history.seekg(0, ios::end);
                        history << tmp << " " << preson.Getname() << "玩了贪吃蛇，获得" << she.Getgrade() << "分\n";
                    }
                    printf("————————————————请按任意键继续———————————————\n\n");
                    _getch();
                    printf("———————————————还想再玩一次嘛?(Y/N)—————————————\n\n");
                    char t = _getch();
                    if (t != 'Y' && t != 'y')
                    {
                        printf("——————————————请按任意键返回主菜单——————————————\n");
                        _getch();
                        break;
                    }
                    cleanScreen();
                }
            }
            else if (ch == 'B' || ch == 'b')
            {
                printf("—————————————————————那让我们愉悦地开始吧！————————————————————\n");
                printf("\n\n请按任意键确认QAQ\n");
                _getch();
                cleanScreen();
                while (1)
                {
                    SetConsoleTitle("扫雷");
                    Mine mi;
                    while (1)
                    {

                        printf("\n\n\n\n\n————————————————————你现在玩的是扫雷哦————————————————————\n\n");
                        printf("—————————————————————请你选择难度吧—————————————————————\n\n");
                        printf("———————————————————A.青铜 B.铂金 C.王者————————————————————\n\n");
                        ch = _getch();
                        if (ch == 'A' || ch == 'a')
                        {
                            mi.init(1);
                            break;
                        }
                        else if (ch == 'B' || ch == 'b')
                        {
                            if (online == 0)
                            {
                                printf("\n\n\n\n\n————————————————————很抱歉，游客没有权限进入喔！——————————————————\n\n");
                                printf("———————————————————————请登录后再来吧^^—————————————————————\n\n\n\n\n\n");
                                _getch();
                            }
                            else if (preson.GetBest(2) < 100)
                            {
                                printf("\n\n\n\n\n——————————————————很抱歉，您的最高分数不够喔！—————————————————\n\n");
                                printf("—————————————————— 请达成100分的小目标再来吧^^—————————————————\n\n\n\n\n\n");
                                _getch();
                            }
                            else
                            {
                                mi.init(2);
                                break;
                            }
                        }
                        else if (ch == 'C' || ch == 'c')
                        {
                            if (online == 0)
                            {
                                printf("\n\n\n\n\n————————————————————很抱歉，游客没有权限进入喔！——————————————————\n\n");
                                printf("———————————————————————请登录后再来吧^^—————————————————————\n\n\n\n\n\n");
                                _getch();
                            }
                            else if (preson.GetBest(2) < 600)
                            {
                                printf("\n\n\n\n\n——————————————————很抱歉，您的最高分数不够喔！—————————————————\n\n");
                                printf("—————————————————— 请达成600分的小目标再来吧^^—————————————————\n\n\n\n\n\n");
                                _getch();
                            }
                            else
                            {
                                mi.init(3);
                                break;
                            }
                        }
                        cleanScreen();
                    }
                    cleanScreen();
                    mi.game_start();
                    if (online == 1)
                    {
                        preson.AddTimes(2);
                        if (mi.Getgrade() > preson.GetBest(2))
                        {
                            preson.SetBest(preson.GetBest(1), mi.Getgrade());
                        }
                        time_t timep;
                        time(&timep);
                        memset(tmp, 0, sizeof(tmp));
                        strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
                        history.clear();
                        history.seekg(0, ios::end);
                        history << tmp << " " << preson.Getname() << "玩了扫雷，获得" << mi.Getgrade() << "分\n";
                    }
                    printf("————————————————请按任意键继续———————————————\n\n");
                    _getch();
                    printf("———————————————还想再玩一次嘛?(Y/N)—————————————\n\n");
                    char t = _getch();
                    if (t != 'y' && t != 'Y')
                    {
                        printf("——————————————请按任意键返回主菜单——————————————\n");
                        _getch();
                        break;
                    }
                    cleanScreen();
                }
            }
            else
            {
                printf("—————————————————————很抱歉喔！输入不对！—————————————————————\n\n");
                printf("——————————————————————请您重新输入吧！——————————————————————\n\n");
                _getch();
            }
        }
        else if (ch == '2')
        {
            cleanScreen();
            SetConsoleTextAttribute(hOut, att2);
            string code, name, ID, id, tt, hh, time0, time1;
            int game1, game2, best1, best2;
            while (1)
            {
                cleanScreen();
                printf("\n\n\n\n\n\n\n");
                printf("—————————————————————————— 游客你好喔！——————————————————————\n\n");
                printf("—————————————————————————— 请问您想要———————————————————————\n\n");
                printf("———————————————————————————1.登录 ————————————————————————\n\n");
                printf("———————————————————————————2.注册 ————————————————————————\n\n");
                printf("——————————————————————————3.返回上一层 ——————————————————————\n\n\n\n\n\n");
                ch = _getch();
                cleanScreen();
                if (ch == '1')
                {
                    if (!online)
                    {
                        while (1)
                        {
                            ShowCursor();
                            printf("—————————————————————————用户登录————————————————————————\n\n\n\n");
                            printf("用户名：______________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
                            cin >> ID;
                            cout << "\n";
                            printf("密码：  ______________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
                            cin >> code;
                            cout << "\n";
                            // code = "";
                            // while ((ch = _getch()) != 13)
                            // {
                            //     cout << "*";
                            //     code += ch;
                            //     // if (ch == '\b')
                            //     //     break;
                            // }
                            HideCursor();
                            _getch();
                            printf("\n\n\n\n—————————————                      确定吗？(Y/N)                     ————————————\n\n\n\n\n\n");
                            ch = _getch();
                            if (ch == 'Y' || ch == 'y')
                                break;
                            else
                            {
                                printf("———————         请重新输入哦！        ——————\n");
                                _getch();
                            }
                            cleanScreen();
                        }
                        bool flag1 = 0, flag2 = 0;
                        counter = 0;
                        my_file.clear();
                        my_file.seekg(0, ios::beg);
                        while (!my_file.eof())
                        {
                            my_file >> tt >> hh;
                            if (tt == ID)
                            {
                                flag1 = 1;
                                if (hh == code)
                                {
                                    flag2 = 1;
                                }
                                break;
                            }
                            counter++;
                        }
                        if (!flag1)
                        {
                            printf("———————   抱歉！该用户名不存在哦！    ——————\n");
                            printf("———————         请重新输入吧！        ——————\n");
                            _getch();
                            continue;
                        }
                        if (!flag2)
                        {
                            printf("———————   抱歉！输入密码不正确哦！    ——————\n");
                            printf("———————         请重新输入吧！        ——————\n");
                            _getch();
                            continue;
                        }
                        yourfile.clear();
                        yourfile.seekg(0, ios::beg);
                        for (int i = 0; i < 2 * counter; i++)
                        {
                            yourfile.getline(tu, sizeof(tu)); //读取行。
                        }
                        yourfile >> id >> name >> time0 >> time1;
                        yourfile.get();
                        yourfile >> game1 >> game2 >> best1 >> best2;
                        preson.Setname(name);
                        preson.SetID(id);
                        preson.Setlogin(time0, time1);
                        preson.SetTimes(game1, game2);
                        preson.SetBest(best1, best2);
                        cout << "                                              欢迎回来！ " << preson.Getname() << "\n\n";
                        printf("—————————————————————让我们开始愉悦地玩耍吧！————————————————————\n");
                        _getch();
                        online = true;
                        break;
                    }
                    else
                    {
                        printf("\n\n\n\n");
                        printf("—————————————————————————您已经登录过了喔————————————————————————\n\n\n\n");
                        printf("—————————————————————如果退出，则无法保存当前账号信息————————————————————\n\n\n\n");
                        printf("———————————————————————请问想要重新登录吗?(Y/N)——————————————————————\n\n\n\n");
                        ch = _getch();
                        if (ch == 'Y' || ch == 'y')
                        {
                            online = false;
                            printf("———————————————————————退出成功，请按任意键继续——————————————————————\n");
                        }
                        else
                            printf("———————————————————————请按任意键返回上一层————————————————————————\n");
                        _getch();
                    }
                }
                else if (ch == '2')
                {
                    while (1)
                    {
                        ShowCursor();
                        printf("—————————————————————————新用户注册————————————————————————\n\n\n\n");
                        printf("PS:昵称，用户名请保持在20个字符内哦，密码要在6个数字以上！\n\n\n");
                        printf("昵称：    ______________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
                        cin >> name;
                        cout << "\n";
                        printf("用户名：  ______________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
                        cin >> ID;
                        cout << "\n";
                        printf("密码：    ______________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
                        cin >> code;
                        cout << "\n";
                        // code = "";
                        // while ((ch = _getch()) != 13)
                        // {
                        //     cout << "*";
                        //     code += ch;
                        //     // if (ch == '\b')
                        //     //     break;
                        // }
                        printf("确定密码：______________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
                        cin >> id;
                        cout << "\n";
                        // id = "";
                        // while ((ch = _getch()) != 13)
                        // {
                        //     cout << "*";
                        //     id += ch;
                        //     // if (ch == '\b')
                        //     //     break;
                        // }
                        _getch();
                        HideCursor();
                        printf("\n\n\n\n—————————————                       确定吗？(Y/N)                     ————————————\n\n\n\n\n\n");
                        ch = _getch();
                        if (ch == 'Y' || ch == 'y')
                            break;
                        else
                        {
                            printf("———————         请重新输入哦！        ——————\n");
                            _getch();
                        }
                        cleanScreen();
                    }
                    if (code != id)
                    {
                        printf("———————   两次输入的密码不一样哦！    ——————\n");
                        printf("———————         请重新输入吧！        ——————\n");
                        _getch();
                        continue;
                    }
                    if (code.length() < 6)
                    {
                        printf("———————   密码的字符数少于六个哦！    ——————\n");
                        printf("———————         请重新输入吧！        ——————\n");
                        _getch();
                        continue;
                    }
                    if (name.length() > 20)
                    {
                        printf("———————   昵称的字符数超过20个哦！    ——————\n");
                        printf("———————         请重新输入吧！        ——————\n");
                        _getch();
                        continue;
                    }
                    if (ID.length() > 20)
                    {
                        printf("———————   用户名的字符数超过20个哦！    ——————\n");
                        printf("———————         请重新输入吧！        ——————\n");
                        _getch();
                        continue;
                    }
                    bool flag0 = 0;
                    counter = 0;
                    my_file.clear();
                    my_file.seekg(0, ios::beg);
                    while (!my_file.eof())
                    {
                        my_file >> tt >> hh;
                        if (tt == ID)
                        {
                            flag0 = 1;
                            break;
                        }
                        counter++;
                    }
                    if (flag0)
                    {
                        printf("———————   该用户名已经被注册过了哦！    ——————\n");
                        printf("———————         请重新输入吧！        ——————\n");
                        _getch();
                        continue;
                    }
                    printf("—————————————                恭喜你呀！你已经注册成功啦！             ————————————\n");
                    printf("—————————————                 让我们一起开心地玩耍吧！！              ————————————\n");
                    time_t timep;
                    time(&timep);
                    memset(tmp, 0, sizeof(tmp));
                    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
                    my_file.clear();
                    my_file.seekp(0, ios::end);
                    yourfile.clear();
                    yourfile.seekp(0, ios::end);
                    my_file << ID << " " << code << "\n";
                    yourfile << ID << " " << name << " " << tmp;
                    yourfile << "\n";
                    yourfile << "0 0 0 0";
                    yourfile << "\n";
                    // preson.Setname(name);
                    // preson.SetID(ID);
                    // preson.Setlogin(tmp);
                    // preson.SetTimes(0, 0);
                    // preson.SetBest(0, 0);
                    // online = true;
                    _getch();
                }
                else if (ch == '3')
                {
                    break;
                }
            }
            HideCursor();
        }
        else if (ch == '3')
        {
            // SetConsoleOutputCP(936);
            SetConsoleTextAttribute(hOut, att3);
            printf("————————————————请按任意键继续———————————————\n......\n");
            _getch();
            cleanScreen();
            string str;
            infile.clear();
            infile.seekg(0, ios::beg);
            while (getline(infile, str))
            {
                cout << str << "\n\n";
            }
            _getch();
        }
        else if (ch == '4')
        {
            SetConsoleTextAttribute(hOut, att4);
            if (!online)
            {
                printf("\n\n\n\n\n—————————————————————很抱歉，您还没有登录喔！———————————————————\n");
                printf("———————————————————————请登录后再来吧^^—————————————————————\n\n\n\n\n\n");
                printf("—————————————————————请按任意键返回主菜单—————————————————————\n");
                _getch();
            }
            else
            {
                while (1)
                {
                    printf("\n\n\n\n\n");
                    cout << "                                                 欢迎回来！ " << preson.Getname() << "\n\n";
                    printf("————————————————————————— 请你选择—————————————————————————\n\n");
                    printf("—————————————————————————1.个人信息 ————————————————————————\n\n");
                    printf("—————————————————————————2.历史记录 ————————————————————————\n\n");
                    printf("—————————————————————————3.世界排行榜 ———————————————————————\n\n");
                    printf("—————————————————————————4.返回上一层 ———————————————————————\n");
                    printf("\n\n\n\n\n");
                    ch = _getch();
                    cleanScreen();
                    if (ch == '1')
                    {
                        printf("—————————————————————————用户信息————————————————————————\n\n\n");
                        cout << "用户昵称：\t\t" << preson.Getname() << "\n\n";
                        cout << "用户名：\t\t" << preson.GetID() << "\n\n";
                        cout << "注册时间：\t\t" << preson.Getlogin() << "\n\n";
                        cout << "游戏总次数：\t\t" << preson.GetTimes(0) << "\n\n";
                        cout << "贪吃蛇次数：\t\t" << preson.GetTimes(1) << "\n\n";
                        cout << "最佳成绩：\t\t" << preson.GetBest(1) << "\n\n";
                        cout << "扫雷次数：\t\t" << preson.GetTimes(2) << "\n\n";
                        cout << "最佳成绩：\t\t" << preson.GetBest(2) << "\n\n";
                        _getch();
                        printf("\n\n——————————————————————————E.N.D.————————————————————————\n");
                        printf("\n\n\n\n");
                        printf("————————————————————————请按任意键返回——————————————————————\n");
                        _getch();
                    }
                    else if (ch == '2')
                    {
                        printf("—————————————————————————历史记录————————————————————————\n\n\n");
                        string str;
                        history.clear();
                        history.seekg(0, ios::beg);
                        while (getline(history, str))
                        {
                            cout << str << "\n\n";
                        }
                        _getch();
                        printf("\n\n——————————————————————————E.N.D.————————————————————————\n");
                        printf("\n\n\n\n");
                        printf("————————————————————————请按任意键返回——————————————————————\n");
                        _getch();
                    }
                    else if (ch == '3')
                    {
                        q1.clear();
                        q2.clear();
                        string Data1 = "", Data2 = "";
                        int line = 0;
                        char tmpData[1024] = {0};
                        yourfile.clear();
                        yourfile.seekg(0, ios::beg);
                        while (yourfile.getline(tmpData, sizeof(tmpData)))
                        {
                            if (line < 2 * counter + 1)
                            {
                                Data1 += CharToStr(tmpData);
                                Data1 += "\n";
                            }
                            else if (line > 2 * counter + 1)
                            {
                                Data2 += CharToStr(tmpData);
                                Data2 += "\n";
                            }
                            line++;
                        }
                        ofstream out;
                        out.open("E:\\testgit\\practical_training\\message.txt");
                        out.flush();
                        out << Data1;
                        out << preson.GetTimes(1) << " " << preson.GetTimes(2) << " " << preson.GetBest(1) << " " << preson.GetBest(2) << "\n";
                        out << Data2;
                        out.close();
                        int sum = 0, a1, a2, a3, a4;
                        string s1, s2, s3, s4;
                        Rank k1, k2;
                        my_file.clear();
                        my_file.seekg(0, ios::beg);
                        while (getline(my_file, s1))
                        {
                            sum++;
                        }
                        yourfile.clear();
                        yourfile.seekg(0, ios::beg);
                        for (int i = 0; i < sum; i++)
                        {
                            yourfile >> s1 >> s2 >> s3 >> s4;
                            yourfile.get();
                            yourfile >> a1 >> a2 >> a3 >> a4;
                            yourfile.get();
                            k1.Set(a3, s2);
                            k2.Set(a4, s2);
                            q1.push_back(k1);
                            q2.push_back(k2);
                        }
                        sort(q1.begin(), q1.end(), cmp);
                        sort(q2.begin(), q2.end(), cmp);
                        while (1)
                        {
                            printf("\n\n\n\n\n");
                            printf("————————————————————————— 请你选择 ———————————————————————————\n\n");
                            printf("————————————————————————— 1.贪吃蛇排行榜 ————————————————————————\n\n");
                            printf("————————————————————————— 2.扫雷排行榜 —————————————————————————\n\n");
                            printf("————————————————————————— 3.返回上一层 —————————————————————————\n");
                            ch = _getch();
                            cleanScreen();
                            if (ch == '1')
                            {
                                printf("——————————————————————贪吃蛇排行榜——————————————————————\n\n\n");
                                printf("|\t\t名次\t\t|\t\t昵称\t\t|\t\t得分\t\t|\n\n");
                                for (int i = 0; i < sum; i++)
                                    cout << "|\t\t" << i + 1 << "\t\t|\t\t" << q1[i].name << "\t\t|\t\t" << q1[i].grade << "\t\t|\n\n";
                                _getch();
                                printf("\n\n———————————————————————E.N.D.————————————————————————\n");
                                printf("\n\n\n\n");
                                printf("—————————————————————请按任意键返回——————————————————————\n");
                                _getch();
                            }
                            else if (ch == '2')
                            {
                                printf("——————————————————————扫雷排行榜————————————————————————\n\n\n");
                                printf("|\t\t名次\t\t|\t\t昵称\t\t|\t\t得分\t\t|\n\n");
                                for (int i = 0; i < sum; i++)
                                    cout << "|\t\t" << i + 1 << "\t\t|\t\t" << q2[i].name << "\t\t|\t\t" << q2[i].grade << "\t\t|\n\n";
                                _getch();
                                printf("\n\n———————————————————————E.N.D.————————————————————————\n");
                                printf("\n\n\n\n");
                                printf("—————————————————————请按任意键返回——————————————————————\n");
                                _getch();
                            }
                            else if (ch == '3')
                            {
                                break;
                            }
                            cleanScreen();
                        }
                    }
                    else if (ch == '4')
                    {
                        break;
                    }
                    cleanScreen();
                }
            }
        }
        else if (ch == '5')
        {
            printf("\n\n\n\n\n\n——————————————————————感谢您游玩本游戏！——————————————————————\n\n");
            printf("———————————————————您的喜欢就是对我最大的支持！————————————————————\n\n\n\n\n\n");
            my_file.close();
            infile.close();
            history.close();
            string Data1 = "", Data2 = "";
            int line = 0;
            char tmpData[1024] = {0};
            yourfile.clear();
            yourfile.seekg(0, ios::beg);
            while (yourfile.getline(tmpData, sizeof(tmpData)))
            {
                if (line < 2 * counter + 1)
                {
                    Data1 += CharToStr(tmpData);
                    Data1 += "\n";
                }
                else if (line > 2 * counter + 1)
                {
                    Data2 += CharToStr(tmpData);
                    Data2 += "\n";
                }
                line++;
            }
            //_getch();
            yourfile.close();
            ofstream out;
            out.open("E:\\testgit\\practical_training\\message.txt");
            out.flush();
            out << Data1;
            out << preson.GetTimes(1) << " " << preson.GetTimes(2) << " " << preson.GetBest(1) << " " << preson.GetBest(2) << "\n";
            out << Data2;
            out.close();
            //cleanScreen();
            // string str;
            // yourfile.open("E:\\testgit\\practical_training\\message.txt", ios::in);
            // yourfile.clear();
            // yourfile.seekg(0, ios::beg);
            // while (getline(yourfile, str))
            // {
            //     cout << str << '\n';
            // }
            // yourfile.close();
            Sleep(1000);
            break;
        }
        cleanScreen();
    }
    return 0;
}