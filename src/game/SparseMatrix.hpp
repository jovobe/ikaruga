/**
 * SparseMatrix.hpp
 *
 * @date 03.03.16
 * @author Dennis Altenhoff (daltenhoff@uni-osnabrueck.de)
 */

#ifndef __SPARSE_VECTOR_HPP__
#define __SPARSE_VECTOR_HPP__

#include "SparseVector.hpp"

namespace ikaruga
{

    /**
     * @brief Representation of a sparse matrix
     */
    class SparseMatrix
    {
        /// Array of sparse vectors to represent the columns
        SparseVector** m_rows;

        /// Number of colums of the matrix
        int m_numRows;

        /// Number of rows of the matrix
        int m_numColumns;

        /// Helper to copy a sparse matrix
        void copy(const SparseMatrix& other);

        /// Helper to delete all contends of a sparse matrix
        void clear();

    public:

        /**
         * Default constructor. Initializes all values with zero.
         */
        SparseMatrix();

        /**
         * Copy constructor.
         *
         * @param other   matrix to copy from
         */
        SparseMatrix(const SparseMatrix& other);

        /**
         * Constructs a matrix with \ref rows rows and \ref columns columns. And initializes all values with zero.
         *
         * @param rows    number of rows
         * @param cols    number of columns
         */
        SparseMatrix(const int& rows, const int& cols);

        /**
         * Destructor
         */
        ~SparseMatrix();

        /**
         * Assignment operator
         *
         * @param other   reference of vector to assign from
         */
        SparseMatrix& operator=(const SparseMatrix& other);

        /**
         * Inserts an integer \ref value at given \ref row and \ref column
         *
         * @param row     row to insert value into
         * @param col     col to insert value into
         * @param value   value to insert
         */
        void insert(const int& row, const int& col, const int& value);

        /**
         * Returns the sparse vector at given \ref row
         *
         * @param row     number of row to return the vector from
         */
        SparseVector& operator[](int row) const;

    };

}  /* namespace ikaruga */

#endif
