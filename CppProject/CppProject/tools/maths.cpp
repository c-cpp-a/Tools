#ifndef _MATHS_CPP
#define _MATHS_CPP
#include "maths.h"
template <typename Double> Double Sqrt(const Double x) {
    Double ans=x;
    while (Abs(ans * ans - x) >= _sqrt_double) {
        ans = (x - ans * ans) / (2 * ans) + ans;
    }
    return ans;
}
#endif