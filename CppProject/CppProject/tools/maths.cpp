#ifndef _MATHS_CPP
#define _MATHS_CPP
#include "maths.h"
#include "BigInt.cpp"
#include "BigInt.h"
template <typename Double> Double Sqrt(const Double x, const Double j) {
    Double ans = x;
    while (Abs(ans * ans - x) >= j) {
        ans = (x - ans * ans) / (Double(2) * ans) + ans;
    }
    return ans;
}
#endif