#ifndef BIGINT_H_
#define BIGINT_H_
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class UnsignedBigInt {
  public:
    typedef unsigned int value_type;
    typedef vector<value_type>::size_type size_type;
    typedef unsigned long long maxinteger_type;
    typedef int mode_type;
    enum strict_mode : mode_type {
        UnsignedBigIntUnUseStrict,
        UnsignedBigIntUseStrict
    };
    static const mode_type default_strict_mode =
        strict_mode::UnsignedBigIntUseStrict;

  private:
    vector<value_type> val; //值，每位一个数字，采用顺序存储
    mode_type isstrict;     //是否开启严格模式
  private:
  public:
    //构造函数&解析函数
    UnsignedBigInt();
    UnsignedBigInt(string& s, mode_type _strict = default_strict_mode);
    UnsignedBigInt(string&& s, mode_type _strict = default_strict_mode);
    UnsignedBigInt(const maxinteger_type _val,
                   mode_type _strict = default_strict_mode);
    UnsignedBigInt(const vector<value_type>& val,
                   mode_type _strict = default_strict_mode);
    UnsignedBigInt(const vector<value_type>&& val,
                   mode_type _strict = default_strict_mode);
    ~UnsignedBigInt() = default;
    //类型转换函数
    inline explicit operator bool() const { return !val.empty(); }
    explicit operator string() const;
    explicit operator maxinteger_type() const;
    //普通函数
    const UnsignedBigInt factorial() const; //返回自己的阶乘
    const maxinteger_type
    value() const; //转换成整型，用普通函数避免任何意外，注意数太大会越界
    void set_strict(strict_mode _strict); //设置严格模式
    strict_mode using_strict() const;     //返回是否是严格模式
    //重载算术运算符
    const UnsignedBigInt operator+(const UnsignedBigInt&) const;
    const UnsignedBigInt operator+(const UnsignedBigInt&&) const;
    const UnsignedBigInt operator-(const UnsignedBigInt&) const;
    const UnsignedBigInt operator-(const UnsignedBigInt&&) const;
    const UnsignedBigInt operator*(const UnsignedBigInt&) const;
    const UnsignedBigInt operator*(const UnsignedBigInt&&) const;
    const UnsignedBigInt operator/(const UnsignedBigInt&) const;
    const UnsignedBigInt operator/(const UnsignedBigInt&&) const;
    const UnsignedBigInt operator%(const UnsignedBigInt&) const;
    const UnsignedBigInt operator%(const UnsignedBigInt&&) const;
    const UnsignedBigInt operator^(const maxinteger_type&)
        const; //快速幂，选用ull是因为到这里vector的size已经到极限了。
    const UnsignedBigInt operator^(const maxinteger_type&&)
        const; //快速幂，选用ull是因为到这里vector的size已经到极限了。
    inline const UnsignedBigInt operator+=(const UnsignedBigInt& a) {
        return ((*this) = (*this) + a);
    }
    inline const UnsignedBigInt operator+=(const UnsignedBigInt&& a) {
        return ((*this) = (*this) + a);
    }
    inline const UnsignedBigInt operator-=(const UnsignedBigInt& a) {
        return ((*this) = (*this) - a);
    }
    inline const UnsignedBigInt operator-=(const UnsignedBigInt&& a) {
        return ((*this) = (*this) - a);
    }
    inline const UnsignedBigInt operator*=(const UnsignedBigInt& a) {
        return ((*this) = (*this) * a);
    }
    inline const UnsignedBigInt operator*=(const UnsignedBigInt&& a) {
        return ((*this) = (*this) * a);
    }
    inline const UnsignedBigInt operator/=(const UnsignedBigInt& a) {
        return ((*this) = (*this) / a);
    }
    inline const UnsignedBigInt operator/=(const UnsignedBigInt&& a) {
        return ((*this) = (*this) / a);
    }
    inline const UnsignedBigInt operator%=(const UnsignedBigInt& a) {
        return ((*this) = (*this) % a);
    }
    inline const UnsignedBigInt operator%=(const UnsignedBigInt&& a) {
        return ((*this) = (*this) % a);
    }
    inline const UnsignedBigInt operator^=(const maxinteger_type& a) {
        return ((*this) = (*this) ^ a);
    }
    inline const UnsignedBigInt operator^=(const maxinteger_type&& a) {
        return ((*this) = (*this) ^ a);
    }

    inline const UnsignedBigInt operator++() { return ((*this) += 1U); }
    inline const UnsignedBigInt operator++(int) {
        auto res = (*this);
        ++(*this);
        return res;
    }
    //重载比较运算符
    bool operator<(const UnsignedBigInt&) const;
    bool operator<=(const UnsignedBigInt&) const;
    inline bool operator>(const UnsignedBigInt& a) const {
        return !((*this) <= a);
    }
    inline bool operator>=(const UnsignedBigInt& a) const {
        return !((*this) < a);
    }
    bool operator==(const UnsignedBigInt&) const;
    inline bool operator!=(const UnsignedBigInt& a) const {
        return !((*this) == a);
    }
};
inline ostream& operator<<(ostream& os, const UnsignedBigInt& a) {
    os << string(a);
    return os;
}
inline ostream& operator<<(ostream& os, const UnsignedBigInt&& a) {
    os << string(a);
    return os;
}
istream& operator>>(istream& is, UnsignedBigInt& a);
istream& operator>>(istream& is, UnsignedBigInt&& a);
const UnsignedBigInt qpow(const UnsignedBigInt& a, const UnsignedBigInt& b,
                          const UnsignedBigInt& p);
class BigInt {
  public:
    typedef UnsignedBigInt::value_type value_type;
    typedef UnsignedBigInt::size_type size_type;
    typedef make_signed<UnsignedBigInt::maxinteger_type>::type maxinteger_type;
    typedef UnsignedBigInt::strict_mode strict_mode;
    typedef UnsignedBigInt::mode_type mode_type;

  private:
    UnsignedBigInt val; //值，每位一个数字，采用顺序存储
    bool sign;          //符号，0正数1负数
  private:
    inline void turn_sign() {
        if (val == 0)
            sign = false;
    }

  public:
    //构造函数&解析函数
    BigInt();
    BigInt(string& s, mode_type _strict = UnsignedBigInt::default_strict_mode);
    BigInt(string&& s, mode_type _strict = UnsignedBigInt::default_strict_mode);
    BigInt(maxinteger_type _val,
           mode_type _strict = UnsignedBigInt::default_strict_mode);
    BigInt(const UnsignedBigInt&);
    BigInt(UnsignedBigInt&&) noexcept;
    ~BigInt() {}
    //类型转换函数
    inline explicit operator bool() const { return bool(val); }
    explicit operator string() const;
    explicit operator UnsignedBigInt() const;
    explicit operator maxinteger_type() const;
    //普通函数
    bool isnegative() const;              //返回是否为负数
    const BigInt factorial() const;       //返回自己的阶乘
    void set_strict(strict_mode _strict); //设置严格模式
    strict_mode using_strict() const;     //返回模式
    //重载算术运算符
    const BigInt operator-() const;
    const BigInt operator+(const BigInt&) const;
    const BigInt operator+(const BigInt&&) const;
    const BigInt operator-(const BigInt&) const;
    const BigInt operator-(const BigInt&&) const;
    const BigInt operator*(const BigInt&) const;
    const BigInt operator*(const BigInt&&) const;
    const BigInt operator/(const BigInt&) const;
    const BigInt operator/(const BigInt&&) const;
    const BigInt operator%(const BigInt&) const;
    const BigInt operator%(const BigInt&&) const;
    const BigInt operator^(const maxinteger_type&) const;
    const BigInt operator^(const maxinteger_type&&) const;
    inline const BigInt operator+=(const BigInt& a) {
        return ((*this) = (*this) + a);
    }
    inline const BigInt operator+=(const BigInt&& a) {
        return ((*this) = (*this) + a);
    }
    inline const BigInt operator-=(const BigInt& a) {
        return ((*this) = (*this) - a);
    }
    inline const BigInt operator-=(const BigInt&& a) {
        return ((*this) = (*this) - a);
    }
    inline const BigInt operator*=(const BigInt& a) {
        return ((*this) = (*this) * a);
    }
    inline const BigInt operator*=(const BigInt&& a) {
        return ((*this) = (*this) * a);
    }
    inline const BigInt operator/=(const BigInt& a) {
        return ((*this) = (*this) / a);
    }
    inline const BigInt operator/=(const BigInt&& a) {
        return ((*this) = (*this) / a);
    }
    inline const BigInt operator%=(const BigInt& a) {
        return ((*this) = (*this) % a);
    }
    inline const BigInt operator%=(const BigInt&& a) {
        return ((*this) = (*this) % a);
    }
    inline const BigInt operator^=(const maxinteger_type& a) {
        return ((*this) = (*this) ^ a);
    }
    inline const BigInt operator^=(const maxinteger_type&& a) {
        return ((*this) = (*this) ^ a);
    }
    inline const BigInt operator++() { return ((*this) += 1U); }
    inline const BigInt operator++(int) {
        auto res = (*this);
        ++(*this);
        return res;
    }
    //重载比较运算符
    bool operator<(const BigInt&) const;
    bool operator<(const BigInt&&) const;
    bool operator<=(const BigInt&) const;
    bool operator<=(const BigInt&&) const;
    bool operator==(const BigInt&) const;
    bool operator==(const BigInt&&) const;
    inline bool operator>(const BigInt& a) const { return !((*this) <= a); }
    inline bool operator>(const BigInt&& a) const { return !((*this) <= a); }
    inline bool operator>=(const BigInt& a) const { return !((*this) < a); }
    inline bool operator>=(const BigInt&& a) const { return !((*this) < a); }
    inline bool operator!=(const BigInt& a) const { return !((*this) == a); }
    inline bool operator!=(const BigInt&& a) const { return !((*this) == a); }
};
inline ostream& operator<<(ostream& os, const BigInt& a) {
    os << string(a);
    return os;
}
inline ostream& operator<<(ostream& os, const BigInt&& a) {
    os << string(a);
    return os;
}
istream& operator>>(istream& is, BigInt& a);
istream& operator>>(istream& is, BigInt&& a);
const BigInt qpow(const BigInt& a, const BigInt& b, const BigInt& p);
#endif