#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include<cassert>
#include<cstddef>

#include<iostream>
#include<algorithm>

template<size_t M, size_t N, typename T = double> class Matrix;

template<size_t M, typename T = double>
using Vector = Matrix<M, 1, T>;

template<size_t M, size_t N, typename T>
void swap(Matrix<M, N, T>& lhs, Matrix<M, N, T>& rhs);

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
    Matrix<M, N, T>& operator=(Matrix<M, N, T> obj) noexcept;
    Matrix<M, N, T>& operator+=(const Matrix<M, N, T>& rhs);
    Matrix<M, N, T>& operator-=(const Matrix<M, N, T>& rhs);
    Matrix<M, N, T>& operator*=(const Matrix<M, N, T>& rhs);

    friend void swap<>(Matrix& lhs, Matrix& rhs);
    friend Matrix operator+<>(Matrix lhs, const Matrix& rhs);
    friend Matrix operator-<>(Matrix lhs, const Matrix& rhs);
    friend bool operator==<>(const Matrix& lhs, const Matrix& rhs);
    friend bool operator!=<>(const Matrix& lhs, const Matrix& rhs);
    friend std::ostream& operator<<<>(std::ostream& os, const Matrix& obj);

protected:
    T m_Data[M * N];
};

#define MATRIX_CHECK_INDEX() \
    assert(idx < (M * N) || \
        std::cerr << "Index (idx=" << idx << ") " \
                  << "out of range for " \
                  << "size (M*N=" << M * N << ")\n" \
    )
#define MATRIX_CHECK_BOUNDS() \
    assert(i < M && j < N || \
        std::cerr << "Subscript (i,j=" << i << ',' << j << ") " \
                  << "out of range for " \
                  << "bounds (M,N=" << M << ',' << N << ")\n" \
    )
#define MATRIX_CHECK_SQUARE() \
    assert(M == N || \
        std::cerr << "Dimensions (M,N=" << M << ',' << N << ") " \
                  << "are not square\n" \
    )

#include "matrix_impl.tpp"
#include "matrix_oper.tpp"

#endif/*__MATGRIX_HPP__*/