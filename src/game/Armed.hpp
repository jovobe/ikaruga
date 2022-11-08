/**
 * Armed.hpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef IKARUGA_ARMED_HPP
#define IKARUGA_ARMED_HPP

#include "Weapon.hpp"

namespace ikaruga
{
    /**
     * @brief Represents an armed object which has a weapon. With the weapon it's able to shoot projectiles to
     * a configured direction.
     */
    class Armed
    {
    public:

        /**
         * Constructor
         */
        Armed();

        /**
         * Destructor
         */
        virtual ~Armed();

        /**
         * Shoots projectiles
         */
        virtual void shoot() = 0;

        /**
         * Sets a weapon
         *
         * @param weapon Weapon to set
         */
        void setWeapon(Weapon* weapon)
        { m_weapon = weapon; }

        /**
         * Returns the weapon
         *
         * @return Current weapon
         */
        Weapon* getWeapon(void)
        { return m_weapon; }

    protected:
        // The weapon
        Weapon* m_weapon;
    };
} /* namespace ikaruga */

#endif //IKARUGA_ARMED_HPP
