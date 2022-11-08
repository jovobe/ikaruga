/**
 * Armed.cpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include "Armed.hpp"

namespace ikaruga
{
    Armed::Armed()
            : m_weapon(0)
    { }

    Armed::~Armed()
    {
        delete m_weapon;
    }
} /* namespace ikaruga */
