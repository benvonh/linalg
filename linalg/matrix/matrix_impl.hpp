#ifndef __MATRIX_IMPL_HPP__
#define __MATRIX_IMPL_HPP__

#include "matrix_decl.hpp"

namespace linalg
{
template<std::size_t M, std::size_t N, typename T>
constexpr Matrix<M, M, T> Matrix<M, N, T>::eye()
{
    Matrix<M, M, T> mat{};
    
    for (std::size_t i = 0; i < M; i++)
    {
        mat(i, i) = 1;
    }
    return mat;
}

template<std::size_t M, std::size_t N, typename T>
constexpr std::size_t Matrix<M, N, T>::idx(std::size_t i, std::size_t j)
{
    return j + i * N;
}

template<std::size_t M, std::size_t N, typename T>
constexpr T Matrix<M, N, T>::det(const Matrix<M, M, T>& mat) 
{
    // TODO: HOW TO DO??? :sad:
    if constexpr(M == 2) { return mat[0] * mat[3] - mat[1] * mat[2]; }

    T det = 0;

    for (std::size_t col = 0; col < N; col++)
    {
        Matrix<M - 1, N - 1, T> tmp;

        for (std::size_t i = 1, p = 0; i < M; i++, p++)
        {
            for (std::size_t j = 0, q = 0; j < N; j++, q++)
            {
                if (j == col) { q--; continue; }
                tmp(p, q) = mat(i, j);
            }
        }
        det += (col % 2 ? -1 : 1) * mat[col] * tmp.Determinant();
    }
    return det;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<N, M, T> Matrix<M, N, T>::Transpose() const
{
    Matrix<N, M, T> mat;

    for (std::size_t i = 0; i < M; i++)
    {
        for (std::size_t j = 0; j < N; j++)
        {
            mat(j, i) = m_Data[idx(i, j)];
        }
    }
    return mat;
}

template<std::size_t M, std::size_t N, typename T>
T Matrix<M, N, T>::Determinant() const
{
    return Matrix<M, N, T>::det(*this);
}
}

#endif/*__MATRIX_IMPL_HPP__*/
