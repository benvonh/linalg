#ifndef __MATRIX_OPER_TPP__
#define __MATRIX_OPER_TPP__

#include "matrix.hpp"

template<size_t M, size_t N, typename T>
T& Matrix<M, N, T>::operator[](size_t idx)
{
    MATRIX_CHECK_INDEX();
    return m_Data[idx];
}

template<size_t M, size_t N, typename T>
T& Matrix<M, N, T>::operator()(size_t i, size_t j)
{
    MATRIX_CHECK_BOUNDS();
    return m_Data[idx(i, j)];
}

template<size_t M, size_t N, typename T>
const T& Matrix<M, N, T>::operator[](size_t idx) const
{
    MATRIX_CHECK_INDEX();
    return m_Data[idx];
}

template<size_t M, size_t N, typename T>
const T& Matrix<M, N, T>::operator()(size_t i, size_t j) const
{
    MATRIX_CHECK_BOUNDS();
    return m_Data[idx(i, j)];
}

template<size_t M, size_t N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator=(Matrix<M, N, T> obj) noexcept
{
    swap(*this, obj);
    return *this;
}

template<size_t M, size_t N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator+=(const Matrix<M, N, T>& rhs)
{
    for (size_t idx = 0; idx < M * N; idx++)
    {
        m_Data[idx] += rhs[idx];
    }
    return *this;
}

template<size_t M, size_t N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator-=(const Matrix<M, N, T>& rhs)
{
    for (size_t idx = 0; idx < M * N; idx++)
    {
        m_Data[idx] -= rhs[idx];
    }
    return *this;
}

template<size_t M, size_t N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator*=(const Matrix<M, N, T>& rhs)
{
    MATRIX_CHECK_SQUARE();
    Matrix<M, N, T> cpy;

    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            T cel = 0;

            for (size_t k = 0; k < N; k++)
            {
                cel += cpy(i, k) * rhs(k, j);
            }
            m_Data[idx(i, j)] = cel;
        }
    }
    return *this;
}

template<size_t M, size_t N, typename T>
void swap(Matrix<M, N, T>& lhs, Matrix<M, N, T>& rhs)
{
    std::swap(lhs.m_Data, rhs.m_Data);
}

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator+(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs)
{
    return lhs += rhs;
}

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator-(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs)
{
    return lhs -= rhs;
}

template<size_t M, size_t N, size_t K, typename T>
Matrix<M, K, T> operator*(Matrix<M, N, T> lhs, const Matrix<N, K, T>& rhs)
{
    Matrix<M, K, T> obj;

    for (size_t i = 0; i < M; i++)
    {
        for (size_t k = 0; k < K; k++)
        {
            T cel = 0;

            for (size_t j = 0; j < N; j++)
            {
                cel += lhs(i, j) * rhs(j, k);
            }
            obj(i, k) = cel;
        }
    }
    return obj;
}

template<size_t M, size_t N, typename T>
bool operator==(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs)
{
    for (size_t idx = 0; idx < M * N; idx++)
    {
        if (lhs[idx] != rhs[idx])
            return false;
    }
    return true;
}

template<size_t M, size_t N, typename T>
bool operator!=(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs)
{
    return !(lhs == rhs);
}

template<size_t M, size_t N, typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& obj)
{
    os << "[ ";
    for (size_t idx = 0; idx < M * N; idx++)
    {
        os << obj[idx];
        os << (((idx + 1) % N) ? ", " : " ]\n[ ");
    }
    return os;
}

#endif/*__MATRIX_OPER_TPP__*/