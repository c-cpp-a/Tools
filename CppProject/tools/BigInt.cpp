#ifndef BIGINT_CPP_CPP_
#define BIGINT_CPP_CPP_
#include "BigInt.h"
#include <algorithm>
#include <exception>
#include <type_traits>
//构造函数&解析函数
UnsignedBigInt::UnsignedBigInt() {
    // pass
}
UnsignedBigInt::UnsignedBigInt(string& s) {
    string::size_type len = s.length();
    for (string::size_type i = 0; i < len; i++) {
        if (isdigit(s[i]))
            val.push_back(s[i] - '0');
        else {
            val = vector<value_type>();
            cerr << "UnsignedBigInt::UnsignedBigInt(string& s):find a char not "
                    "number!\n";
            throw;
        }
    }
}
UnsignedBigInt::UnsignedBigInt(string&& s) {
    string::size_type len = s.length();
    for (string::size_type i = 0; i < len; i++) {
        if (isdigit(s[i]))
            val.push_back(s[i] - '0');
        else {
            val = vector<value_type>();
            cerr << "UnsignedBigInt::UnsignedBigInt(string&& s):find a char "
                    "not number!\n";
            throw exception();
        }
    }
}
UnsignedBigInt::UnsignedBigInt(unsigned long long _val) {
    if (_val == 0) {
        return;
    }
    while (_val) {
        val.push_back(_val % 10);
        _val /= 10;
    }
    val = vector<value_type>(val.rbegin(), val.rend());
}
//类型转换函数
UnsignedBigInt::operator string() const {
    string ans;
    for (size_type i = 0, len = val.size(); i < len; i++) {
        ans += char(val[i] + '0');
    }
    return ans;
}
//重载算术运算符
const UnsignedBigInt UnsignedBigInt::operator+(const UnsignedBigInt& a) const {
    if ((*this) > a)
        return a + (*this);
    UnsignedBigInt ans;
    size_type lena = val.size(), lenb = a.val.size(), x = 0; // lena<=lenb
    for (size_type i = 0; i < lenb; i++) {
        ans.val.push_back(0U);
    }
    for (size_type i = 0; i < lenb; i++) {
        if (i > lena)
            ans.val[i] = a.val[lenb - i - 1] + x;
        else
            ans.val[i] = val[lena - i - 1] + a.val[lenb - i - 1] + x;
        x = ans.val[i] / 10;
        ans.val[i] %= 10;
    }
    if (x) {
        ans.val.push_back(x);
    }
    ans.val = vector<value_type>(ans.val.rbegin(), ans.val.rend());

    return ans;
}
const UnsignedBigInt UnsignedBigInt::operator+(const UnsignedBigInt&& a) const {
    if ((*this) > a)
        return a + (*this);
    UnsignedBigInt ans;
    size_type lena = val.size(), lenb = a.val.size(), x = 0; // lena<=lenb
    for (size_type i = 0; i < lenb; i++) {
        if (i > lena)
            ans.val.push_back(a.val[lenb - i - 1] + x);
        else
            ans.val.push_back(val[lena - i - 1] + a.val[lenb - i - 1] + x);
        x = ans.val[i] / 10;
        ans.val[i] %= 10;
    }
    if (x) {
        ans.val.push_back(x);
    }
    ans.val = vector<value_type>(ans.val.rbegin(), ans.val.rend());

    return ans;
}
const UnsignedBigInt UnsignedBigInt::operator-(const UnsignedBigInt& a) const {
    if ((*this) < a) {
        cerr << "const UnsignedBigInt UnsignedBigInt::operator-(const "
                "UnsignedBigInt& a) const:(*this)<a not alivible!\n";
        throw exception();
    }
    UnsignedBigInt ans;
    size_type lena = val.size(), lenb = a.val.size(), x = 0; // lena>=lenb
    for (int i = 0; i < lena; i++) {
        std::make_signed<value_type>::type tmp;
        if (i >= lenb)
            tmp = val[lena - i - 1] - x;
        else
            tmp = val[lena - i - 1] - a.val[lenb - i - 1] - x;
        if (tmp < 0) {
            x = 1;
            ans.val.push_back(static_cast<value_type>(tmp + 10));
        } else {
            x = 0;
            ans.val.push_back(static_cast<value_type>(tmp));
        }
    }
    while (ans.val.size() && *(ans.val.end() - 1) == 0) {
        ans.val.pop_back();
    }

    if (ans.val.empty()) {
        ans.val.push_back(0U);
    }
    ans.val = vector<value_type>(ans.val.rbegin(), ans.val.rend());
    return ans;
}
const UnsignedBigInt UnsignedBigInt::operator-(const UnsignedBigInt&& a) const {
    if ((*this) < a) {
        cerr << "const UnsignedBigInt UnsignedBigInt::operator-(const "
                "UnsignedBigInt& a) const:(*this)<a not alivible!\n";
        throw exception();
    }
    UnsignedBigInt ans;
    size_type lena = val.size(), lenb = a.val.size(), x = 0; // lena>=lenb
    for (int i = 0; i < lena; i++) {
        std::make_signed<value_type>::type tmp;
        if (i >= lenb)
            tmp = val[lena - i - 1] - x;
        else
            tmp = val[lena - i - 1] - a.val[lenb - i - 1] - x;
        if (tmp < 0) {
            x = 1;
            ans.val.push_back(static_cast<value_type>(tmp + 10));
        } else {
            x = 0;
            ans.val.push_back(static_cast<value_type>(tmp));
        }
    }
    while (*(ans.val.end() - 1) == 0)
        ans.val.pop_back();
    ans.val = vector<value_type>(ans.val.rbegin(), ans.val.rend());
    return ans;
}
const UnsignedBigInt UnsignedBigInt::operator*(const UnsignedBigInt& a) const {
    UnsignedBigInt ans;
    size_type lena = val.size(), lenb = a.val.size(), x = 0;
    for (size_type i = 0, len = lena + lenb; i < len; i++) {
        ans.val.push_back(0U);
    }
    for (size_type i = 0; i < lena; i++) {
        x = 0;
        for (size_type j = 0; j < lenb; j++) {
            ans.val[i + j] += val[lena - i - 1] * a.val[lenb - j - 1] + x;
            x = ans.val[i + j] / 10;
            ans.val[i + j] %= 10;
        }
        for (size_type j = 0; x; j++) {
            if (ans.val.size() > i + lenb + j) {
                ans.val[i + j + lenb] += x % 10;
                x = ans.val[i + j + lenb] / 10;
                ans.val[i + j + lenb] %= 10;
            } else {
                while (x) {
                    ans.val.push_back(x % 10);
                    x /= 10;
                }
                break;
            }
        }
    }

    while (ans.val.size() && *(ans.val.end() - 1) == 0) {
        ans.val.pop_back();
    }
    if (ans.val.empty()) {
        ans.val.push_back(0);
    }
    ans.val = vector<value_type>(ans.val.rbegin(), ans.val.rend());
    return ans;
}
const UnsignedBigInt UnsignedBigInt::operator*(const UnsignedBigInt&& a) const {
    UnsignedBigInt ans;
    size_type lena = val.size(), lenb = a.val.size(), x = 0;
    for (size_type i = 0, len = lena + lenb; i < len; i++) {
        ans.val.push_back(0U);
    }
    for (size_type i = 0; i < lena; i++) {
        x = 0;
        for (size_type j = 0; j < lenb; j++) {
            ans.val[i + j] += val[lena - i - 1] * a.val[lenb - j - 1] + x;
            x = ans.val[i + j] / 10;
            ans.val[i + j] %= 10;
        }
        for (size_type j = 0; x; j++) {
            if (ans.val.size() > i + lenb + j) {
                ans.val[i + j + lenb] += x % 10;
                x = ans.val[i + j + lenb] / 10;
                ans.val[i + j + lenb] %= 10;
            } else {
                while (x) {
                    ans.val.push_back(x % 10);
                    x /= 10;
                }
                break;
            }
        }
    }

    while (ans.val.size() && *(ans.val.end() - 1) == 0) {
        ans.val.pop_back();
    }
    if (ans.val.empty()) {
        ans.val.push_back(0);
    }
    ans.val = vector<value_type>(ans.val.rbegin(), ans.val.rend());
    return ans;
}
//重载比较运算符
bool UnsignedBigInt::operator<(const UnsignedBigInt& a) const {
    size_type lena = val.size(), lenb = a.val.size();
    if (lena < lenb)
        return true;
    else if (lena > lenb)
        return false;
    else {
        for (size_type i = 0; i < lena; i++) {
            if (val[i] < a.val[i])
                return true;
            else if (val[i] > a.val[i])
                return false;
        }
        return false;
    }
}
bool UnsignedBigInt::operator<=(const UnsignedBigInt& a) const {
    size_type lena = val.size(), lenb = a.val.size();
    if (lena < lenb)
        return true;
    else if (lena > lenb)
        return false;
    else {
        for (size_type i = 0; i < lena; i++) {
            if (val[i] < a.val[i])
                return true;
            else if (val[i] > a.val[i])
                return false;
        }
        return true;
    }
}
bool UnsignedBigInt::operator==(const UnsignedBigInt& a) const {
    size_type lena = val.size(), lenb = a.val.size();
    if (lena != lenb)
        return false;
    else {
        for (size_type i = 0; i < lena; i++) {
            if (val[i] != a.val[i])
                return false;
        }
        return true;
    }
}
//输入流运算符
istream& operator>>(istream& is, UnsignedBigInt& a) {
    string tmp;
    is >> tmp;
    try {
        a = tmp;
    } catch (...) {
        cerr << "istream& operator>>(istream& is, UnsignedBigInt& "
                "a):Something wrong!\n";
        is.exceptions(std::istream::failbit);
    }
    return is;
}
istream& operator>>(istream& is, UnsignedBigInt&& a) {
    string tmp;
    is >> tmp;
    try {
        a = tmp;
    } catch (...) {
        cerr << "istream& operator>>(istream& is, UnsignedBigInt&& "
                "a):Something wrong!\n";
        is.exceptions(std::istream::failbit);
    }
    return is;
}
//构造函数&解析函数
BigInt::BigInt() : sign(false) {
    // pass
}
BigInt::BigInt(string& s) : sign(false) {
    if (s[0] == '-') { //负数
        sign = true;
        s.erase(s.begin());
    }
    val = s;
}
BigInt::BigInt(string&& s) : sign(false) {
    if (s[0] == '-') { //负数
        sign = true;
        s.erase(s.begin());
    }
    val = s;
}
BigInt::BigInt(long long _val) {
    if (_val >= 0) {
        val = _val;
    } else {
        sign = true;
        val = -_val;
    }
}
BigInt::BigInt(const UnsignedBigInt& _val) : val(_val), sign(false) {}
BigInt::BigInt(UnsignedBigInt&& _val) : val(_val), sign(false) {}
//类型转换函数
BigInt::operator string() const { return (sign ? "-" : "") + string(val); }
//普通函数
bool BigInt::isnegative() const { return !sign; }
//重载算术运算符
const BigInt BigInt::operator-() const {
    BigInt ans;
    ans.sign = !sign;
    ans.val = val;
    return ans;
}
const BigInt BigInt::operator+(const BigInt& a) const {
    switch ((sign << 1) | a.sign) {
    case 0: //都是正数，绝对值相加
        return (val + a.val);
    case 1: //自己是正数，a是负数，等价于(*this)-a.val
        return (val - a.val);
    case 2: //自己是负数，a是正数，等价于a-(*this).val
        return (a.val - val);
    case 3: //都是负数，绝对值相加后取负
        return -BigInt((val + a.val));
    }
    return BigInt();
}
const BigInt BigInt::operator+(const BigInt&& a) const {
    switch ((sign << 1) | a.sign) {
    case 0: //都是正数，绝对值相加
        return (val + a.val);
    case 1: //自己是正数，a是负数，等价于(*this)-a.val
        return (val - a.val);
    case 2: //自己是负数，a是正数，等价于a-(*this).val
        return (a.val - val);
    case 3: //都是负数，绝对值相加后取负
        return -BigInt((val + a.val));
    }
    return BigInt();
}
const BigInt BigInt::operator-(const BigInt& a) const {
    switch ((sign << 1) | a.sign) {
    case 0: //都是正数，绝对值相减，注意相减后小于0的情况
        if (val < a.val) {
            return -BigInt(a.val - val);
        } else {
            return (val - a.val);
        }
    case 1: //自己是正数，a是负数，等价于(*this)+a.val
        return (val + a.val);
    case 2: //自己是负数，a是正数，等价于-(a.val+(*this))
        return -BigInt(a.val + val);
    case 3: //都是负数，等价于(a.val-(*this)),同样注意相减后小于0的情况
        if (val <= a.val) {
            return (a.val - val);
        } else {
            return -BigInt(val - a.val);
        }
    }
    return BigInt();
}
const BigInt BigInt::operator-(const BigInt&& a) const {
    switch ((sign << 1) | a.sign) {
    case 0: //都是正数，绝对值相减，注意相减后小于0的情况
        if (val < a.val) {
            return -BigInt(a.val - val);
        } else {
            return (val - a.val);
        }
    case 1: //自己是正数，a是负数，等价于(*this)+a.val
        return (val + a.val);
    case 2: //自己是负数，a是正数，等价于-(a.val+(*this))
        return -BigInt(a.val + val);
    case 3: //都是负数，等价于(a.val-(*this)),同样注意相减后小于0的情况
        if (val <= a.val) {
            return (a.val - val);
        } else {
            return -BigInt(val - a.val);
        }
    }
    return BigInt();
}
const BigInt BigInt::operator*(const BigInt& a) const {
    //异或运算规则：相同为false，不同为true
    if (a.sign ^ sign)
        return -BigInt(
            val * a.val); //不同符号，一定有一个是负号，所以是绝对值相乘再取负
    else
        return val *
               a.val; //相同符号，要么正正得正，要么负负得正，都是绝对值相乘
}
const BigInt BigInt::operator*(const BigInt&& a) const {
    //异或运算规则：相同为false，不同为true
    if (a.sign ^ sign)
        return -BigInt(
            val * a.val); //不同符号，一定有一个是负号，所以是绝对值相乘再取负
    else
        return val *
               a.val; //相同符号，要么正正得正，要么负负得正，都是绝对值相乘
}
//重载比较运算符
bool BigInt::operator<(const BigInt& a) const {
    if (sign < a.sign)
        return false; //自己正a负，(*this)>a
    else if (sign > a.sign)
        return true; //自己负a正，(*this)<a
    else if (sign) { //负数比大小：谁的绝对值小谁大
        return val > a.val;
    } else { //正数比大小：谁打绝对值大谁大
        return val < a.val;
    }
}
bool BigInt::operator<=(const BigInt& a) const {
    if (sign < a.sign)
        return false; //自己正a负，(*this)>a
    else if (sign > a.sign)
        return true; //自己负a正，(*this)<a
    else if (sign) { //负数比大小：谁的绝对值小谁大
        return val >= a.val;
    } else { //正数比大小：谁打绝对值大谁大
        return val <= a.val;
    }
}
bool BigInt::operator==(const BigInt& a) const {
    if (sign != a.sign)
        return false; //符号不一样，值一定不一样
    else
        return val == a.val; //否则返回绝对值是否一样
}
//输入流运算符
istream& operator>>(istream& is, BigInt& a) {
    string tmp;
    is >> tmp;
    try {
        a = tmp;
    } catch (...) {
        cerr
            << "istream& operator>>(istream& is, BigInt& a):Something wrong!\n";
        is.exceptions(std::istream::failbit);
    }
    return is;
}
istream& operator>>(istream& is, BigInt&& a) {
    string tmp;
    is >> tmp;
    try {
        a = tmp;
    } catch (...) {
        cerr << "istream& operator>>(istream& is, BigInt&& a):Something "
                "wrong!\n";
        is.exceptions(std::istream::failbit);
    }
    return is;
}
#endif