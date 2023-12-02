#ifndef __LINALG__MATRIX_HPP__
#define __LINALG__MATRIX_HPP__

#include<cstddef>
#include<iostream>

namespace linalg
{
template<std::size_t M, std::size_t N, typename T = double>
struct Matrix
{
  T _M_Data_[M * N];

  Matrix() = default;
  ~Matrix() = default;

  Matrix(const Matrix&) = default;
  Matrix& operator=(const Matrix&) = default;

  Matrix(Matrix&&) = delete;
  Matrix& operator=(Matrix&&) = delete;

  constexpr const T operator()(std::size_t i, std::size_t j) const noexcept
  {
    return _M_Data_[i * N + j];
  }

  constexpr T& operator()(std::size_t i, std::size_t j) noexcept
  {
    return _M_Data_[i * N + j];
  }

  constexpr const T operator[](std::size_t idx) const noexcept
  {
    return _M_Data_[idx];
  }

  constexpr T& operator[](std::size_t idx) noexcept
  {
    return _M_Data_[idx];
  }

  constexpr Matrix& operator+=(const Matrix& rhs) noexcept
  {
    for (std::size_t idx = 0UL; idx < M * N; idx++)
    {
      _M_Data_[idx] += rhs[idx];
    }

    return *this;
  }

  constexpr Matrix& operator-=(const Matrix& rhs) noexcept
  {
    for (std::size_t idx = 0UL; idx < M * N; idx++)
    {
      _M_Data_[idx] -= rhs[idx];
    }

    return *this;
  }

  constexpr Matrix& operator*=(const Matrix& rhs) noexcept
  {
    Matrix tmp(*this);

    for (std::size_t ai = 0UL; ai < M; ai++)
    {
      for (std::size_t bj = 0UL; bj < N; bj++)
      {
        (*this)(ai, bj) = (T)0;

        for (std::size_t k = 0UL; k < N; k++)
        {
          (*this)(ai, bj) += tmp(ai, k) * rhs(k, bj);
        }
      }
    }

    return *this;
  }

  friend constexpr Matrix operator+(Matrix lhs, const Matrix& rhs)
  {
    lhs += rhs;
    return lhs;
  }

  friend constexpr Matrix operator-(Matrix lhs, const Matrix& rhs)
  {
    lhs -= rhs;
    return lhs;
  }

  friend constexpr Matrix operator*(Matrix lhs, const Matrix& rhs)
  {
    lhs *= rhs;
    return lhs;
  }
};

template<std::size_t M, std::size_t N, typename T>
constexpr std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& obj)
{
  for (std::size_t i = 0UL; i < M; i++)
  {
    os << "[ ";

    for (std::size_t j = 0UL; j < N - 1; j++)
    {
      os << obj(i, j) << ", ";
    }

    os << obj(i, N - 1) << " ]\n";
  }

  return os;
}
} // namespace linalg

#endif/*__LINALG__MATRIX_HPP__*/