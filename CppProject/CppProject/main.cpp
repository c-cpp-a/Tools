#include "tools/BigInt.cpp"
#include <ctime>
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    BigInt a;
    cin >> a;
    cout << a << "! =";
    cout << a.factorial();
    return 0;
}
