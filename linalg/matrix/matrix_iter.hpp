/**
 * @file matrix_iter.hpp
 * @author Benjamin von Snarski (benjaminvonsnarski@gmail.com)
 * @brief Header file for matrix iterator definition.
 * @version 0.1
 * @date 19-12-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __MATRIX_ITER_HPP__
#define __MATRIX_ITER_HPP__

#include "matrix_decl.hpp"

namespace linalg
{
template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T>::Iterator::Iterator(T* ptr) : m_Ptr(ptr)
{
}

template<std::size_t M, std::size_t N, typename T>
T*
Matrix<M, N, T>::Iterator::operator->()
{
    return m_Ptr;
}

template<std::size_t M, std::size_t N, typename T>
T&
Matrix<M, N, T>::Iterator::operator*() const
{
    return *m_Ptr;
}

template<std::size_t M, std::size_t N, typename T>
typename Matrix<M, N, T>::Iterator
Matrix<M, N, T>::Iterator::operator++(T)
{
    Iterator tmp = *this;
    return tmp++;
}

template<std::size_t M, std::size_t N, typename T>
typename Matrix<M, N, T>::Iterator&
Matrix<M, N, T>::Iterator::operator++()
{
    return m_Ptr++, *this;
}

template<std::size_t M, std::size_t N, typename T>
bool
operator==(const typename Matrix<M, N, T>::Iterator& lhs,
           const typename Matrix<M, N, T>::Iterator& rhs)
{
    return lhs.m_Ptr == rhs.m_Ptr;
}

template<std::size_t M, std::size_t N, typename T>
bool
operator!=(const typename Matrix<M, N, T>::Iterator& lhs,
           const typename Matrix<M, N, T>::Iterator& rhs)
{
    return !(lhs == rhs);
}

template<std::size_t M, std::size_t N, typename T>
typename Matrix<M, N, T>::Iterator
Matrix<M, N, T>::end()
{
    return Iterator(&Data[M * N]);
}

template<std::size_t M, std::size_t N, typename T>
typename Matrix<M, N, T>::Iterator
Matrix<M, N, T>::begin()
{
    return Iterator(&Data);
}

template<std::size_t M, std::size_t N, typename T>
const typename Matrix<M, N, T>::Iterator
Matrix<M, N, T>::cend() const
{
    return Iterator(&Data[M * N]);
}

template<std::size_t M, std::size_t N, typename T>
const typename Matrix<M, N, T>::Iterator
Matrix<M, N, T>::cbegin() const
{
    return Iterator(&Data);
}
}

#endif/*__MATRIX_ITER_HPP__*/
