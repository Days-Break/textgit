#ifndef ZOO_H
#define ZOO_H
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
class AnimalFood
{
public:
    int getPeanuts();
    int getCarrots();
    int getBananas();
    void setPeanuts(int);
    void setCarrots(int);
    void setBananas(int);
    void sellPeanuts(int);
    void sellCarrots(int);
    void sellBananas(int);

private:
    int peanuts, carrots, bananas;
};

class AnimaEnclosure
{

public:
    AnimaEnclosure();
    void addDirt(const int);
    void setStatus(const bool);
    bool getStatus();
    bool check();
    int getDays();

private:
    int dirt_level, days;
    bool cur_status;
};

class Animal : public AnimaEnclosure
{
public:
    Animal();
    double getWeight();
    double getAmount();
    void zero();
    virtual void addAmount(const int) = 0;

private:
    double weight, amount_of_food;
};

class Elephant : public Animal
{
public:
    Elephant();
    double getTrunk_length();
    void addAmount(const int);

private:
    double trunk_length;
};

class Giraffe : public Animal
{
public:
    Giraffe();
    double getNeck_length();
    void addAmount(const int);

private:
    double neck_length;
};

class Monkey : public Animal
{
public:
    Monkey();
    double getArm_length();
    void addAmount(const int);

private:
    double arm_length;
};

class Money
{
    friend ostream &operator<<(ostream &, const Money &);
    friend istream &operator>>(istream &, Money &);
    friend Money operator*(const int &, Money &);

public:
    Money(int = 0, int = 0);
    void setMoney(int, int);
    Money getMoney();
    void addMoney(const Money);
    Money operator+(const Money &);
    Money operator-(const Money &);
    Money operator*(const int &);
    Money operator/(const int &);
    int turn();

private:
    int dollar, cent;
};

class Person
{
public:
    Person();
    virtual void setAge();
    void setAge(int);
    void setName();
    string getName();
    int getAge();

private:
    string name;
    int age;
};

class Visitor : public Person
{
public:
    Visitor();
    string getID();
    void setID();

private:
    string passID;
};

class Child : public Visitor, public AnimalFood
{
public:
    Child();
    void setAge();
};
class Adult : public Visitor
{
public:
    Adult();
    ~Adult();
    int getChild();
    int getTo_buy();
    Money getMoneytoSell();
    void ShowChild();

private:
    Child *myChild;
    Money myMoney, paySeller;
    int children, To_buy;
};

class ZooKeeper : public Person
{
public:
    ZooKeeper();
    int getDay_of_clean();
    void addDays();

private:
    int day_of_clean;
};

class FoodSeller : public Person, public AnimalFood, public Money
{
public:
    FoodSeller();
};

class Zoo : public ZooKeeper, public FoodSeller
{
public:
    Zoo();
    void oneday();
    void entire();

private:
    int All_adult, All_child, DAY;
    Elephant myElephant;
    Giraffe myGiraffe;
    Monkey myMonkey;
    Adult *myAdult;
};

#endif