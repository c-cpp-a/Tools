#include "tools/BigInt.cpp"
#include "tools/code.cpp"
#include "tools/fraction.cpp"
#include "tools/maths.cpp"
#include "tools/matrix.cpp"
#include <cmath>
#include <ctime>
#include <iostream>
#include <math.h>
#include <random>
#include <vector>
using namespace std;
default_random_engine e;
inline void putrand(long long& a, long long& b) { a = e(), b = e(); };
inline void putrand(long long& a, long long& b, long long& c) {
    a = e(), b = e(), c = e();
}
long long qadd(long long& a, long long b, const long long& p) {
    long long ans = 0, tmp = a;
    while (b) {
        if (b & 1) {
            ans += tmp;
            ans %= p;
        }
        tmp <<= 1;
        tmp %= p;
        b >>= 1;
    }
    return ans % p;
}
long long qpow(long long& a, long long b, const long long& p) {
    long long ans = 1, tmp = a;
    while (b) {
        if (b & 1) {
            ans *= tmp;
            ans %= p;
        }
        tmp *= tmp;
        tmp %= p;
        b >>= 1;
    }
    return ans % p;
}
void test_BigInt() {
    //测试BigInt类
    cout << "testing class BigInt...\n";
    BigInt testa, testb, testc, testp;
    long long a, b, c, p;
    unsigned int ans_correct = 0, ans_wrong = 0;
    cout << "testing operator+...\n";
    for (int i = 0; i < 10; i++) {
        putrand(a, b);
        testa = a, testb = b;
        c = a + b, testc = testa + testb;
        if (BigInt(c) == testc) {
            ++ans_correct;
            cout << "test " << i + 1 << ":correct!\n";
        } else {
            ++ans_wrong;
            cout << "test " << i + 1 << ":wrong!\n";
            cout << "...when a=" << a << ",b=" << b << ".\n";
            cout << "...a+b=" << BigInt(c) << ",but find testa+testb=" << testc
                 << ".\n";
        }
    }
    cout << "testing operaotr-...\n";
    for (int i = 0; i < 10; i++) {
        putrand(a, b);
        testa = a, testb = b;
        c = a - b, testc = testa - testb;
        if (BigInt(c) == testc) {
            ++ans_correct;
            cout << "test " << i + 11 << ":correct!\n";
        } else {
            ++ans_wrong;
            cout << "test " << i + 11 << ":wrong!\n";
            cout << "...when a=" << a << ",b=" << b << ".\n";
            cout << "...a-b=" << c << ",but find testa-testb=" << testc
                 << ".\n";
        }
    }
    cout << "testing operaotr*...\n";
    for (int i = 0; i < 10; i++) {
        putrand(a, b, p);
        testa = a, testb = b, testp = p;
        c = qadd(a, b, p), testc = testa * testb % testp;
        if (BigInt(c) == testc) {
            ++ans_correct;
            cout << "test " << i + 21 << ":correct!\n";
        } else {
            ++ans_wrong;
            cout << "test " << i + 21 << ":wrong!\n";
            cout << "...when a=" << a << ",b=" << b << ",p=" << p << ".\n";
            cout << "...a*b%p=" << c << ",but find testa*testb%p=" << testc
                 << ".\n";
        }
    }
    cout << "testing operaotr/...\n";
    for (int i = 0; i < 10; i++) {
        putrand(a, b);
        testa = a, testb = b;
        c = a / b, testc = testa / testb;
        if (BigInt(c) == testc) {
            ++ans_correct;
            cout << "test " << i + 31 << ":correct!\n";
        } else {
            ++ans_wrong;
            cout << "test " << i + 31 << ":wrong!\n";
            cout << "...when a=" << a << ",b=" << b << ".\n";
            cout << "...a/b=" << c << ",but find testa/testb=" << testc
                 << ".\n";
        }
    }
    cout << "testing operaotr^...\n";
    for (int i = 0; i < 10; i++) {
        putrand(a, b, p);
        testa = a, testb=b,testp = p;
        c = qpow(a, b, p), testc = qpow(testa,testb,testp);
        if (BigInt(c) == testc) {
            ++ans_correct;
            cout << "test " << i + 31 << ":correct!\n";
        } else {
            ++ans_wrong;
            cout << "test " << i + 31 << ":wrong!\n";
            cout << "...when a=" << a << ",b=" << b << ",p=" << p << ".\n";
            cout << "...a^b%p=" << c << ",but find testa^testb%testp=" << testc
                 << ".\n";
        }
    }
    cout << "testing operaotr%...\n";
    for (int i = 0; i < 10; i++) {
        putrand(a, b);
        testa = a, testb = b;
        c = a % b, testc = testa % testb;
        if (BigInt(c) == testc) {
            ++ans_correct;
            cout << "test " << i + 31 << ":correct!\n";
        } else {
            ++ans_wrong;
            cout << "test " << i + 31 << ":wrong!\n";
            cout << "...when a=" << a << ",b="
                 << ".\n";
            cout << "...a%b=" << c << ",but find testa%testb=" << testc
                 << ".\n";
        }
    }
}
int main() {
    e.seed(time(0));
    test_BigInt();
    return 0;
}
