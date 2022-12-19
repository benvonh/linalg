/**
 * @file matrix_oper.hpp
 * @author Benjamin von Snarski (benjaminvonsnarski@gmail.com)
 * @brief Header file for overloaded matrix operators.
 * @version 0.1
 * @date 19-12-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __MATRIX_OPER_HPP__
#define __MATRIX_OPER_HPP__

#include "matrix_decl.hpp"

namespace linalg
{
template<std::size_t M, std::size_t N, typename T>
T&
Matrix<M, N, T>::operator[](std::size_t idx)
{
    __matrix_assert_index();
    return Data[idx];
}

template<std::size_t M, std::size_t N, typename T>
T&
Matrix<M, N, T>::operator()(std::size_t i, std::size_t j)
{
    __matrix_assert_bounds();
    return Data[idx(i, j)];
}

template<std::size_t M, std::size_t N, typename T>
T
Matrix<M, N, T>::operator[](std::size_t idx) const
{
    __matrix_assert_index();
    return Data[idx];
}

template<std::size_t M, std::size_t N, typename T>
T
Matrix<M, N, T>::operator()(std::size_t i, std::size_t j) const
{
    __matrix_assert_bounds();
    return Data[idx(i, j)];
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>&
Matrix<M, N, T>::operator+=(const Matrix<M, N, T>& rhs)
{
    for (std::size_t idx = 0; idx < M * N; idx++)
    {
        Data[idx] += rhs[idx];
    }
    return *this;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>&
Matrix<M, N, T>::operator-=(const Matrix<M, N, T>& rhs)
{
    for (std::size_t idx = 0; idx < M * N; idx++)
    {
        Data[idx] -= rhs[idx];
    }
    return *this;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>&
Matrix<M, N, T>::operator*=(const Matrix<N, N, T>& rhs)
{
    Matrix<M, M, T> cpy = *this;

    for (std::size_t i = 0; i < M; i++)
    {
        for (std::size_t j = 0; j < N; j++)
        {
            T cell = 0;

            for (std::size_t k = 0; k < N; k++)
            {
                cell += cpy(i, k) * rhs(k, j);
            }
            Data[idx(i, j)] = cell;
        }
    }
    return *this;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>&
Matrix<M, N, T>::operator*=(T rhs)
{
    for (std::size_t idx = 0; idx < M * N; idx++)
    {
        Data[idx] *= rhs;
    }
    return *this;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>
operator+(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs)
{
    return lhs += rhs;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>
operator-(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs)
{
    return lhs -= rhs;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>
operator*(Matrix<M, N, T> lhs, T rhs)
{
    return lhs *= rhs;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>
operator*(T lhs, Matrix<M, N, T> rhs)
{
    return rhs *= lhs;
}

template<std::size_t M, std::size_t N, std::size_t K, typename T>
Matrix<M, K, T>
operator*(Matrix<M, N, T> lhs, const Matrix<N, K, T>& rhs)
{
    Matrix<M, K, T> mat;

    for (std::size_t i = 0; i < M; i++)
    {
        for (std::size_t k = 0; k < K; k++)
        {
            T cell = 0;

            for (std::size_t j = 0; j < N; j++)
            {
                cell += lhs(i, j) * rhs(j, k);
            }
            mat(i, k) = cell;
        }
    }
    return mat;
}

template<std::size_t M, std::size_t N, typename T>
bool
operator==(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs)
{
    for (std::size_t idx = 0; idx < M * N; idx++)
    {
        if (lhs[idx] != rhs[idx])
            return false;
    }
    return true;
}

template<std::size_t M, std::size_t N, typename T>
bool
operator!=(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs)
{
    return !(lhs == rhs);
}

template<std::size_t M, std::size_t N, typename T>
std::ostream&
operator<<(std::ostream& os, const Matrix<M, N, T>& obj)
{
    long max = static_cast<long>(obj.AbsMax());
    long digits = static_cast<long>(max < 0) + 1L;

    do { digits++; } while (max /= 10);

    long width = digits + MATRIX_PRINT_PRECISION + 1;
    os << std::setprecision(MATRIX_PRINT_PRECISION) << std::fixed;

    for (std::size_t i = 0; i < M; i++)
    {
        os << "[ ";

        for (std::size_t j = 0; j < N; j++)
        {
            os << std::setw(width) << obj(i, j);
            os << (j != N - 1 ? ", " : " ]\n");
        }
    }
    return os;
}
}

#endif/*__MATRIX_OPER_HPP__*/
