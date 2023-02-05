#ifndef FRACTION_H_
#define FRACTION_H_
#include "BigInt.h"
#include <cmath>
template <typename T> class Fraction {
  public:
    typedef double real_type;
    typedef T member_type;
    static const T search_max = T(1000000);
    constexpr static const real_type DefaultEps = real_type(1) / search_max;

  private:
    T a, b; //表示a/b
  public:
    //构造函数&解析函数
    Fraction(T _a = T(0), T _b = T(1));
    Fraction(real_type x, real_type exp = DefaultEps);
    ~Fraction() = default;

    //重载运算符
    // const Fraction<T> operator+(const Fraction<T>&) const;

    //普通函数
    const T& get_numerator() const { return a; }
    T& get_numerator() { return a; }
    const T& get_denominator() const { return b; }
    T& get_denominator() { return b; }
    real_type get_value() const { return real_type(a) / b; }
};
typedef Fraction<int> fraction;
#endif