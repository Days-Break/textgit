#include "Matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix()
{
    a = d = 1;
    b = c = 0;
}

ostream &operator<<(ostream &output, const Matrix &op2)
{
    output << op2.a << ' ' << op2.b << '\n'
           << op2.c << ' ' << op2.d << '\n';
    return output;
}

istream &operator>>(istream &input, Matrix &op2)
{
    input >> op2.a >> op2.b >> op2.c >> op2.d;
    return input;
}
Matrix Matrix::operator+(const Matrix &op2)
{
    Matrix tmp;
    tmp.a = a + op2.a;
    tmp.b = b + op2.b;
    tmp.c = c + op2.c;
    tmp.d = d + op2.d;
    return tmp;
}

Matrix Matrix::operator-(const Matrix &op2)
{
    Matrix tmp;
    tmp.a = a - op2.a;
    tmp.b = b - op2.b;
    tmp.c = c - op2.c;
    tmp.d = d - op2.d;
    return tmp;
}

Matrix Matrix::operator*(const Matrix &op2)
{
    Matrix tmp;
    tmp.a = a * op2.a + b * op2.c;
    tmp.b = a * op2.b + b * op2.d;
    tmp.c = c * op2.a + d * op2.c;
    tmp.d = c * op2.b + d * op2.d;
    return tmp;
}

Matrix Matrix::operator*(const long double &op2)
{
    Matrix tmp;
    tmp.a = a * op2;
    tmp.b = b * op2;
    tmp.c = c * op2;
    tmp.d = d * op2;
    return tmp;
}

Matrix Matrix::operator*(const int &op2)
{
    Matrix tmp;
    tmp.a = a * op2;
    tmp.b = b * op2;
    tmp.c = c * op2;
    tmp.d = d * op2;
    return tmp;
}

Matrix operator*(const long double &op1, Matrix &op2)
{
    return op2 * op1;
}

Matrix operator*(const int &op1, Matrix &op2)
{
    return op2 * op1;
}

Matrix Matrix::operator=(const Matrix &op2)
{
    a = op2.a;
    b = op2.b;
    c = op2.c;
    d = op2.d;
    return *this;
}

Matrix Matrix::operator+=(const Matrix &op2)
{
    return *this + op2;
}

Matrix Matrix::operator-=(const Matrix &op2)
{
    return *this - op2;
}

Matrix Matrix::operator*=(const Matrix &op2)
{
    return *this * op2;
}

bool Matrix::operator==(const Matrix &op2) const
{
    if (a == op2.a && b == op2.b && c == op2.c && d == op2.d)
        return true;
    else
        return false;
}

bool Matrix::operator!=(const Matrix &op2) const
{
    return !(*this == op2);
}
