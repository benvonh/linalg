/**
 * @file matrix_decl.hpp
 * @author Benjamin von Snarski (benjaminvonsnarski@gmail.com)
 * @brief Header file for matrix declaration.
 * @version 0.1
 * @date 19-12-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __MATRIX_DECL_HPP__
#define __MATRIX_DECL_HPP__

#include<cstddef>
#include<cstdlib>

#include<iomanip>
#include<sstream>
#include<utility>
#include<iostream>
#include<iterator>
#include<algorithm>
#include<stdexcept>
#include<functional>

#ifndef MATRIX_PRINT_PRECISION
#define MATRIX_PRINT_PRECISION 2
#elif MATRIX_PRINT_PRECISION < 0
#error MATRIX_PRINT_PRECISION must be positive
#endif

#ifndef MATRIX_OPTIMISE
#define __matrix_assert(expr, except, msg) \
        if constexpr(!(expr)) \
        { \
            std::ostringstream oss; \
            oss << __PRETTY_FUNCTION__ << ':' << msg; \
            throw except(oss.str()); \
        }

#define __matrix_assert_index() \
        __matrix_assert(idx < M * N, std::out_of_range, \
            "Index (" << idx << ") out of range for " \
            "dimension (" << M << ", " << N << ')')

#define __matrix_assert_bounds() \
        __matrix_assert(i < M && j < N, std::out_of_range, \
            "Index (" << i << ", " << j << ") out of range for " \
            "dimension (" << M << ", " << N << ')')
#define __matrix_assert_square() \
        __matrix_assert(M == N, std::logic_error, \
            "Matrix of dimension (" << M << ", " << N << ") " \
            "not square")
#elif
#define __matrix_assert_index()
#define __matrix_assert_bounds()
#define __matrix_assert_square()
#endif

namespace linalg
{
template<std::size_t M, std::size_t N, typename T = double> struct Matrix;

template<std::size_t N, typename T = double>
using Array = Matrix<1, N, T>;

template<std::size_t M, typename T = double>
using Vector = Matrix<M, 1, T>;

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> operator+(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> operator-(Matrix<M, N, T> lhs, const Matrix<M, N, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> operator*(Matrix<M, N, T> lhs, T rhs);

template<std::size_t M, std::size_t N, typename T>
Matrix<M, N, T> operator*(T lhs, Matrix<M, N, T> rhs);

template<std::size_t M, std::size_t N, std::size_t K, typename T>
Matrix<M, K, T> operator*(Matrix<M, N, T> lhs, const Matrix<N, K, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
bool operator==(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
bool operator!=(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs);

template<std::size_t M, std::size_t N, typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& obj);

/**
 * @brief A Matrix class representing a 2 dimensional object.
 *
 * @tparam T Data type
 * @tparam M Number of rows
 * @tparam N Number of columns
 */
template<std::size_t M, std::size_t N, typename T>
struct Matrix
{
    T Data[M * N]; /**< Matrix data */

    /**
     * @brief Creates an identity matrix.
     * 
     * Must be a square matrix.
     * 
     * @return Identity matrix
     */
    static inline Matrix<N, N, T> eye();

    /**
     * @brief Returns the index for the position i, j.
     * 
     * @param i Row
     * @param j Column
     * @return Matrix data index
     */
    static inline std::size_t idx(std::size_t i, std::size_t j);

    /**
     * @brief Returns the array at row i.
     * 
     * @param i Row
     * @return Array
     */
    Array<N, T> GetRow(std::size_t i) const;

    /**
     * @brief Returns the vector at column j.
     * 
     * @param j Column
     * @return Vector
     */
    Vector<M, T> GetCol(std::size_t j) const;

    /**
     * @brief Copies the array into row i.
     * 
     * @param i Row
     * @param row Array
     */
    void SetRow(std::size_t i, const Array<N, T>& row);

    /**
     * @brief Copies the vector into column j.
     * 
     * @param j Column
     * @param col Vector
     */
    void SetCol(std::size_t j, const Vector<M, T>& col);

    /**
     * @brief Returns the largest value in the matrix.
     * 
     * @return Max
     */
    T Max() const;

    /**
     * @brief Returns the absolute largest value in the matrix.
     * 
     * @return Absolute max
     */
    T AbsMax() const;

    /**
     * @brief Returns the determinant of the matrix.
     * 
     * Uses LU decomposition. Must be a square matrix.
     * 
     * @return Determinant
     */
    T Determinant() const;

    /**
     * @brief Returns an array of the products of each column.
     * 
     * @return Array of product
     */
    Array<N, T> Product() const;
    
    /**
     * @brief Returns the transpose of the matrix.
     * 
     * @return Transpose of matrix
     */
    Matrix<N, M, T> Transpose() const;

    /**
     * @brief Applies LU decomposition and returns the lower and upper matrices.
     * 
     * @return Pair of lower and upper matrix
     */
    std::pair<Matrix<N, N, T>, Matrix<N, N, T>> LU_Decomposition() const;

    /**
     * @brief Accesses the matrix data at index.
     * 
     * @param idx Index
     * @return Matrix data
     */
    T& operator[](std::size_t idx);

    /**
     * @brief Accesses the matrix at position i, j.
     * 
     * @param i Row
     * @param j Column
     * @return Matrix data
     */
    T& operator()(std::size_t i, std::size_t j);

    /**
     * @brief Returns the matrix data at index.
     * 
     * @param idx Index
     * @return Matrix data
     */
    T operator[](std::size_t idx) const;

    /**
     * @brief Returns the matrix data at position i, j.
     * 
     * @param i Row
     * @param j Column
     * @return Matrix data
     */
    T operator()(std::size_t i, std::size_t j) const;

    /**
     * @brief The plus-assignment operator.
     * 
     * @param rhs Right-hand-side matrix
     * @return This
     */
    Matrix<M, N, T>& operator+=(const Matrix<M, N, T>& rhs);

    /**
     * @brief The minus-assignment operator.
     * 
     * @param rhs Right-hand-side matrix
     * @return This
     */
    Matrix<M, N, T>& operator-=(const Matrix<M, N, T>& rhs);

    /**
     * @brief The multiply-assignment operator.
     * 
     * @param rhs Right-hand-side matrix
     * @return This
     */
    Matrix<M, N, T>& operator*=(const Matrix<N, N, T>& rhs);

    /**
     * @brief The multiply-assignment operator.
     * 
     * @param rhs Right-hand-side scalar
     * @return This
     */
    Matrix<M, N, T>& operator*=(T rhs);

    /**
     * @brief The plus operator.
     * 
     * @param lhs Left-hand-side matrix
     * @param rhs Right-hand-side matrix
     * @return Sum of matrices
     */
    friend Matrix operator+<>(Matrix lhs, const Matrix& rhs);

    /**
     * @brief The minus operator.
     * 
     * @param lhs Left-hand-side matrix
     * @param rhs Right-hand-side matrix
     * @return Difference of matrices
     */
    friend Matrix operator-<>(Matrix lhs, const Matrix& rhs);

    /**
     * @brief The multiply operator
     * 
     * @param lhs Left-hand-side matrix
     * @param rhs Right-hand-side scalar
     * @return Scaled matrix
     */
    friend Matrix operator*<>(Matrix lhs, T rhs);

    /**
     * @brief The multiply operator.
     * 
     * @param lhs Left-hand-side scalar
     * @param rhs Right-hand-side matrix
     * @return Scaled matrix
     */
    friend Matrix operator*<>(T lhs, Matrix rhs);

    /**
     * @brief The equality operator.
     * 
     * @param lhs Left-hand-side matrix
     * @param rhs Right-hand-side matrix
     * @return True if equal, false otherwise
     */
    friend bool operator==<>(const Matrix& lhs, const Matrix& rhs);

    /**
     * @brief The inequality operator.
     * 
     * @param lhs Left-hand-side matrix
     * @param rhs Right-hand-side matrix
     * @return True if not equal, false otherwise
     */
    friend bool operator!=<>(const Matrix& lhs, const Matrix& rhs);

    /**
     * @brief The stream insertion overload.
     * 
     * Outputs the matrix data to the stream with pretty formatting.
     * 
     * @param os Output stream
     * @param obj Matrix
     * @return Output stream
     */
    friend std::ostream& operator<<<>(std::ostream& os, const Matrix& obj);

    /**
     * @brief The iterator class (see C++ iterator convention).
     */
    class Iterator
    {
    public:
        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        Iterator(T* ptr);
        
        T* operator->();
        T& operator*() const;
        Iterator operator++(T);
        Iterator& operator++();
        friend bool operator==<>(const Iterator& lhs, const Iterator& rhs);
        friend bool operator!=<>(const Iterator& lhs, const Iterator& rhs);

    private:
        T* m_Ptr;
    };

    /**
     * @brief The iterator pointing to the last index + 1 of the matrix data.
     * 
     * @return Iterator
     */
    Iterator end();

    /**
     * @brief The iterator pointing to the first index of the matrix data.
     * 
     * @return Iterator
     */
    Iterator begin();

    /**
     * @brief The iterator pointing to the last index + 1 of the matrix data.
     * 
     * @return Iterator
     */
    const Iterator cend() const;

    /**
     * @brief The iterator pointing to the first index of the matrix data.
     * 
     * @return Iterator
     */
    const Iterator cbegin() const;
};
template<std::size_t M, std::size_t N, typename T>
bool operator==(const typename Matrix<M, N, T>::Iterator& lhs,
                const typename Matrix<M, N, T>::Iterator& rhs);

template<std::size_t M, std::size_t N, typename T>
bool operator!=(const typename Matrix<M, N, T>::Iterator& lhs,
                const typename Matrix<M, N, T>::Iterator& rhs);
}

#endif/*__MATGRIX_DECL_HPP__*/
