#ifndef PLAYER_PROPERTIES_H
#define PLAYER_PROPERTIES_H

#include "Vector.hpp"

namespace ikaruga
{
    /**
     * @brief		A class to represent the physical properties of
     * 				a player.
     */
    class PlayerProperty
    {
    public:

        /**
         * Constructor.
         */
        PlayerProperty();

        /**
         * Constructor
         *
         * @param position		Initial position
         * @param moveForce		Initial move force
         * @param velocity		Initial velocity
         * @param maxVel		Maximum velocity
         * @param maxJumpVel	Maximum jump velocity
         * @param maxJumpHeight Maximum jump height
         * @param maxRunVel		Maximum run velocity
         * @param maxFallVel	Maximum fall velocity
         */
        PlayerProperty(
                const Vector2f& position,
                const Vector2f& moveForce,
                const Vector2f& velocity,
                double maxVel
        );

        /**
         * Returns the move force to push the player
         */
        const Vector2f& moveForce() const;

        /**
         * Sets the move force to push the player
         */
        void setMoveForce(const Vector2f& move);

        /**
         * Returns the maximum running velocity
         */
        double maxRunVelocity() const;

        /**
         * Sets the maximum running velocity
         */
        void setMaxRunVelocity(double maxVelRun);

        /**
         * Sets the player position
         */
        void setPosition(const Vector2f& m_pos);

        /**
         * Sets the player's velocity
         */
        void setVelocity(const Vector2f& m_vel);

        /**
         * Returns the player's velocity
         */
        Vector2f& velocity();

        /**
         * Returns the player's position
         */
        Vector2f& position();

    private:

        /// Position
        Vector2f m_pos;

        /// Velocity
        Vector2f m_vel;

        /// Force that pushes the player
        Vector2f m_moveForce;

        /// Maximum run velocity
        double m_maxVelRun;
    };
} /* namespace ikaruga */

#endif //IKARUGA_PHYSICPLAYER_H
