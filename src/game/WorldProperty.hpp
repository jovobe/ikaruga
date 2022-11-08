//
// Created by isaak on 26.11.15.
//

#ifndef IKARUGA_WorldProperties_H
#define IKARUGA_WorldProperties_H

#include "Vector.hpp"

namespace ikaruga
{

    /**
     * @brief	A class that holds properties about the physical characteristics
     * 			of a level.
     */
    class WorldProperty
    {
    public:

        WorldProperty();

        /**
         * Constructor.
         *
         * @param damping		Damping force on tiles
         */
        WorldProperty(const Vector2f& damping);

        /**
         * Returns the damping force
         */
        const Vector2f& damping() const;

        /**
         * Sets the damping force
         */
        void setDamping(const Vector2f& damping);

        /**
         * Getter for the scrolling speed
         * @param scrollingSpeed Takes an Vector2f for setting the scrolling speed
         */
        const Vector2f& getScrollingSpeed() const
        {
            return m_scrollingSpeed;
        }

        /**
         * Setter for the scrolling speed
         * @param scrollingSpeed Takes an Vector2f for setting the scrolling speed
         */
        void setScrollingSpeed(const Vector2f& scrollingSpeed)
        {
            m_scrollingSpeed = scrollingSpeed;
        }

    private:

        /// Damping force. Currently for the whole level
        Vector2f m_damping;

        /** Sets the scrolling speed of camera and player. */
        Vector2f m_scrollingSpeed;
    };

} /* namespace ikaruga */

#endif //IKARUGA_WorldProperties_H
