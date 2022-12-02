#ifndef __MATRIX_OPER_TPP__
#define __MATRIX_OPER_TPP__

#include "matrix.hpp"

template<size_t M, size_t N, typename T>
T& Matrix<M, N, T>::operator()(size_t i, size_t j)
{
    MATRIX_CHECK_BOUNDS();
    return m_Data[i][j];
}

template<size_t M, size_t N, typename T>
const T& Matrix<M, N, T>::operator()(size_t i, size_t j) const
{
    MATRIX_CHECK_BOUNDS();
    return m_Data[i][j];
}

template<size_t M, size_t N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator=(Matrix<M, N, T> rhs) noexcept
{
    for (size_t i = 0; i < N; i++)
    {
        std::swap(m_Data[i], rhs.m_Data[i]);
    }
    return *this;
}

template<size_t M, size_t N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator+=(const Matrix<M, N, T>& rhs)
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            m_Data[i][j] += rhs(i, j);
        }
    }
    return *this;
}
    
template<size_t M, size_t N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator-=(const Matrix<M, N, T>& rhs)
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            m_Data[i][j] -= rhs(i, j);
        }
    }
    return *this;
}

template<size_t M, size_t N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator*=(const Matrix<M, N, T>& rhs)
{
    Matrix<M, N, T> cpy = *this;

    for (size_t i = 0; i < M; i++)
    {
        for (size_t k = 0; k < N; k++)
        {
            T cell = 0;

            for (size_t j = 0; j < N; j++)
            {
                cell += cpy(i, j) * rhs(j, k);
            }
            m_Data[i][k] = cell;
        }
    }
    return *this;
}

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator+(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs)
{
    lhs += rhs;
    return lhs;
}

template<size_t M, size_t N, typename T>
Matrix<M, N, T> operator-(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs)
{
    lhs -= rhs;
    return lhs;
}
    
template<size_t M, size_t N, size_t K, typename T>
Matrix<M, K, T> operator*(Matrix<M, N, T> lhs, const Matrix<N, K, T>& rhs)
{
    if (M == N)
    {
        lhs *= rhs;
        return lhs;
    }
    else
    {
        Matrix<M, N, T> obj;

        for (size_t i = 0; i < M; i++)
        {
            for (size_t k = 0; k < K; k++)
            {
                T cell = 0;

                for (size_t j = 0; j < N; j++)
                {
                    cell += lhs(i, j) * rhs(j, k);
                }
                obj(i, k) = cell;
            }
        }
        return obj;
    }
}

template<size_t M, size_t N, typename T>
bool operator==(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs)
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (lhs(i, j) != rhs(i, j))
                return false;
        }
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
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            os << obj.m_Data[i][j];
            os << (j < N - 1 ? ", " : "\n");
        }
    }
    return os;
}

#endif/*__MATRIX_OPER_TPP__*/