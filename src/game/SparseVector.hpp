/**
 * SparseVector.hpp
 *
 * @date 03.03.16
 * @author Dennis Altenhoff (daltenhoff@uni-osnabrueck.de)
 */

#ifndef __SPARSEVECTOR_HPP__
#define __SPARSEVECTOR_HPP__

#include <cassert>

namespace ikaruga
{

    /**
     * @brief A sparse vector representation for integer values. Non-Zero Entries are saved in a linked list,
     */
    class SparseVector
    {

        /// Inner struct to represent a node in the sparse vector
        struct node
        {
            /// Element number, must be smaller than the vector's size
            int index;

            /// The value of this element
            int value; // The value of this element.

            /// A pointer to the next node in the list
            node* next; // A pointer to the next node in the linked-list.

            /**
             * Constructor
             *
             * @param idx	Index of the node
             * @param val	Value of the node
             * @param nxt	Pointer to next node in list
             */
            node(int idx, int val, node* nxt) : index(idx), value(val), next(nxt)
            { }

            /**
             * Copy constructor
             */
            node(const node& c) : index(c.index), value(c.value), next(c.next)
            { }
        };

    public:

        /**
         * Constructs a sparse vector with given size.
         * @param size   Size of the vector
         */
        SparseVector(int size);

        /**
         * Copy constructor.
         *
         * @param other    SparseVector to copy from
         */
        SparseVector(const SparseVector& other);

        /*
         * Destructor.
         */
        ~SparseVector();

        /**
         * Assigns the given value the the ith component.
         *
         * @param index  index of component to assign value to
         * @param value  value to assign to component
         */
        void setElem(int index, int value);

        /**
         * Returns the value of component index
         *
         * @param index index of component to get value from
         */
        int getElem(int index) const;

        /**
         * Returns the size of the vector
         */
        int getSize() const;

        /**
         * Assignment operator
         *
         * @param other   reference of vector to assign from
         */
        SparseVector& operator=(const SparseVector& other);

        /**
         * Checks if two vectors are equal
         *
         * @param other   reference of vector to check for equality
         */
        bool operator==(const SparseVector& other) const;

        /**
         * Checks for inequality
         *
         * @param other   reference of vector to check for inequality
         */
        bool operator!=(const SparseVector& other) const;

        /**
         * Returns the value of the ith component
         *
         * @param ndexi   index of component to get value from
         */
        int operator[](int index) const
        { return getElem(index); }

    private:

        /// List anchor
        node* m_start;

        /// Size of the vector
        int m_size;

        /**
         * Removes all non-zero elements
         */
        void clear();

        /**
         * Copies the contends of the other vector
         *
         * @param other   Vector to copy contends from.
         */
        void copy(const SparseVector& other);

        /**
         * Sets a value of an non-zero element, i.e., inserts a new
         * node in the list
         *
         * @param index   index to insert to
         * @param value   value to insert
         */
        void setNonzeroElem(int index, int value);

        /**
         * Removes the element at given
         *
         * @param index  index to remove at
         */
        void removeElem(int index);

        /**
         * Returns a pointer to node in the list before \ref index
         *
         * @param index   index to get previous element from
         */
        node* getPrevElem(int index) const;

    };

}  /* namespace ikaruga */

#endif
