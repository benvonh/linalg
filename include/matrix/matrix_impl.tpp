#ifndef __MATRIX_IMPL_TPP__
#define __MATRIX_IMPL_TPP__

#include "matrix.hpp"

template<size_t M, size_t N, typename T>
constexpr Matrix<M, N, T> Matrix<M, N, T>::eye()
{
    MATRIX_CHECK_SQUARE();
    Matrix<M, N, T> obj{};
    
    for (size_t ij = 0; ij < M; ij++)
    {
        obj(ij, ij) = 1;
    }
    return obj;
}

template<size_t M, size_t N, typename T>
constexpr size_t Matrix<M, N, T>::idx(size_t i, size_t j)
{
    return j + i * N;
}

template<size_t M, size_t N, typename T>
Matrix<N, M, T> Matrix<M, N, T>::Transpose() const
{
    Matrix<N, M, T> obj;

    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            obj(j, i) = m_Data[idx(i, j)];
        }
    }
    return obj;
}

#endif/*__MATRIX_IMPL_TPP__*/