#include "tools/BigInt.cpp"
#include <ctime>
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    UnsignedBigInt a, b;
    cin >> a >> b;
    cout << a << "*" << b << "=";
    cout << (a * b);
    return 0;
}
