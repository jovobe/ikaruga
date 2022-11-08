/*
 * Collidable.hpp
 *
 *  @date   03.03.2015
 *  @author Benjamin Lücking <bluecking@uos.de>
 *  @author David Rolfes     <darolfes@uos.de>
 *  @author Nathan Wollek    <nwollek@uos.de>
 *
 */

#ifndef SRC_GAME_COLLIDABLE_HPP_
#define SRC_GAME_COLLIDABLE_HPP_

#include "Level.hpp"

namespace ikaruga
{
    /**
     * Interface for objects which support collisions (tile and actor)
     */
    class Collidable
    {
    public:
        /**
         * Constructor for Collidable inits the vars
         */
        Collidable();

        /**
         * Destructor of Collidable
         */
        virtual ~Collidable();

        /**
         * Is invoked if the actor (Collidable) collides with an tile
         */
        virtual void onTileCollision() = 0;

        /**
         * Is invoked if the actor collides with another actor
         * It is pure virtual, since the subclasses react differently on
         * collisions with different actors.
         *
         * @parameter other The actor instance which collided with this instance
         */
        virtual void onActorCollision(Actor& other) = 0;

        /**
         * Is used to get the Hitbox of the Collidable (pure virtual)
         *
         * @return SDL_Rect& - Hitbox of the Collidable (Actor collision only)
         */
        virtual SDL_Rect& getHitbox() = 0;

        /**
         * Getter of m_collisionDamage (collision damage of Collidable)
         *
         * @return int - value of m_collisionDamage
         */
        int getCollisionDamage() const
        {
            return m_collisionDamage;
        }

    protected:
        SDL_Rect m_hitbox;

        /** The hitbox size is resized to this factor */
        float m_hitboxfactor;

        int m_collisionDamage;

        bool m_hit;

        /** The opacity level that is rendered, when a collidable was hit */
        const unsigned char m_opacityLevelWhenHit;
    };

} /* namespace ikaruga */

#endif /* SRC_GAME_COLLIDABLE_HPP_ */
