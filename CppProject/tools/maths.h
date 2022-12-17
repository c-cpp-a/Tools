#ifndef MATHS_H_H
#define MATHS_H_H
#define _sqrt_double 1e-10
template <typename Double> inline Double Abs(const Double x) { //求绝对值
    return (x < 0 ? -x : x);
}
template <> inline int Abs(const int x) { //求绝对值的位运算版本
    return x & (-x);
}
template <typename Double> Double Sqrt(const Double); //开平方根，传入一个数
#endif