#ifndef BIGINT_CPP_CPP_
#define BIGINT_CPP_CPP_
#include "BigInt.h"
#include "code.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <exception>
#include <type_traits>
#include <vector>
//构造函数&解析函数
UnsignedBigInt::UnsignedBigInt()
    : isstrict(UnsignedBigInt::default_strict_mode) {
    val.push_back(0);
}
UnsignedBigInt::UnsignedBigInt(string& s, mode_type _strict)
    : isstrict(_strict) {
    string::size_type len = s.length(), i = 0;
    while (i < len && s[i] == '0')
        ++i;
    if (i == len) {
        val.push_back(0);
        return;
    }
    for (; i < len; i++) {
        if (isdigit(s[i]))
            val.push_back(s[i] - '0');
        else {
            if (isstrict) {
                val = vector<value_type>();
                cerr << __func__
                     << ":find a char "
                        "not number!\n";
                throw exception();
                return;
            } else {
                return;
            }
        }
    }
}
UnsignedBigInt::UnsignedBigInt(string&& s, mode_type _strict)
    : isstrict(_strict) {
    string::size_type len = s.length(), i = 0;
    while (i < len && s[i] == '0')
        ++i;
    if (i == len) {
        val.push_back(0);
        return;
    }
    for (; i < len; i++) {
        if (isdigit(s[i]))
            val.push_back(s[i] - '0');
        else {
            if (isstrict) {
                val = vector<value_type>();
                cerr << __func__
                     << ":find a char "
                        "not number!\n";
                throw exception();
                return;
            } else {
                return;
            }
        }
    }
}
UnsignedBigInt::UnsignedBigInt(UnsignedBigInt::maxinteger_type _val,
                               mode_type _strict)
    : isstrict(_strict) {
    if (_val == 0) {
        val.push_back(0);
        return;
    }
    while (_val) {
        val.push_back(_val % 10);
        _val /= 10;
    }
    val = vector<value_type>(val.rbegin(), val.rend());
}
UnsignedBigInt::UnsignedBigInt(const vector<value_type>& _val,
                               mode_type _strict)
    : val(_val), isstrict(_strict) {}
UnsignedBigInt::UnsignedBigInt(const vector<value_type>&& _val,
                               mode_type _strict)
    : val(_val), isstrict(_strict) {}
//类型转换函数
UnsignedBigInt::operator string() const {
    string ans;
    for (size_type i = 0, len = val.size(); i < len; i++) {
        ans += char(val[i] + '0');
    }
    return ans;
}
UnsignedBigInt::operator UnsignedBigInt::maxinteger_type() const {
    maxinteger_type ans = 0;
    for (size_type i = 0, len = val.size(); i < len; i++) {
        ans *= 10;
        ans += val[i];
    }
    return ans;
}
//普通函数
const UnsignedBigInt UnsignedBigInt::factorial() const {
    UnsignedBigInt ans(1U, isstrict);
    for (UnsignedBigInt i = 2; i <= (*this); ++i) {
        ans *= i;
    }
    return ans;
}
const UnsignedBigInt::maxinteger_type UnsignedBigInt::value() const {
    UnsignedBigInt::maxinteger_type ans = 0;
    for (auto it = val.rbegin(); it != val.rend(); ++it) {
        ans = ans * 10 + *it;
    }
    return ans;
}
void UnsignedBigInt::set_strict(strict_mode _strict) { isstrict = _strict; }
UnsignedBigInt::strict_mode UnsignedBigInt::using_strict() const {
    return static_cast<UnsignedBigInt::strict_mode>(isstrict);
}
//重载算术运算符
const UnsignedBigInt UnsignedBigInt::operator+(const UnsignedBigInt& a) const {
    if ((*this) > a)
        return a + (*this);
    UnsignedBigInt ans;
    size_type lena = val.size(), lenb = a.val.size(), x = 0; // lena<=lenb
    ans.val.pop_back();
    for (size_type i = 0; i < lenb; i++) {
        if (i >= lena)
            ans.val.push_back(a.val[lenb - i - 1] + x);
        else
            ans.val.push_back(val[lena - i - 1] + a.val[lenb - i - 1] + x);
        x = ans.val[i] / 10;
        ans.val[i] %= 10;
    }
    if (x) {
        ans.val.push_back(x);
    }
    while (ans.val.size() && ans.val.back() == 0) {
        ans.val.pop_back();
    }
    if (ans.val.empty()) {
        ans.val.push_back(0);
    }
    ans.val = vector<value_type>(ans.val.rbegin(), ans.val.rend());

    return ans;
}
const UnsignedBigInt UnsignedBigInt::operator+(const UnsignedBigInt&& a) const {
    if ((*this) > a)
        return a + (*this);
    UnsignedBigInt ans;
    size_type lena = val.size(), lenb = a.val.size(), x = 0; // lena<=lenb
    ans.val.pop_back();
    for (size_type i = 0; i < lenb; i++) {
        if (i >= lena)
            ans.val.push_back(a.val[lenb - i - 1] + x);
        else
            ans.val.push_back(val[lena - i - 1] + a.val[lenb - i - 1] + x);
        x = ans.val[i] / 10;
        ans.val[i] %= 10;
    }
    if (x) {
        ans.val.push_back(x);
    }
    while (ans.val.size() && ans.val.back() == 0) {
        ans.val.pop_back();
    }
    if (ans.val.empty()) {
        ans.val.push_back(0);
    }
    ans.val = vector<value_type>(ans.val.rbegin(), ans.val.rend());

    return ans;
}
const UnsignedBigInt UnsignedBigInt::operator-(const UnsignedBigInt& a) const {
    if ((*this) < a) {
        cerr << __func__ << ":(*this)<a not alivible!\n";
        throw exception();
        return UnsignedBigInt();
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
    while (ans.val.size() && ans.val.back() == 0) {
        ans.val.pop_back();
    }
    if (ans.val.empty()) {
        return 0U;
    } else {
        ans.val = vector<value_type>(ans.val.rbegin(), ans.val.rend() - 1);
        return ans;
    }
}
const UnsignedBigInt UnsignedBigInt::operator-(const UnsignedBigInt&& a) const {
    if ((*this) < a) {
        cerr << __func__ << ":(*this)<a not alivible!\n";
        throw exception();
        return UnsignedBigInt();
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
    while (ans.val.size() && ans.val.back() == 0) {
        ans.val.pop_back();
    }
    if (ans.val.empty()) {
        return 0U;
    } else {
        ans.val = vector<value_type>(ans.val.rbegin(), ans.val.rend() - 1);
        return ans;
    }
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
const UnsignedBigInt UnsignedBigInt::operator/(const UnsignedBigInt& a) const {
    if (a == 0U) { //不能除以0
        cerr << __func__ << ":Cannot with zero!\n";
        throw exception();
        return UnsignedBigInt();
    } else if (a == 1U) { //除以1返回自身
        return (*this);
    }
    UnsignedBigInt ans, t(*this), t2(a);
    ans.val.pop_back();
    while (t2 <= t) {
        t2.val.push_back(0);
    }
    while (t >= a) {
        t2.val.pop_back();
        ans.val.push_back(0);
        while (t >= t2) {
            t -= t2;
            ++ans.val[ans.val.size() - 1];
        }
    }
    while (t2 > a) {
        ans.val.push_back(0);
        t2.val.pop_back();
    }
    if (ans.val.empty()) {
        ans.val.push_back(0);
    }
    return ans;
}
const UnsignedBigInt UnsignedBigInt::operator/(const UnsignedBigInt&& a) const {
    if (a == 0U) { //不能除以0
        cerr << __func__ << ":Cannot with zero!\n";
        throw exception();
        return UnsignedBigInt();
    } else if (a == 1U) { //除以1返回自身
        return (*this);
    }
    UnsignedBigInt ans, t(*this), t2(a);
    ans.val.pop_back();
    while (t2 <= t) {
        t2.val.push_back(0);
    }
    while (t >= a) {
        t2.val.pop_back();
        ans.val.push_back(0);
        while (t >= t2) {
            t -= t2;
            ++ans.val[ans.val.size() - 1];
        }
    }
    while (t2 > a) {
        ans.val.push_back(0);
        t2.val.pop_back();
    }
    if (ans.val.empty()) {
        ans.val.push_back(0);
    }
    return ans;
}
const UnsignedBigInt UnsignedBigInt::operator%(const UnsignedBigInt& a) const {
    if (a == 0U) { //不能对0取余
        cerr << __func__ << ":Cannot with zero!\n";
        throw exception();
        return UnsignedBigInt();
    } else if (a == 1U) { //任何数%1就是0
        return 0;
    }
    UnsignedBigInt t(*this), t2(a);
    while (t2 <= t) {
        t2.val.push_back(0);
    }
    while (t >= a) {
        t2.val.pop_back();
        while (t >= t2) {
            t -= t2;
        }
    }
    return t;
}
const UnsignedBigInt UnsignedBigInt::operator%(const UnsignedBigInt&& a) const {
    if (a == 0U) { //不能对0取余
        cerr << __func__ << ":Cannot with zero!\n";
        throw exception();
        return UnsignedBigInt();
    } else if (a == 1U) { //任何数%1就是0
        return 0;
    }
    UnsignedBigInt t(*this), t2(a);
    while (t2 <= t) {
        t2.val.push_back(0);
    }
    while (t >= a) {
        t2.val.pop_back();
        while (t >= t2) {
            t -= t2;
        }
    }
    return t;
}
const UnsignedBigInt
UnsignedBigInt::operator^(const UnsignedBigInt::maxinteger_type& a) const {
    if (a == 0U)
        return 1U;
    else if (a == 1U)
        return (*this);
    else {
        UnsignedBigInt::maxinteger_type cnt = a;
        UnsignedBigInt s((*this)), ans(1, isstrict);
        while (cnt) {
            if (cnt & 1) {
                ans *= s;
            }
            s *= s;
            cnt >>= 1;
        }
        return ans;
    }
}
const UnsignedBigInt
UnsignedBigInt::operator^(const UnsignedBigInt::maxinteger_type&& a) const {
    if (a == 0U)
        return 1U;
    else if (a == 1U)
        return (*this);
    else {
        UnsignedBigInt::maxinteger_type cnt = a;
        UnsignedBigInt s((*this)), ans(1, isstrict);
        while (cnt) {
            if (cnt & 1) {
                ans *= s;
            }
            s *= s;
            cnt >>= 1;
        }
        return ans;
    }
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
        cerr << __func__ << ":Something wrong!\n";
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
        cerr << __func__ << ":Something wrong!\n";
        is.exceptions(std::istream::failbit);
    }
    return is;
}
//快速幂（mod p意义)
const UnsignedBigInt qpow(const UnsignedBigInt& a, const UnsignedBigInt& b,
                          const UnsignedBigInt& p) {
    UnsignedBigInt ans = 1, tmp = a, nowb = b;
    while (nowb) {
        if (nowb.back() % 2) {
            ans *= tmp;
            ans %= p;
        }
        tmp *= tmp;
        nowb /= 2;
    }
    return ans;
}
// BigInt类
//构造函数&解析函数
BigInt::BigInt() : sign(false) {}
BigInt::BigInt(string& s, mode_type _strict) : sign(false) {
    val.set_strict(static_cast<strict_mode>(_strict));
    if (s[0] == '-') { //负数
        sign = true;
        s.erase(s.begin());
    }
    val = s;
}
BigInt::BigInt(string&& s, mode_type _strict) : sign(false) {
    val.set_strict(static_cast<strict_mode>(_strict));
    if (s[0] == '-') { //负数
        sign = true;
        s.erase(s.begin());
    }
    val = s;
}
BigInt::BigInt(BigInt::maxinteger_type _val, mode_type _strict) {
    if (_val >= 0) {
        sign = false;
        val = _val;
    } else {
        sign = true;
        val = -_val;
    }
    val.set_strict(static_cast<strict_mode>(_strict));
}
BigInt::BigInt(const UnsignedBigInt& _val) : val(_val), sign(false) {}
BigInt::BigInt(UnsignedBigInt&& _val) noexcept : val(_val), sign(false) {}
//类型转换函数
BigInt::operator string() const { return (sign ? "-" : "") + string(val); }
BigInt::operator UnsignedBigInt() const {
    if (sign) {
        cerr << __func__
             << ":Cannot give class "
                "UnsignedBigInt a negative number!\n";
        throw exception();
        return UnsignedBigInt();
    }
    return val;
}
BigInt::operator BigInt::maxinteger_type() const {
    return maxinteger_type(UnsignedBigInt::maxinteger_type(val)) *
           (sign == false ? 1 : -1);
}
//普通函数
bool BigInt::isnegative() const { return !sign; }
const BigInt BigInt::factorial() const {
    if (sign) {
        cerr << __func__
             << ":The factorial of a "
                "negative integer is undefined!\n";
        throw exception();
        return 0LL;
    }
    return val.factorial();
}
void BigInt::set_strict(strict_mode _strict) { val.set_strict(_strict); }
BigInt::strict_mode BigInt::using_strict() const { return val.using_strict(); }
//重载算术运算符
const BigInt BigInt::operator-() const {
    BigInt ans;
    ans.sign = !sign;
    ans.val = val;
    return ans;
}
const BigInt BigInt::operator+(const BigInt& a) const {
    BigInt ans;
    switch ((sign << 1) | a.sign) {
    case 0: //都是正数，绝对值相加
        ans = (val + a.val);
        break;
    case 1: //自己是正数，a是负数，等价于(*this)-a.val
        ans = (val - a.val);
        break;
    case 2: //自己是负数，a是正数，等价于a-(*this).val
        ans = (a.val - val);
        break;
    case 3: //都是负数，绝对值相加后取负
        ans = -BigInt((val + a.val));
        break;
    }
    ans.turn_sign();
    return ans;
}
const BigInt BigInt::operator+(const BigInt&& a) const {
    BigInt ans;
    switch ((sign << 1) | a.sign) {
    case 0: //都是正数，绝对值相加
        ans = (val + a.val);
        break;
    case 1: //自己是正数，a是负数，等价于(*this)-a.val
        ans = (val - a.val);
        break;
    case 2: //自己是负数，a是正数，等价于a-(*this).val
        ans = (a.val - val);
        break;
    case 3: //都是负数，绝对值相加后取负
        ans = -BigInt((val + a.val));
        break;
    }
    ans.turn_sign();
    return ans;
}
const BigInt BigInt::operator-(const BigInt& a) const {
    BigInt ans;
    switch ((sign << 1) | a.sign) {
    case 0: //都是正数，绝对值相减，注意相减后小于0的情况
        if (val < a.val) {
            ans = -BigInt(a.val - val);
        } else {
            ans = (val - a.val);
        }
        break;
    case 1: //自己是正数，a是负数，等价于(*this)+a.val
        ans = (val + a.val);
        break;
    case 2: //自己是负数，a是正数，等价于-(a.val+(*this))
        ans = -BigInt(a.val + val);
        break;
    case 3: //都是负数，等价于(a.val-(*this)),同样注意相减后小于0的情况
        if (val <= a.val) {
            ans = (a.val - val);
        } else {
            ans = -BigInt(val - a.val);
        }
        break;
    }
    ans.turn_sign();
    return ans;
}
const BigInt BigInt::operator-(const BigInt&& a) const {
    BigInt ans;
    switch ((sign << 1) | a.sign) {
    case 0: //都是正数，绝对值相减，注意相减后小于0的情况
        if (val < a.val) {
            ans = -BigInt(a.val - val);
        } else {
            ans = (val - a.val);
        }
        break;
    case 1: //自己是正数，a是负数，等价于(*this)+a.val
        ans = (val + a.val);
        break;
    case 2: //自己是负数，a是正数，等价于-(a.val+(*this))
        ans = -BigInt(a.val + val);
        break;
    case 3: //都是负数，等价于(a.val-(*this)),同样注意相减后小于0的情况
        if (val <= a.val) {
            ans = (a.val - val);
        } else {
            ans = -BigInt(val - a.val);
        }
        break;
    }
    ans.turn_sign();
    return ans;
}
const BigInt BigInt::operator*(const BigInt& a) const {
    BigInt ans;
    if (a.sign != sign)
        ans = -BigInt(
            val * a.val); //不同符号，一定有一个是负号，所以是绝对值相乘再取负
    else
        ans =
            val * a.val; //相同符号，要么正正得正，要么负负得正，都是绝对值相乘
    ans.turn_sign();
    return ans;
}
const BigInt BigInt::operator*(const BigInt&& a) const {
    BigInt ans;
    if (a.sign != sign)
        ans = -BigInt(
            val * a.val); //不同符号，一定有一个是负号，所以是绝对值相乘再取负
    else
        ans =
            val * a.val; //相同符号，要么正正得正，要么负负得正，都是绝对值相乘
    ans.turn_sign();
    return ans;
}
const BigInt BigInt::operator/(const BigInt& a) const {
    BigInt ans;
    if (a.sign != sign)
        ans = -BigInt(
            val / a.val); //不同符号，一定有一个是负号，所以是绝对值相除再取负
    else
        ans = val / a.val; //相同符号，符号会互相抵消，所以是绝对值相除
    ans.turn_sign();
    return ans;
}
const BigInt BigInt::operator/(const BigInt&& a) const {
    BigInt ans;
    if (a.sign != sign)
        ans = -BigInt(
            val / a.val); //不同符号，一定有一个是负号，所以是绝对值相除再取负
    else
        ans = val / a.val; //相同符号，符号会互相抵消，所以是绝对值相除
    ans.turn_sign();
    return ans;
}
const BigInt BigInt::operator%(const BigInt& a) const {
    BigInt ans;
    switch ((sign << 1) | a.sign) {
    case 0: //都是正数
        ans = val % a.val;
        break;
    case 1: //自己是正数，a是负数
        ans = -BigInt(a.val - val % a.val);
        break;
    case 2: //自己是负数，a是正数
        ans = a.val - val % a.val;
        break;
    case 3: //都是负数
        ans = -BigInt(val % a.val);
        break;
    }
    ans.turn_sign();
    return ans;
}
const BigInt BigInt::operator%(const BigInt&& a) const {
    BigInt ans;
    switch ((sign << 1) | a.sign) {
    case 0: //都是正数
        ans = val % a.val;
        break;
    case 1: //自己是正数，a是负数
        ans = -BigInt(a.val - val % a.val);
        break;
    case 2: //自己是负数，a是正数
        ans = a.val - val % a.val;
        break;
    case 3: //都是负数
        ans = -BigInt(val % a.val);
        break;
    }
    ans.turn_sign();
    return ans;
}
const BigInt BigInt::operator^(const BigInt::maxinteger_type& a) const {
    BigInt ans;
    if (a < 0) {           //如果a为负数
        return 0;          //任何数的小于0的次方都小于1，忽略
    } else if (a & sign) { //如果a为奇数而且sign是true（负数）
        ans = -BigInt(val ^ a);
    } else { //正数的幂次方都是正数，负数的偶数幂次方也是正数（很明显，负负得正）
        ans = (val ^ a);
    }
    ans.turn_sign();
    return ans;
}
const BigInt BigInt::operator^(const BigInt::maxinteger_type&& a) const {
    BigInt ans;
    if (a < 0) {           //如果a为负数
        return 0;          //任何数的小于0的次方都小于1，忽略
    } else if (a & sign) { //如果a为奇数而且sign是true（负数）
        ans = -BigInt(val ^ a);
    } else { //正数的幂次方都是正数，负数的偶数幂次方也是正数（很明显，负负得正）
        ans = (val ^ a);
    }
    ans.turn_sign();
    return ans;
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
bool BigInt::operator<(const BigInt&& a) const {
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
bool BigInt::operator<=(const BigInt&& a) const {
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
    if (val == 0 && a.val == 0)
        return true;
    if (sign != a.sign)
        return false; //符号不一样，值一定不一样
    else
        return val == a.val; //否则返回绝对值是否一样
}
bool BigInt::operator==(const BigInt&& a) const {
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
        cerr << __func__ << ":Something wrong!\n";
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
        cerr << __func__
             << ":Something "
                "wrong!\n";
        is.exceptions(std::istream::failbit);
    }
    return is;
}
const BigInt qpow(const BigInt& a, const BigInt& b, const BigInt& p) {
    BigInt ans = 1, tmp = a, nowb = b;
    while (nowb > 0) {
        if (nowb.back() % 2) {
            ans *= tmp;
            ans %= p;
        }
        tmp *= tmp;
        nowb /= 2;
    }
    return ans;
}
#endif