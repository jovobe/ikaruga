/**
 * SparseVector.cpp
 *
 * @date 03.03.16
 * @author Jan Elseberg, Dennis Altenhoff
 */

#include "SparseVector.hpp"

#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

namespace ikaruga
{

    SparseVector::SparseVector(int size)
    {
        m_size = size;
        m_start = new node(-1, 0, 0);
    }


    SparseVector::SparseVector(const SparseVector& other)
    {
        copy(other);
    }

    SparseVector::~SparseVector()
    {
        clear();
    }

    void SparseVector::setElem(int index, int value)
    {
        // If index out of Bounds do nothing
        if (index >= getSize())
        {
            return;
        }

        if (value != 0)
        {
            setNonzeroElem(index, value);
            return;
        }
        removeElem(index);
    }

    int SparseVector::getElem(int index) const
    {
        // If index out of Bounds do nothing
        if (index >= getSize())
        {
            return 0.0;
        }

        node* elem = getPrevElem(index);

        if (elem != 0 && elem->next != 0 && elem->next->index == index)
        {
            return elem->next->value;
        }
        return 0.0;
    }

    int SparseVector::getSize() const
    {
        return m_size;
    }

    void SparseVector::clear()
    {
        node* elem;

        while (m_start != 0)
        {
            elem = m_start;
            m_start = m_start->next;
            delete elem;
        }
    }

    void SparseVector::copy(const SparseVector& other)
    {
        m_size = other.getSize();
        node* otherelem = other.m_start;
        m_start = new node(*otherelem);
        node* elem = m_start;

        while (otherelem->next != 0)
        {
            otherelem = otherelem->next;
            elem->next = new node(*otherelem);
            elem = elem->next;
        }
    }

/**
 * Sets an element to a non-zero value.
 *
 * @param index The index of the entry.
 * @param value The non zero-value to set.
 */
    void SparseVector::setNonzeroElem(int index, int value)
    {
        node* elem = getPrevElem(index);

        // No preceeding element found!
        if (elem == 0)
        {
            return;
        }

        // element with index already exists
        if (elem->next != 0 && elem->next->index == index)
        {
            elem->next->value = value;
            return;
        }

        // create new node
        elem->next = new node(index, value, elem->next);
    }


    void SparseVector::removeElem(int index)
    {
        // Only go to element to remove if possible
        node* elem = getPrevElem(index);
        if (elem == 0 || elem->next == 0)
        {
            return;
        }
        node* tmp = elem->next;
        elem->next = elem->next->next;
        delete tmp;
    }


    SparseVector::node* SparseVector::getPrevElem(int index) const
    {
        node* elem;
        elem = m_start;

        while (elem != 0 && elem->next != 0 && elem->next->index < index)
        {
            elem = elem->next;
        }
        return elem;
    }


    SparseVector& SparseVector::operator=(const SparseVector& other)
    {
        // Check for Self-Assignement
        if (this == &other)
        {
            return *this;
        }

        // destroy old values
        clear();

        copy(other);

        return *this;
    }


    bool SparseVector::operator==(const SparseVector& other) const
    {
        // If sizes of vectors are different do nothing
        if (getSize() != other.getSize())
        {
            return false;
        }

        node* elem = m_start;
        node* elemOther = other.m_start;

        while (true)
        {
            if (elem->index != elemOther->index || elem->value != elemOther->value)
            {
                return false;
            }

            // end of both SparseVectors
            if (elem->next == 0 && elemOther->next == 0)
            {
                return true;
            }
            // only reached the end of one SparseVector
            if (elem->next == 0 || elemOther->next == 0)
            {
                return false;
            }

            //iterate otherwise
            elem = elem->next;
            elemOther = elemOther->next;
        }
    }

    bool SparseVector::operator!=(const SparseVector& other) const
    {
        return !(*this == other);
    }

}  /* namespace ikaruga */


