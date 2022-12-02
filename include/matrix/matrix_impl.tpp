#ifndef __MATRIX_IMPL_TPP__
#define __MATRIX_IMPL_TPP__

#include "matrix.hpp"

template<size_t M, size_t N, typename T>
Matrix<M, N, T> Matrix<M, N, T>::Eye()
{
    assert(M == N);
    Matrix<M, N, T> obj;
    
    for (size_t i = 0; i < M; i++)
    {
        obj(i, i) = 1;
    }
    return obj;
}

template<size_t M, size_t N, typename T>
constexpr size_t Matrix<M, N, T>::GetRows() const
{
    return c_Rows;
}

template<size_t M, size_t N, typename T>
constexpr size_t Matrix<M, N, T>::GetCols() const
{
    return c_Cols;
}
    
template<size_t M, size_t N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::Transpose()
{
    assert(M == N);
    
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = i + 1; j < N; j++)
        {
            T tmp = m_Data[i][j];
            m_Data[i][j] = m_Data[j][i];
            m_Data[j][i] = tmp;
        }
    }
    return *this;
}

// template<size_t M, size_t N, typename T>
// Matrix<M, N, T> Matrix<M, N, T>::Row(size_t row)
// {
//     return Matrix<1, N, T>(m_Data[i]);
// }

#endif/*__MATRIX_IMPL_TPP__*/