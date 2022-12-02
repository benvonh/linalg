#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include<cassert>
#include<cstddef>

#include<utility>
#include<iostream>

#define MATRIX_CHECK_BOUNDS()   assert(i < M && j < N)

template<size_t M, size_t N, typename T = double> class Matrix;

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator+(Matrix<M, N, T>, const Matrix<M, N, T>&);

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator-(Matrix<M, N, T>, const Matrix<M, N, T>&);

template<size_t M, size_t N, size_t K, typename T>
Matrix<M, K, T> operator*(Matrix<M, N, T>, const Matrix<N, K, T>&);

template<size_t M, size_t N, typename T>
bool operator==(const Matrix<M, N, T>&, const Matrix<M, N, T>&);

template<size_t M, size_t N, typename T>
bool operator!=(const Matrix<M, N, T>&, const Matrix<M, N, T>&);

template<size_t M, size_t N, typename T>
std::ostream& operator<<(std::ostream&, const Matrix<M, N, T>&);

template<size_t M, size_t N, typename T>
class Matrix
{
public:
    Matrix() = default;
    virtual ~Matrix() = default;
    static Matrix<M, N, T> Eye();
    constexpr size_t GetRows() const;
    constexpr size_t GetCols() const;
    Matrix<M, N, T>& Transpose();

    T& operator()(size_t i, size_t j);
    const T& operator()(size_t i, size_t j) const;
    Matrix<M, N, T>& operator=(Matrix<M, N, T> rhs) noexcept;
    Matrix<M, N, T>& operator+=(const Matrix<M, N, T>& rhs);
    Matrix<M, N, T>& operator-=(const Matrix<M, N, T>& rhs);
    Matrix<M, N, T>& operator*=(const Matrix<M, N, T>& rhs);

private:
    friend Matrix operator+<>(Matrix<M, N, T> lhs, const Matrix& rhs);
    friend Matrix operator-<>(Matrix<M, N, T> lhs, const Matrix& rhs);
    friend Matrix operator*<>(Matrix<M, N, T> lhs, const Matrix& rhs);
    friend bool operator==<>(const Matrix<M, N, T>& lhs, const Matrix& rhs);
    friend bool operator!=<>(const Matrix<M, N, T>& lhs, const Matrix& rhs);
    friend std::ostream& operator<<<>(std::ostream& os, const Matrix& obj);

protected:
    const size_t c_Rows = M;
    const size_t c_Cols = N;
    T m_Data[M][N];
};

#include "matrix_oper.tpp"
#include "matrix_impl.tpp"

#endif/*__MATRIX_HPP__*/