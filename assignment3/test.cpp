#include "Matrix.h"
#include <iostream>
using namespace std;
int main()
{
    Matrix M1, M2, M3, M4;
    cout << M1;
    cin >> M1 >> M2 >> M3;
    cout << M1 - M2 << M2 + M3 << M1 * M3;
    M2 = 3 * M1;
    cout << (M1 == M2) << ' ' << (M1 != M3) << '\n';
    M4 = M1 + M2 + M3;
    cout << M4;
    M1 -= M2;
    M2 += M3;
    M3 *= M1;
    cout << M1 << M2 << M3;
    return 0;
}