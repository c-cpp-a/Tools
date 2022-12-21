#include "tools/BigInt.h"
#include "tools/matrix.cpp"
#include "tools/BigInt.cpp"
#include "tools/maths.cpp"
#include <cmath>
#include <ctime>
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    UnsignedBigInt a,b;
    cin >> a;
    cout << "sqrt(" << a << ")=";
    cout << Sqrt(a,UnsignedBigInt(1));
    return 0;
}
