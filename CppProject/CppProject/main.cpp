#include "tools/BigInt.cpp"
#include "tools/BigInt.h"
#include "tools/maths.cpp"
#include "tools/matrix.cpp"
#include <cmath>
#include <ctime>
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    // BigInt a;
    // cin >> a;
    // cout << "sqrt(" << a << ")=" << Sqrt(a);
    BigInt a;
    BigInt::maxinteger_type b;
    cin >> a >> b;
    cout << a << "^" << b << "=";
    cout << (a^b);
    return 0;
}
