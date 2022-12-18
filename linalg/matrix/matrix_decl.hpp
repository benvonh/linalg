#ifndef __MATRIX_DECL_HPP__
#define __MATRIX_DECL_HPP__

#include<cmath>
#include<cstddef>
#include<cstdlib>

#include<iomanip>
#include<sstream>
#include<utility>
#include<iostream>
#include<iterator>
#include<algorithm>
#include<stdexcept>
#include<functional>

#ifndef MATRIX_PRINT_PRECISION
#define MATRIX_PRINT_PRECISION 2
#elif MATRIX_PRINT_PRECISION < 0
#error MATRIX_PRINT_PRECISION must be positive
#endif

#ifndef MATRIX_OPTIMISE
#define __matrix_assert(expr, except, msg) \
        if (!(expr)) \
        { \
            std::ostringstream oss; \
            oss << __PRETTY_FUNCTION__ << ':' << msg; \
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
#define __matrix_assert_square() \
        __matrix_assert(M == N, std::logic_error, \
            "Matrix of dimension (" << M << ", " << N << ") " \
            "not square")
#elif
#define __matrix_assert_index()
#define __matrix_assert_bounds()
#define __matrix_assert_square()
#endif

namespace linalg
{
template<std::size_t M, std::size_t N, typename T = double> struct Matrix;

template<std::size_t M, typename T = double>
using Vector = Matrix<M, 1, T>;

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> operator+(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> operator-(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> operator*(Matrix<M, N, T> lhs, T rhs);

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> operator*(T lhs, Matrix<M, N, T> rhs);

template<std::size_t M, std::size_t N, std::size_t K, typename T>
Matrix<M, K, T> operator*(Matrix<M, N, T> lhs, const Matrix<N, K, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
bool operator==(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
bool operator!=(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& obj);

template<std::size_t M, std::size_t N, typename T>
struct Matrix
{
    T Data[M * N];

    static inline Matrix<N, N, T> eye();
    static inline constexpr std::size_t idx(std::size_t i, std::size_t j);

    Matrix<1, N, T> GetRow(std::size_t i) const;
    Matrix<M, 1, T> GetCol(std::size_t j) const;
    void SetRow(std::size_t i, const Matrix<1, N, T>& row);
    void SetCol(std::size_t j, const Matrix<M, 1, T>& col);

    T Max() const;
    T AbsMax() const;
    T Determinant() const;
    Matrix<1, N, T> Product() const;
    Matrix<N, M, T> Transpose() const;
    std::pair<Matrix<N, N, T>, Matrix<N, N, T>> LU_Decomposition() const;

    T& operator[](std::size_t idx);
    T& operator()(std::size_t i, std::size_t j);
    const T& operator[](std::size_t idx) const;
    const T& operator()(std::size_t i, std::size_t j) const;
    Matrix<M, N, T>& operator+=(const Matrix<M, N, T>& rhs);
    Matrix<M, N, T>& operator-=(const Matrix<M, N, T>& rhs);
    Matrix<M, N, T>& operator*=(const Matrix<N, N, T>& rhs);
    Matrix<M, N, T>& operator*=(T rhs);

    friend Matrix operator+<>(Matrix lhs, const Matrix& rhs);
    friend Matrix operator-<>(Matrix lhs, const Matrix& rhs);
    friend Matrix operator*<>(Matrix lhs, T rhs);
    friend Matrix operator*<>(T lhs, Matrix rhs);
    friend bool operator==<>(const Matrix& lhs, const Matrix& rhs);
    friend bool operator!=<>(const Matrix& lhs, const Matrix& rhs);
    friend std::ostream& operator<<<>(std::ostream& os, const Matrix& obj);

    class Iterator
    {
    public:
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        Iterator(T* ptr);
        
        T* operator->();
        T& operator*() const;
        Iterator operator++(T);
        Iterator& operator++();
        friend bool operator==<>(const Iterator& lhs, const Iterator& rhs);
        friend bool operator!=<>(const Iterator& lhs, const Iterator& rhs);

    private:
        T* m_Ptr;
    };
    Iterator end();
    Iterator begin();
    const Iterator cend() const;
    const Iterator cbegin() const;
};
template<std::size_t M, std::size_t N, typename T>
bool operator==(const typename Matrix<M, N, T>::Iterator& lhs,
                const typename Matrix<M, N, T>::Iterator& rhs);

template<std::size_t M, std::size_t N, typename T>
bool operator!=(const typename Matrix<M, N, T>::Iterator& lhs,
                const typename Matrix<M, N, T>::Iterator& rhs);
}

#endif/*__MATGRIX_DECL_HPP__*/
