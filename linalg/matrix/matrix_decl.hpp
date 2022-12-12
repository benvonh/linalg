#ifndef __MATRIX_DECL_HPP__
#define __MATRIX_DECL_HPP__

#include<cstddef>
#include<cstdlib>

#include<algorithm>
#include<iomanip>
#include<iostream>
#include<iterator>
#include<sstream>
#include<stdexcept>

#ifndef MATRIX_PRINT_PRECISION
    #define MATRIX_PRINT_PRECISION 2
#elif MATRIX_PRINT_PRECISION < 0
    #error MATRIX_PRINT_PRECISION must be not be negative
#endif

#define __matrix_assert(expr, except, msg) \
        if (!(expr)) \
        { \
            std::ostringstream oss; \
            oss << __PRETTY_FUNCTION__ << '\n' << msg; \
            throw except(oss.str()); \
        }

#define __matrix_assert_index() \
        __matrix_assert(idx < M * N, std::out_of_range, \
            "Index (" << idx << ") out of range for " \
            "dimension (" << M << ", " << N << ')')

#define __matrix_assert_bounds() \
        __matrix_assert(i < M && j < N, std::out_of_range, \
            "Index (" << i << ", " << j << ") out of range for " \
            "dimension (" << M << ", " << N << ')')

namespace linalg
{
template<std::size_t M, std::size_t N, typename T = double> class Matrix;

template<std::size_t M, typename T = double>
using Vector = Matrix<M, 1, T>;

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> operator+(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> operator-(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs);

template<std::size_t M, std::size_t N, std::size_t K, typename T>
Matrix<M, K, T> operator*(Matrix<M, N, T> lhs, const Matrix<N, K, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
bool operator==(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
bool operator!=(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& obj);

template<std::size_t M, std::size_t N, typename T>
class Matrix
{
public:
    Matrix() = default;
    ~Matrix() = default;

    static constexpr Matrix<M, M, T> eye();
    static constexpr std::size_t idx(std::size_t i, std::size_t j);
    static constexpr T det(const Matrix<M, M, T>& mat);

    Matrix<N, M, T> Transpose() const;
    T Determinant() const;

    T& operator[](std::size_t idx);
    T& operator()(std::size_t i, std::size_t j);
    const T& operator[](std::size_t idx) const;
    const T& operator()(std::size_t i, std::size_t j) const;
    Matrix<M, N, T>& operator+=(const Matrix<M, N, T>& rhs);
    Matrix<M, N, T>& operator-=(const Matrix<M, N, T>& rhs);
    Matrix<M, M, T>& operator*=(const Matrix<M, M, T>& rhs);

    friend Matrix operator+<>(Matrix lhs, const Matrix& rhs);
    friend Matrix operator-<>(Matrix lhs, const Matrix& rhs);
    friend bool operator==<>(const Matrix& lhs, const Matrix& rhs);
    friend bool operator!=<>(const Matrix& lhs, const Matrix& rhs);
    friend std::ostream& operator<<<>(std::ostream& os, const Matrix& obj);

protected:
    T m_Data[M * N];
};
}

#endif/*__MATGRIX_DECL_HPP__*/
