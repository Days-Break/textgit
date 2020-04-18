#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
class Matrix
{
    friend std::ostream &operator<<(std::ostream &, const Matrix &);
    friend std::istream &operator>>(std::istream &, Matrix &);
    friend Matrix operator*(const long double &, Matrix &);
    friend Matrix operator*(const int &, Matrix &);

public:
    Matrix();
    Matrix operator+(const Matrix &);
    Matrix operator-(const Matrix &);
    Matrix operator*(const Matrix &);
    Matrix operator*(const long double &);
    Matrix operator*(const int &);
    Matrix operator=(const Matrix &);
    Matrix operator+=(const Matrix &);
    Matrix operator-=(const Matrix &);
    Matrix operator*=(const Matrix &);
    bool operator==(const Matrix &) const;
    bool operator!=(const Matrix &) const;

private:
    long double a, b, c, d;
};

#endif