#ifndef BIGINT_H_
#define BIGINT_H_
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class UnsignedBigInt {
  public:
    typedef unsigned int value_type;
    typedef vector<value_type>::size_type size_type;
    typedef unsigned long long maxinteger_type;

  private:
    vector<value_type> val; //值，每位一个数字，采用顺序存储
  private:
  public:
    //构造函数&解析函数
    UnsignedBigInt();
    UnsignedBigInt(string& s);
    UnsignedBigInt(string&& s);
    UnsignedBigInt(const maxinteger_type _val);
    UnsignedBigInt(const vector<value_type>& val);
    UnsignedBigInt(const vector<value_type>&& val);
    ~UnsignedBigInt() = default;
    //类型转换函数
    inline explicit operator bool() const { return !val.empty(); }
    explicit operator string() const;
    //普通函数
    const UnsignedBigInt factorial() const; //返回自己的阶乘
    const maxinteger_type
    value() const; //转换成整型，用普通函数避免任何意外，注意数太大会越界
    //重载算术运算符
    const UnsignedBigInt operator+(const UnsignedBigInt&) const;
    const UnsignedBigInt operator+(const UnsignedBigInt&&) const;
    const UnsignedBigInt operator-(const UnsignedBigInt&) const;
    const UnsignedBigInt operator-(const UnsignedBigInt&&) const;
    const UnsignedBigInt operator*(const UnsignedBigInt&) const;
    const UnsignedBigInt operator*(const UnsignedBigInt&&) const;
    const UnsignedBigInt operator/(const UnsignedBigInt&) const;
    const UnsignedBigInt operator/(const UnsignedBigInt&&) const;
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

class BigInt {
  public:
    typedef UnsignedBigInt::value_type value_type;
    typedef UnsignedBigInt::size_type size_type;
    typedef UnsignedBigInt::maxinteger_type maxinteger_type;

  private:
    UnsignedBigInt val; //值，每位一个数字，采用顺序存储
    bool sign;          //符号，0正数1负数
  public:
    //构造函数&解析函数
    BigInt();
    BigInt(string& s);
    BigInt(string&& s);
    BigInt(long long _val);
    BigInt(const UnsignedBigInt&);
    BigInt(UnsignedBigInt&&);
    ~BigInt() {}
    //类型转换函数
    inline explicit operator bool() const { return bool(val); }
    explicit operator string() const;
    explicit operator UnsignedBigInt() const;
    //普通函数
    bool isnegative() const;        //返回是否为负数
    const BigInt factorial() const; //返回自己的阶乘
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
    bool operator<=(const BigInt&) const;
    inline bool operator>(const BigInt& a) const { return !((*this) <= a); }
    inline bool operator>=(const BigInt& a) const { return !((*this) < a); }
    bool operator==(const BigInt&) const;
    inline bool operator!=(const BigInt& a) const { return !((*this) == a); }
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
#endif