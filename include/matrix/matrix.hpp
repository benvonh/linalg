#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include<cstddef>
#include<cstdlib>

#include<sstream>
#include<iomanip>
#include<iostream>
#include<iterator>
#include<algorithm>
#include<stdexcept>

#ifndef MATRIX_PRINT_PRECISION
    #define MATRIX_PRINT_PRECISION 2
#elif MATRIX_PRINT_PRECISION < 0
    #error "MATRIX_PRINT_PRECISION must be not be negative"
#endif

#define MATRIX_CHECK(expr, excp, msg) if (!(expr)) \
        throw excp(( \
            std::ostringstream() << msg << \
            " from function Matrix<M, N, T>::" << __FUNCTION__ << "(...)\n" \
        ).str())

#define MATRIX_CHECK_INDEX \
        MATRIX_CHECK( \
            idx < M * N, \
            std::out_of_range, \
            "Index (" << idx << ") out of range for " \
            "dimension (" << M << ", " << N << ")" \
        )

#define MATRIX_CHECK_BOUNDS \
        MATRIX_CHECK( \
            i < M && j < N, \
            std::out_of_range, \
            "Index (" << i << ", " << j << ") out of range for " \
            "dimension (" << M << ", " << N << ")" \
        )

#define MATRIX_CHECK_SQUARE \
        MATRIX_CHECK( \
            M == N, \
            std::logic_error, \
            "Dimension (" << M << ", " << N << ") not a square matrix" \
        )

namespace linalg
{
template<size_t M, size_t N, typename T = double> class Matrix;

template<size_t M, typename T = double>
using Vector = Matrix<M, 1, T>;

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator+(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs);

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator-(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs);

template<size_t M, size_t N, size_t K, typename T>
Matrix<M, K, T> operator*(Matrix<M, N, T> lhs, const Matrix<N, K, T>& rhs);

template<size_t M, size_t N, typename T>
bool operator==(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs);

template<size_t M, size_t N, typename T>
bool operator!=(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs);

template<size_t M, size_t N, typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& obj);

template<size_t M, size_t N, typename T>
class Matrix
{
public:
    Matrix() = default;
    ~Matrix() = default;

    static constexpr Matrix<M, N, T> eye();
    static constexpr size_t idx(size_t i, size_t j);

    Matrix<N, M, T> Transpose() const;

    T& operator[](size_t idx);
    T& operator()(size_t i, size_t j);
    const T& operator[](size_t idx) const;
    const T& operator()(size_t i, size_t j) const;
    Matrix<M, N, T>& operator+=(const Matrix<M, N, T>& rhs);
    Matrix<M, N, T>& operator-=(const Matrix<M, N, T>& rhs);
    Matrix<M, N, T>& operator*=(const Matrix<M, N, T>& rhs);

    friend Matrix operator+<>(Matrix lhs, const Matrix& rhs);
    friend Matrix operator-<>(Matrix lhs, const Matrix& rhs);
    friend bool operator==<>(const Matrix& lhs, const Matrix& rhs);
    friend bool operator!=<>(const Matrix& lhs, const Matrix& rhs);
    friend std::ostream& operator<<<>(std::ostream& os, const Matrix& obj);

protected:
    T m_Data[M * N];
};
};

#include "matrix_impl.tpp"
#include "matrix_oper.tpp"

#endif/*__MATGRIX_HPP__*/