#ifndef FRACTION_H_
#define FRACTION_H_
#include "BigInt.h"
#include <cmath>
template <typename T> class Fraction {
  public:
    typedef double real_type;
    typedef T member_type;

  private:
    T a, b; //表示a/b
  public:
    //构造函数&解析函数
    Fraction(T _a = T(), T _b = T());
    Fraction(real_type x);
    ~Fraction() = default;

    const Fraction operator+(const Fraction&) const;
};
typedef Fraction<int> fraction;
typedef Fraction<UnsignedBigInt> ubigfraction;
typedef Fraction<BigInt> bigfraction;
#endif