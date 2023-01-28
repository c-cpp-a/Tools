#include "tools/BigInt.cpp"
#include "tools/code.cpp"
#include "tools/maths.cpp"
#include "tools/matrix.cpp"
#include <cmath>
#include <ctime>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
int main() {
    cout << (BigInt(7,BigInt::strict_mode::UnsignedBigIntUnUseStrict)^2010);
    return 0;
}
