#ifndef GAME_H
#define GAME_H
#include <string>
#include <windows.h>
using namespace std;

enum where
{
    Null,
    Up,
    Down,
    Left,
    Right
};

struct cor
{
    int x, y;
    cor(int a = 0, int b = 0)
    {
        x = a, y = b;
    }
};

class gamer
{
private:
    string name, code, ID, time;
    int game1, game2, best1, best2;

public:
    void Setname(string);
    void SetID(string);
    void SetCode(string);
    void Setlogin(string, string);
    void Setlogin(string);
    void SetTimes(int, int);
    void SetBest(int, int);
    void AddTimes(int);
    string Getlogin();
    string Getname();
    string GetID();
    string GetCode();
    int GetTimes(int);
    int GetBest(int);
};

class Game
{
private:
    int grade;
    //bool flag;

public:
    virtual void init(int) = 0;
    virtual void game_start() = 0;
    void cleanScreen();
    void Setgrade(int);
    int Getgrade();
    // void Setflag(bool);
    // bool Getflag();
    // void SetBest(int);
    // int GetBest();
    void gotoxy(int, int);
    HANDLE hOut, hIn;
};

class Snake : public Game
{
private:
    int speed, len, n, head, tail, seed, p, other;
    int *vis;
    double pay;
    where *map;

public:
    //~Snake();
    void init(int);
    void game_start();
    int go_ahead(int &);
    void go_back();
    void new_seed();
    void draw_ground();
    void turn(int);
};

class Mine : public Game
{
private:
    int num, len, wid, solve;
    double pay;
    int **pos, **vis;

public:
    //~Mine();
    void init(int);
    void game_start();
    void gride();
    void showclear();
    void clear(int, int);
    void tip(int, int);
};

#endif
