#ifndef _MATHS_CPP
#define _MATHS_CPP
#include "maths.h"
#include "BigInt.cpp"
#include "BigInt.h"
#include <exception>
BigInt Abs(const BigInt x) {
    if (x >= BigInt(0))
        return x;
    else
        return -x;
}
UnsignedBigInt Sqrt(UnsignedBigInt x) {
    if (x <= 1)
        return x;
    UnsignedBigInt left = 0, right = x;
    while (left < right) {
        UnsignedBigInt mid = (right + left) / 2;
        if (x / mid >= mid)
            left = mid + 1;
        else
            right = mid;
    }
    return right - 1;
}
BigInt Sqrt(const BigInt x) {
    if (x < 0) {
        cerr << "BigInt Sqrt(const BigInt x):Cannot do sqrt() with "
                "x<0!\n";
        throw exception();
        return BigInt();
    }
    return Sqrt(UnsignedBigInt(x));
}
#endif