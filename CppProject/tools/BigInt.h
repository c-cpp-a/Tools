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

  private:
    vector<value_type> val; //值，每位一个数字，采用顺序存储
  public:
    //构造函数&解析函数
    UnsignedBigInt();
    UnsignedBigInt(string& s);
    UnsignedBigInt(string&& s);
    UnsignedBigInt(unsigned long long _val);
    ~UnsignedBigInt() = default;
    //类型转换函数
    inline explicit operator bool() const { return !val.empty(); }
    explicit operator string() const;
    //重载算术运算符
    const UnsignedBigInt operator+(const UnsignedBigInt&) const;
    const UnsignedBigInt operator+(const UnsignedBigInt&&) const;
    const UnsignedBigInt operator-(const UnsignedBigInt&) const;
    const UnsignedBigInt operator-(const UnsignedBigInt&&) const;
    const UnsignedBigInt operator*(const UnsignedBigInt&) const;
    const UnsignedBigInt operator*(const UnsignedBigInt&&) const;
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
    //普通函数
    bool isnegative() const;
    //重载算术运算符
    const BigInt operator-() const;
    const BigInt operator+(const BigInt&) const;
    const BigInt operator+(const BigInt&&) const;
    const BigInt operator-(const BigInt&) const;
    const BigInt operator-(const BigInt&&) const;
    const BigInt operator*(const BigInt&) const;
    const BigInt operator*(const BigInt&&) const;
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