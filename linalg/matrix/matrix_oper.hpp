#ifndef __MATRIX_OPER_HPP__
#define __MATRIX_OPER_HPP__

#include "matrix_decl.hpp"

namespace linalg
{
template<std::size_t M, std::size_t N, typename T>
T& Matrix<M, N, T>::operator[](std::size_t idx)
{
    __matrix_assert_index();
    return m_Data[idx];
}

template<std::size_t M, std::size_t N, typename T>
T& Matrix<M, N, T>::operator()(std::size_t i, std::size_t j)
{
    __matrix_assert_bounds();
    return m_Data[idx(i, j)];
}

template<std::size_t M, std::size_t N, typename T>
const T& Matrix<M, N, T>::operator[](std::size_t idx) const
{
    __matrix_assert_index();
    return m_Data[idx];
}

template<std::size_t M, std::size_t N, typename T>
const T& Matrix<M, N, T>::operator()(std::size_t i, std::size_t j) const
{
    __matrix_assert_bounds();
    return m_Data[idx(i, j)];
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator+=(const Matrix<M, N, T>& rhs)
{
    for (std::size_t idx = 0; idx < M * N; idx++)
    {
        m_Data[idx] += rhs[idx];
    }
    return *this;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator-=(const Matrix<M, N, T>& rhs)
{
    for (std::size_t idx = 0; idx < M * N; idx++)
    {
        m_Data[idx] -= rhs[idx];
    }
    return *this;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, M, T>& Matrix<M, N, T>::operator*=(const Matrix<M, M, T>& rhs)
{
    Matrix<M, M, T> cpy = *this;

    for (std::size_t i = 0; i < M; i++)
    {
        for (std::size_t j = 0; j < N; j++)
        {
            T cel = 0;

            for (std::size_t k = 0; k < N; k++)
            {
                cel += cpy(i, k) * rhs(k, j);
            }
            m_Data[idx(i, j)] = cel;
        }
    }
    return *this;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> operator+(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs)
{
    return lhs += rhs;
}

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> operator-(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs)
{
    return lhs -= rhs;
}

template<std::size_t M, std::size_t N, std::size_t K, typename T>
Matrix<M, K, T> operator*(Matrix<M, N, T> lhs, const Matrix<N, K, T>& rhs)
{
    Matrix<M, K, T> mat;

    for (std::size_t i = 0; i < M; i++)
    {
        for (std::size_t k = 0; k < K; k++)
        {
            T cel = 0;

            for (std::size_t j = 0; j < N; j++)
            {
                cel += lhs(i, j) * rhs(j, k);
            }
            mat(i, k) = cel;
        }
    }
    return mat;
}

template<std::size_t M, std::size_t N, typename T>
bool operator==(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs)
{
    for (std::size_t idx = 0; idx < M * N; idx++)
    {
        if (lhs[idx] != rhs[idx])
            return false;
    }
    return true;
}

template<std::size_t M, std::size_t N, typename T>
bool operator!=(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs)
{
    return !(lhs == rhs);
}

template<std::size_t M, std::size_t N, typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& obj)
{
    long max_num = static_cast<long>(
        *std::max_element(
            std::cbegin(obj.m_Data),
            std::cend(obj.m_Data),
            [](const T& a, const T& b) -> bool
            {
                return std::abs(a) < std::abs(b);
            }
        )
    );
    long digits = static_cast<long>(max_num < 0) + 1;

    do { digits++; } while (max_num /= 10);

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
};

#endif/*__MATRIX_OPER_HPP__*/
