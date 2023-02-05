#ifndef MATRIX_CPP_CPP_
#define MATRIX_CPP_CPP_
#include "matrix.h"
#include <algorithm>
#include <iterator>
//私有函数
template <typename Int>
bool Matrix<Int>::check(const Matrix::len_type _i,
                        const Matrix::len_type _j) const {
    return (_i >= 0 && _i < n && _j >= 0 && _j < m);
}
template <typename Int>
typename Matrix<Int>::len_type
Matrix<Int>::find_maxsize(const vector<vector<Int>>& a) {
    len_type maxx = a[0].size();
    for (len_type i = 1, len = a.size(); i < len; i++) {
        maxx = max(a[i].size(), maxx);
    }
    return maxx;
}

//构造函数&解析函数
template <typename Int>
Matrix<Int>::Matrix(const Matrix::len_type& _n, const Matrix::len_type& _m)
    : n(_n), m(_m) {
    if (n < 0 || m < 0) {
        Matrix();
        return;
    }
    for (Matrix::len_type i = 0; i < n; i++) {
        val.push_back(vector<int>());
        for (Matrix::len_type j = 0; j < m; j++) {
            val[i].push_back(0);
        }
    }
}
template <typename Int>
Matrix<Int>::Matrix(const Matrix::len_type&& _n, const Matrix::len_type&& _m)
    : n(_n), m(_m) {
    if (n < 0 || m < 0) {
        cerr << "Matrix<Int>::Matrix(const Matrix::len_type&& _n, const "
                "Matrix::len_type&& _m):n<0 || m<0!\n";
        Matrix();
        return;
    }
    for (Matrix::len_type i = 0; i < n; i++) {
        val.push_back(vector<int>());
        for (Matrix::len_type j = 0; j < m; j++) {
            val[i].push_back(0);
        }
    }
}
template <typename Int>
Matrix<Int>::Matrix(vector<vector<Int>>& _val)
    : Matrix(_val, _val.size(), find_maxsize(_val)) {}
template <typename Int>
Matrix<Int>::Matrix(vector<vector<Int>>& _val, const Matrix::len_type _n,
                    const Matrix::len_type _m)
    : n(_n), m(_m) {
    if (n < 0 || m < 0) {
        cerr << "Matrix<Int>::Matrix(vector<vector<Int>>& _val, const "
                "Matrix::len_type _n,const Matrix::len_type _m):n<0 || m<0!\n";
        Matrix();
        return;
    } else if (_val.size() < n || find_maxsize(_val) < m) {
        cerr << "Matrix<Int>::Matrix(vector<vector<Int>>& _val, const "
                "Matrix::len_type _n,const Matrix::len_type _m):_val size too "
                "small!\n";
        Matrix();
        return;
    }
    for (Matrix::len_type i = 0; i < n; i++) {
        val.push_back(vector<int>());
        for (Matrix::len_type j = 0; j < m; j++) {
            if (j > _val[i].size()) {
                val[i].push_back(Int());
            } else {
                val[i].push_back(_val[i][j]);
            }
        }
    }
}

//普通方法
template <typename Int>
const Int& Matrix<Int>::at(const Matrix::len_type _i,
                           const Matrix::len_type _j) const {
    if (!check(_i, _j)) {
        cerr << "const Int &Matrix<Int>::at(const Matrix::len_type _i, const "
                "Matrix::len_type _j) const:pos not right!\n";
        throw;
        return -1;
    }
    return val[_i][_j];
}
template <typename Int>
Int& Matrix<Int>::at(const Matrix::len_type _i, const Matrix::len_type _j) {
    if (!check(_i, _j)) {
        cerr << "Int &Matrix<Int>::at(const Matrix::len_type _i, const "
                "Matrix::len_type _j):pos not right!\n";
        throw;
        return -1;
    }
    return val[_i][_j];
}
template <typename Int>
const typename Matrix<Int>::len_type& Matrix<Int>::sizei() const {
    return n;
}
template <typename Int>
const typename Matrix<Int>::len_type& Matrix<Int>::sizej() const {
    return m;
}
template <typename Int> const Matrix<Int> Matrix<Int>::transpose() const {
    Matrix<Int> ans(m, n);
    for (Matrix::len_type i = 0; i < n; i++) {
        for (Matrix::len_type j = 0; j < m; j++) {
            ans[i][j] = val[j][i];
        }
    }
    return ans;
}
template <typename Int> const Int Matrix<Int>::trace() const {
    if (sizei() != sizej()) {
        cerr << "template<typename Int> const Int Matrix<Int>::trace() "
                "const:Matrix with different length and width cannot be "
                "traced!\n";
        throw;
        return Int();
    }
    Int summ(0);
    for (len_type i = 0; i < sizei(); i++) {
        summ += val[i][i];
    }
    return summ;
}

//重载符号
template <typename Int>
const vector<Int>& Matrix<Int>::operator[](const Matrix::len_type _i) const {
    return val[_i];
}
template <typename Int>
vector<Int>& Matrix<Int>::operator[](const Matrix::len_type _i) {
    return val[_i];
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator+(const Matrix<Int>& a) const {
    if (a.sizei() != sizei() || a.sizej() != sizej()) {
        cerr << "const Matrix<Int> Matrix<Int>::operator+(const Matrix<Int> "
                "&a):Matrix size does not match!\n";
        throw;
    }
    Matrix<Int> ans(n, m);
    for (Matrix::len_type i = 0; i < n; i++) {
        for (Matrix::len_type j = 0; j < m; j++) {
            ans[i][j] = val[i][j] + a[i][j];
        }
    }
    return ans;
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator+(const Matrix<Int>&& a) const {
    if (a.sizei() != sizei() || a.sizej() != sizej()) {
        cerr << "const Matrix<Int> Matrix<Int>::operator+(const Matrix<Int> "
                "&a):Matrix size does not match!\n";
        throw;
    }
    Matrix<Int> ans(n, m);
    for (Matrix::len_type i = 0; i < n; i++) {
        for (Matrix::len_type j = 0; j < m; j++) {
            ans[i][j] = val[i][j] + a[i][j];
        }
    }
    return ans;
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator-(const Matrix<Int>& a) const {
    if (a.sizei() != sizei() || a.sizej() != sizej()) {
        cerr << "const Matrix<Int> Matrix<Int>::operator+(const Matrix<Int> "
                "&a):Matrix size does not match!\n";
        throw;
    }
    Matrix<Int> ans(n, m);
    for (Matrix::len_type i = 0; i < n; i++) {
        for (Matrix::len_type j = 0; j < m; j++) {
            ans[i][j] = val[i][j] - a[i][j];
        }
    }
    return ans;
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator-(const Matrix<Int>&& a) const {
    if (a.sizei() != sizei() || a.sizej() != sizej()) {
        cerr << "const Matrix<Int> Matrix<Int>::operator+(const Matrix<Int> "
                "&a):Matrix size does not match!\n";
        throw;
    }
    Matrix<Int> ans(n, m);
    for (Matrix::len_type i = 0; i < n; i++) {
        for (Matrix::len_type j = 0; j < m; j++) {
            ans[i][j] = val[i][j] - a[i][j];
        }
    }
    return ans;
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator*(const Matrix<Int>& a) const {
    if (sizej() != a.sizei()) {
        cerr << "const Matrix<Int> Matrix<Int>::operator+(const Matrix<Int> "
                "&a):Matrix size does not match!\n";
        throw;
    }
    Matrix<Int> ans(sizei(), a.sizej());
    for (Matrix::len_type i = 0; i < sizei(); i++) {
        for (Matrix::len_type j = 0; j < a.sizej(); j++) {
            for (Matrix::len_type k = 0; k < m; k++) {
                ans[i][j] += val[i][k] * a[k][j];
            }
        }
    }
    return ans;
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator*(const Matrix<Int>&& a) const {
    if (sizej() != a.sizei()) {
        cerr << "const Matrix<Int> Matrix<Int>::operator+(const Matrix<Int> "
                "&&a):Matrix size does not match!\n";
        throw;
    }
    Matrix<Int> ans(sizei(), a.sizej());
    for (Matrix::len_type i = 0; i < sizei(); i++) {
        for (Matrix::len_type j = 0; j < a.sizej(); j++) {
            for (Matrix::len_type k = 0; k < m; k++) {
                ans[i][j] += val[i][k] * a[k][j];
            }
        }
    }
    return ans;
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator*(const Int& a) const {
    Matrix<Int> ans(n, n);
    for (Matrix::len_type i = 0; i < n; i++) {
        for (Matrix::len_type j = 0; j < m; j++) {
            ans[i][j] = val[i][j] * a;
        }
    }
    return ans;
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator*(const Int&& a) const {
    Matrix<Int> ans(n, n);
    for (Matrix::len_type i = 0; i < n; i++) {
        for (Matrix::len_type j = 0; j < m; j++) {
            ans[i][j] = val[i][j] * a;
        }
    }
    return ans;
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator/(const Int& a) const {
    Matrix<Int> ans(n, n);
    for (Matrix::len_type i = 0; i < n; i++) {
        for (Matrix::len_type j = 0; j < m; j++) {
            ans[i][j] = val[i][j] / a;
        }
    }
    return ans;
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator/(const Int&& a) const {
    Matrix<Int> ans(n, n);
    for (Matrix::len_type i = 0; i < n; i++) {
        for (Matrix::len_type j = 0; j < m; j++) {
            ans[i][j] = val[i][j] / a;
        }
    }
    return ans;
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator+=(const Matrix<Int>& a) {
    return ((*this) = (*this) + a);
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator+=(const Matrix<Int>&& a) {
    return ((*this) = (*this) + a);
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator-=(const Matrix<Int>& a) {
    return ((*this) = (*this) - a);
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator-=(const Matrix<Int>&& a) {
    return ((*this) = (*this) - a);
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator*=(const Matrix<Int>& a) {
    return ((*this) = (*this) * a);
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator*=(const Matrix<Int>&& a) {
    return ((*this) = (*this) * a);
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator/=(const Int& a) {
    return ((*this) = (*this) / a);
}
template <typename Int>
const Matrix<Int> Matrix<Int>::operator/=(const Int&& a) {
    return ((*this) = (*this) / a);
}

//外部函数
template <typename Int> ostream& operator<<(ostream& os, const Matrix<Int>& a) {
    typename Matrix<Int>::len_type leni = a.sizei(), lenj = a.sizej();
    for (typename Matrix<Int>::len_type i = 0; i < leni; i++) {
        for (typename Matrix<Int>::len_type j = 0; j < lenj; j++) {
            os << a[i][j] << ' ';
        }
        os << endl;
    }
    return os;
}
template <typename Int>
ostream& operator<<(ostream& os, const Matrix<Int>&& a) {
    typename Matrix<Int>::len_type leni = a.sizei(), lenj = a.sizej();
    for (typename Matrix<Int>::len_type i = 0; i < leni; i++) {
        for (typename Matrix<Int>::len_type j = 0; j < lenj; j++) {
            os << a[i][j] << ' ';
        }
        os << endl;
    }
    return os;
}
#endif