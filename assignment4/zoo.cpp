#include "zoo.h"
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

bool flag = 1;
int why = 0;

int AnimalFood::getPeanuts()
{
    return peanuts;
}

int AnimalFood::getCarrots()
{
    return carrots;
}
int AnimalFood::getBananas()
{
    return bananas;
}

void AnimalFood::setPeanuts(int a)
{
    peanuts = a;
}
void AnimalFood::setCarrots(int a)
{
    carrots = a;
}
void AnimalFood::setBananas(int a)
{
    bananas = a;
}

void AnimalFood::sellPeanuts(int a)
{
    peanuts -= a;
    if (peanuts <= 0)
    {
        flag = 0;
        why = 1;
    }
}
void AnimalFood::sellCarrots(int a)
{
    carrots -= a;
    if (carrots <= 0)
    {
        flag = 0;
        why = 2;
    }
}
void AnimalFood::sellBananas(int a)
{
    bananas -= a;
    if (bananas <= 0)
    {
        flag = 0;
        why = 3;
    }
}
AnimaEnclosure::AnimaEnclosure()
{
    dirt_level = days = 0;
    cur_status = 1;
}
void AnimaEnclosure::addDirt(const int a)
{
    dirt_level += a;
}

void AnimaEnclosure::setStatus(const bool a)
{
    cur_status = a;
}

bool AnimaEnclosure::getStatus()
{
    return cur_status;
}
bool AnimaEnclosure::check()
{
    if (dirt_level > 2000)
    {
        setStatus(0);
        dirt_level = 0;
        days++;
        return true;
    }
    return false;
}
int AnimaEnclosure::getDays()
{
    return days;
}
double Animal::getWeight()
{
    return weight;
}

double Animal::getAmount()
{
    return amount_of_food;
}
void Animal::addAmount(const int a)
{
    amount_of_food += a;
    addDirt(a);
}
void Animal::zero()
{
    amount_of_food = 0;
}
Animal::Animal() : AnimaEnclosure()
{
    amount_of_food = 0;

    weight = rand() % 1000;
}

double Elephant::getTrunk_length()
{
    return trunk_length;
}

void Elephant::addAmount(const int a)
{
    Animal::addAmount(a);
    if (getAmount() > 750)
    {
        zero();
    }
}
Elephant::Elephant() : Animal()
{

    trunk_length = rand() % 5 / 10 + 0.2;
}

double Giraffe::getNeck_length()
{
    return neck_length;
}
void Giraffe::addAmount(const int a)
{
    Animal::addAmount(a);
    if (getAmount() > 500)
    {
        zero();
    }
}

Giraffe::Giraffe() : Animal()
{

    neck_length = rand() % 20 / 10 + 1;
}
double Monkey::getArm_length()
{
    return arm_length;
}

void Monkey::addAmount(const int a)
{
    Animal::addAmount(a);
    if (getAmount() > 300)
    {
        zero();
    }
}
Monkey::Monkey() : Animal()
{

    arm_length = rand() % 5 / 10 + 0.5;
}

Money::Money(int a, int b)
{
    dollar = a;
    cent = b;
    if (cent > 100)
    {
        dollar += cent / 100;
        cent %= 100;
    }
    if (cent < 0)
    {
        dollar -= (-cent) / 100 + 1;
        cent += 100 * (b - dollar);
    }
}

Money Money::getMoney()
{
    return *this;
}
void Money::addMoney(const Money a)
{
    *this = getMoney() + a;
}
int Money::turn()
{
    return dollar * 100 + cent;
}
void Money::setMoney(int a, int b)
{
    dollar = a;
    cent = b;
    if (cent > 100)
    {
        dollar += cent / 100;
        cent %= 100;
    }
    if (cent < 0)
    {
        dollar -= (-cent) / 100 + 1;
        cent += 100 * (b - dollar);
    }
}
Money Money::operator+(const Money &a)
{
    dollar += a.dollar;
    cent += a.cent;
    if (cent >= 100)
    {
        dollar++;
        cent -= 100;
    }
    return *this;
}
Money Money::operator-(const Money &a)
{
    dollar -= a.dollar;
    cent -= a.cent;
    if (cent < 0)
    {
        dollar--;
        cent += 100;
    }
    return *this;
}
Money Money::operator*(const int &a)
{
    dollar *= a;
    cent *= a;
    if (cent >= 100)
    {
        dollar += cent / 100;
        cent %= 100;
    }
    return *this;
}
Money Money::operator/(const int &a)
{
    double money = dollar + cent / 100;
    money /= (double)a;
    dollar = (int)money;
    cent = (int)100 * (money - dollar);
    return *this;
}

Money operator*(const int &a, Money &m)
{
    return m * a;
}

ostream &operator<<(ostream &output, const Money &a)
{
    output << '$' << a.dollar << "." << a.cent;
    return output;
}
istream &operator>>(istream &input, Money &a)
{
    input >> a.dollar >> a.cent;
    return input;
}

string Person::getName()
{
    return name;
}
int Person::getAge()
{
    return age;
}

void Person::setName()
{
    name = '\0';

    int n = rand() % 7 + 3;
    for (int i = 0; i < n; i++)
    {
        if (!i)
            name += (char)(65 + rand() % 26);
        else
            name += (char)(97 + rand() % 26);
    }
}
void Person::setAge()
{

    age = 18 + rand() % 50;
}

void Person::setAge(int a)
{
    age = a;
}
Person::Person()
{
    setName();
}
string Visitor::getID()
{
    return passID;
}

void Visitor::setID()
{
    passID = '\0';

    for (int i = 0; i < 9; i++)
        passID += (char)(48 + rand() % 10);
}
Visitor::Visitor()
{
    Person();
    setID();
}
int Adult::getChild()
{
    return children;
}

int Adult::getTo_buy()
{
    return To_buy;
}
Money Adult::getMoneytoSell()
{
    return paySeller;
}

void Adult::ShowChild()
{
    printf("Accompanied by %d kids\n", children);
    for (int j = 0; j < children; j++)
    {
        printf("Child %d : ", j + 1);
        cout << myChild[j].getName() << '\n';
        cout << "Age : " << myChild[j].getAge() << '\t' << "ID : " << myChild[j].getID() << '\n';
    }
}
Adult::Adult()
{
    Visitor();
    Person::setAge();

    int a = rand() % 11 + 10;
    if (a == 20)
        myMoney.setMoney(a, 0);
    else
    {
        int b = rand() % 100;
        myMoney.setMoney(a, b);
    }
    int n = 1 + rand() % 3;
    children = n;
    myChild = new Child[n];
    Money pay(1, 40 * n);
    myMoney = myMoney - pay;
    Money buyFood = myMoney / n;
    To_buy = buyFood.turn();
    paySeller = buyFood * n;
    int aa = To_buy / 20;
    int bb = To_buy / 30;
    int cc = To_buy / 50;
    for (int i = 0; i < n; i++)
    {
        myChild[i].setPeanuts(aa / n);
        myChild[i].setCarrots(bb / n);
        myChild[i].setBananas(cc / n);
    }
}

Adult::~Adult()
{
    delete[] myChild;
}

void Child::setAge()
{

    Person::setAge(rand() % 18 + 1);
}

Child::Child()
{
    Visitor();
    setAge();
    setPeanuts(0);
    setCarrots(0);
    setBananas(0);
}

int ZooKeeper::getDay_of_clean()
{
    return day_of_clean;
}

void ZooKeeper::addDays()
{
    day_of_clean++;
    if (day_of_clean >= 10)
    {
        flag = 0;
        why = 4;
    }
}
ZooKeeper::ZooKeeper() : Person()
{
    Person::setAge();
    day_of_clean = 0;
}

FoodSeller::FoodSeller()
{
    Person::setAge();
    setMoney(0, 0);
    setPeanuts(10000);
    setCarrots(7000);
    setBananas(4000);
}

Zoo::Zoo()
{
    All_adult = All_child = DAY = 0;
    entire();
}

void Zoo::oneday()
{

    int number = 20 + rand() % 21;
    All_adult += number;
    myAdult = new Adult[number];
    for (int i = 0; i < number; i++)
    {
        All_child += myAdult[i].getChild();

        addMoney(myAdult[i].getMoneytoSell());
        int a = myAdult[i].getTo_buy() / 20;
        int b = myAdult[i].getTo_buy() / 30;
        int c = myAdult[i].getTo_buy() / 50;
        if (why != 1)
            sellPeanuts(a);
        if (why != 2)
            sellCarrots(b);
        if (why != 3)
            sellBananas(c);
        if (myElephant.getStatus())
            myElephant.addAmount(a);
        if (myGiraffe.getStatus())
            myGiraffe.addAmount(b);
        if (myMonkey.getStatus())
            myMonkey.addAmount(c);
        cout << "Visitor " << i + 1 << ": " << myAdult[i].getName() << '\n';
        cout << "Age : " << myAdult[i].getAge() << '\t' << "ID :" << myAdult[i].getID() << '\n';
        myAdult[i].ShowChild();
        cout << '\n';
    }
    delete[] myAdult;
    if (myElephant.check())
    {
        addDays();
        return;
    }
    if (myGiraffe.check())
    {
        addDays();
        return;
    }
    if (myMonkey.check())
    {
        addDays();
        return;
    }
}

void Zoo::entire()
{
    srand(time(0));
    while (flag)
    {
        DAY++;
        cout << setfill('-') << setw(20) << "DAY " << DAY << setw(20) << "\n\n";
        oneday();
        if (!myElephant.getStatus())
            myElephant.setStatus(1);
        if (!myGiraffe.getStatus())
            myGiraffe.setStatus(1);
        if (!myMonkey.getStatus())
            myMonkey.setStatus(1);
        cout << '\n';
    }
    printf("The zoo was opended for %d days.\n", DAY);
    printf("The reason why the zoo closed : \n");
    switch (why)
    {
    case 1:
        cout << "The zoo closed because the seller ran out of peanuts." << endl;
        break;
    case 2:
        cout << "The zoo closed because the seller ran out of carrots." << endl;
        break;
    case 3:
        cout << "The zoo closed because the seller ran out of bananas." << endl;
        break;
    case 4:
        cout << "The zoo closed because the zoo keeper had enough of cleaning and quit!" << endl;
        break;
    default:
        break;
    }
    printf("The total number of adult visitors : %d\n", All_adult);
    printf("The total number of children visitors : %d\n", All_child);
    cout << "The foodseller earns : " << getMoney() << '\n';
    printf("the number of days the zoo keeper spent cleaning : %d\n", getDay_of_clean());
    printf("The elephant enclosure was closed for %d days\n", myElephant.getDays());
    printf("The giraffe enclosure was closed for %d days\n", myGiraffe.getDays());
    printf("The monkey enclosure was closed for %d days\n", myMonkey.getDays());
}