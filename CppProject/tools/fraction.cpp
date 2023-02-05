#ifndef FRACTION_CPP_CPP
#define FRACTION_CPP_CPP
#include "fraction.h"
#include "BigInt.h"
#include <algorithm>
#include <cmath>
#include <ctime>
namespace {
//一些辅助函数
template <typename T>
Fraction<T> to_Accurate_score(typename Fraction<T>::real_type x) {
    Fraction<T> ans;
    while (fabs(x - T(x)) > Fraction<T>::DefaultEps) {
        x *= 10;
        ans.get_denominator() *= 10;
    }
    ans.get_numerator() = T(x);
    return ans;
}
template <typename T>
Fraction<T> search_Fraction(Fraction<T> l, Fraction<T> r) {
    if (l.get_numerator() < l.get_denominator()) {
        if (r.get_numerator() < r.get_denominator()) {
            swap(l.get_numerator(), l.get_denominator());
            swap(r.get_numerator(), r.get_denominator());
            Fraction<T> ans = search_Fraction(l, r);
            swap(ans.get_numerator(), ans.get_denominator());
            return ans;
        } else {
            return Fraction<T>(1, 1);
        }
    } else {
        T under_num = T(floor(l.get_value()));
        l.get_numerator() -= under_num * l.get_denominator(),
            r.get_numerator() -= under_num * r.get_denominator();
        Fraction<T> ans = search_Fraction<T>(l, r);
        return Fraction<T>(under_num * ans.get_denominator() +
                               ans.get_numerator(),
                           ans.get_denominator());
    }
}
} // namespace
template <typename T> Fraction<T>::Fraction(T _a, T _b) : a(_a), b(_b) {}
template <typename T> Fraction<T>::Fraction(real_type x, real_type eps) {
    member_type i, j;
    for (i = 0; i <= search_max; ++i) { //枚举分子
        j = round(real_type(i) / x);
        real_type now_e = fabs(real_type(i) / j - x);
        if (j != 0 && fabs(real_type(i) / j - x) <= eps) {
            break;
        }
    }
    a=i,b=j;
}
// template <typename T> Fraction<T>::Fraction(real_type x, real_type eps) {
//     (*this) = search_Fraction(to_Accurate_score<T>(x - eps),
//                               to_Accurate_score<T>(x + eps));
// }
#endif