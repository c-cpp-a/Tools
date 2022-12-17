#ifndef MATRIX_H_H
#define MATRIX_H_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
template <typename Int> class Matrix {
  public:
    typedef string::size_type len_type;

  private:
    len_type n, m;           // n行m列
    vector<vector<Int>> val; //矩阵
  private:
    //私有函数
    bool check(const len_type, const len_type) const; //检查是否超界
  public:
    //构造函数&解析函数
    Matrix(const len_type& _n, const len_type& _m); //初始化（传变量）
    Matrix(const len_type&& _n = 0, const len_type&& _m = 0); //初始化（传值）
    Matrix(vector<vector<Int>>&); //初始化（传vector二维动态数组）
    Matrix(vector<vector<Int>>&, const len_type,
           const len_type); //初始化（传vector二维动态数组及大小）
    ~Matrix() {}

  public:
    //普通方法
    const Int& at(const len_type,
                  const len_type) const; //矩阵n行m列的数（常量），进行下标检查
    Int& at(const len_type,
            const len_type); //矩阵n行m列的数（变量），进行下标检查
    const len_type& sizei() const;       //返回矩阵的行数
    const len_type& sizej() const;       //返回矩阵的列数
    const Matrix<Int> transpose() const; //返回转置矩阵
  public:
    //重载符号
    const vector<Int>&
    operator[](const len_type) const; //矩阵n行m列的数（常量），不进行下标检查
    vector<Int>&
    operator[](const len_type); //矩阵n行m列的数（变量），不进行下标检查
    const Matrix<Int> operator+(const Matrix<Int>&) const; //矩阵加法（变量）
    const Matrix<Int> operator+(const Matrix<Int>&&) const; //矩阵加法（值）
    const Matrix<Int> operator-(const Matrix<Int>&) const; //矩阵减法（变量）
    const Matrix<Int> operator-(const Matrix<Int>&&) const; //矩阵减法（值）
    const Matrix<Int> operator*(const Matrix<Int>&) const; //矩阵乘法（变量）
    const Matrix<Int> operator*(const Matrix<Int>&&) const; //矩阵乘法（值）
    const Matrix<Int> operator*(const Int&) const; //矩阵乘法（数：变量）
    const Matrix<Int> operator*(const Int&&) const; //矩阵乘法（数：值）
    const Matrix<Int> operator/(const Int&) const; //矩阵除法（数：变量）
    const Matrix<Int> operator/(const Int&&) const; //矩阵除法（数：值）
    const Matrix<Int> operator+=(const Matrix<Int>&); //矩阵加法（变量）
    const Matrix<Int> operator+=(const Matrix<Int>&&); //矩阵加法（值）
    const Matrix<Int> operator-=(const Matrix<Int>&); //矩阵减法（变量）
    const Matrix<Int> operator-=(const Matrix<Int>&&); //矩阵减法（值）
    const Matrix<Int> operator*=(const Matrix<Int>&); //矩阵乘法（变量）
    const Matrix<Int> operator*=(const Matrix<Int>&&); //矩阵乘法（值）
    const Matrix<Int> operator*=(const Int&); //矩阵乘法（数：变量）
    const Matrix<Int> operator*=(const Int&&); //矩阵乘法（数：值）
    const Matrix<Int> operator/=(const Int&); //矩阵除法（数：变量）
    const Matrix<Int> operator/=(const Int&&); //矩阵除法（数：值）
};
//外部函数
template <typename Int>
ostream& operator<<(ostream&, const Matrix<Int>&); //输出矩阵（变量/常量）
template <typename Int>
ostream& operator<<(ostream&, const Matrix<Int>&&); //输出矩阵（传值）
template <typename Int>
inline const Matrix<Int> operator*(const Int& a,
                                   const Matrix<Int>& b) { //矩阵乘法1
    return b * a;
}
template <typename Int>
inline const Matrix<Int> operator*(const Int& a,
                                   const Matrix<Int>&& b) { //矩阵乘法2
    return b * a;
}
template <typename Int>
inline const Matrix<Int> operator*(const Int&& a,
                                   const Matrix<Int>& b) { //矩阵乘法3
    return b * a;
}
template <typename Int>
inline const Matrix<Int> operator*(const Int&& a,
                                   const Matrix<Int>&& b) { //矩阵乘法4
    return b * a;
}

//定义的默认矩阵
typedef Matrix<int> matrix;
#endif
