/*
 * Collidable.cpp
 *
 *  @date   03.03.2015
 *  @author Benjamin Lücking <bluecking@uos.de>
 *  @author David Rolfes	 <darolfes@uos.de>
 *  @author Nathan Wollek	 <nwollek@uos.de>
 *
 */

#include "Collidable.hpp"

namespace ikaruga
{

    Collidable::Collidable()
            : m_hitboxfactor(1.0), m_hit(false), m_opacityLevelWhenHit(0)
    {
        // TODO Auto-generated constructor stub

    }


    Collidable::~Collidable()
    {
        // TODO Auto-generated destructor stub
    }

} /* namespace ikaruga */
