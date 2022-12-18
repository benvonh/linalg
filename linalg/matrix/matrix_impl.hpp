#ifndef __MATRIX_IMPL_HPP__
#define __MATRIX_IMPL_HPP__

#include "matrix_decl.hpp"

namespace linalg
{
template<std::size_t M, std::size_t N, typename T>
Matrix<N, N, T>
Matrix<M, N, T>::eye()
{
    __matrix_assert_square();
    Matrix<N, N, T> mat { };
    
    for (std::size_t i = 0; i < N; i++)
    {
        mat(i, i) = 1;
    }
    return mat;
}

template<std::size_t M, std::size_t N, typename T>
constexpr std::size_t
Matrix<M, N, T>::idx(std::size_t i, std::size_t j)
{
    return j + i * N;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<1, N, T>
Matrix<M, N, T>::GetRow(std::size_t i) const
{
    Matrix<1, N, T> row;

    for (std::size_t idxr = 0, idx = i * N; idxr < N; idxr++, idx++)
    {
        row[idxr] = Data[idx];
    }
    return row;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, 1, T>
Matrix<M, N, T>::GetCol(std::size_t j) const
{
    Matrix<M, 1, T> col;

    for (std::size_t idxc = 0, idx = j; idxc < M; idxc++, idx += N)
    {
        col[idxc] = Data[idx];
    }
    return col;
}

template<std::size_t M, std::size_t N, typename T>
void
Matrix<M, N, T>::SetRow(std::size_t i, const Matrix<1, N, T>& row)
{
    for (std::size_t idxr = 0, idx = i * N; idxr < N; idxr++, idx++)
    {
        Data[idx] = row[idxr];
    }
}

template<std::size_t M, std::size_t N, typename T>
void
Matrix<M, N, T>::SetCol(std::size_t j, const Matrix<M, 1, T>& col)
{
    for (std::size_t idxc = 0, idx = j; idxc < M; idxc++, idx += N)
    {
        Data[idx] = col[idxc];
    }
}

template<std::size_t M, std::size_t N, typename T>
T
Matrix<M, N, T>::Max() const
{
    return *std::max_element(
        std::cbegin(Data),
        std::cend(Data)
    );
}

template<std::size_t M, std::size_t N, typename T>
T
Matrix<M, N, T>::AbsMax() const
{
    return *std::max_element(
        std::cbegin(Data),
        std::cend(Data),
        [](const T& a, const T& b) -> bool
        {
            return std::abs(a) < std::abs(b);
        }
    );
}

template<std::size_t M, std::size_t N, typename T>
T
Matrix<M, N, T>::Determinant() const
{
    auto[L, U] = LU_Decomposition();
    T det = U[0];
    
    for (std::size_t i = 1; i < N; i++)
    {
        det *= U(i, i);
    }
    return det;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<1, N, T>
Matrix<M, N, T>::Product() const
{
    Matrix<1, N, T> mat;

    for (std::size_t j = 0; j < N; j++)
    {
        mat[j] = Data[j];

        for (std::size_t i = 1; i < M; i++)
        {
            mat[j] *= Data[idx(i, j)];
        }
    }
    return mat;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<N, M, T>
Matrix<M, N, T>::Transpose() const
{
    Matrix<N, M, T> mat;

    for (std::size_t i = 0; i < M; i++)
    {
        for (std::size_t j = 0; j < N; j++)
        {
            mat(j, i) = Data[idx(i, j)];
        }
    }
    return mat;
}

template<std::size_t M, std::size_t N, typename T>
std::pair<Matrix<N, N, T>, Matrix<N, N, T>>
Matrix<M, N, T>::LU_Decomposition() const
{
    __matrix_assert_square();
    Matrix<N, N, T> lower = Matrix<N, N, T>::eye();
    Matrix<N, N, T> upper = *this;

    for (std::size_t j = 0; j < N; j++)
    {
        T pivot = upper(j, j);

        for (std::size_t i = j + 1; i < N; i++)
        {
            lower(i, j) = upper(i, j) / pivot;
            upper.SetRow(i, upper.GetRow(i) - lower(i, j) * upper.GetRow(j));
        }
    }
    return std::make_pair(lower, upper);
}
}

#endif/*__MATRIX_IMPL_HPP__*/
