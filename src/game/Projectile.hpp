/**
 * Projectile.hpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef IKARUGA_PROJECTILE_HPP
#define IKARUGA_PROJECTILE_HPP

#include "Level.hpp"
#include "Game.hpp"

namespace ikaruga
{
    class Projectile : public Actor
    {
    public:
        /**
         * Constructor
         *
         * @param renderer Renderer in which this projectile will be rendered
         * @param texture Texture for this projectile
         * @param frameWidth Width of the projectile texture
         * @param frameHeight Height of the projectile texture
         * @pararm numFrames Number of animation frames
         * @param collisionDamage Amount of damage this projectile deals
         * @param speed Speed with which this projectile travels
         */
        Projectile(SDL_Renderer* renderer,
                   SDL_Texture* texture,
                   int frameWidth,
                   int frameHeight,
                   int numFrames,
                   int collisionDamage,
                   float speed);

        /**
         * Returns origin actor of this projectile
         *
         * @return Actor which launched this projectile
         */
        Actor* getOriginActor() const
        { return m_originActor; }

        /**
         * Sets origin actor
         *
         * @param m_originActor Actor to set
         */
        void setOriginActor(Actor* m_originActor)
        { Projectile::m_originActor = m_originActor; }

        /**
         * Destruktor
         */
        virtual ~Projectile();

        /**
         * @see Actor::move(Level& level)
         */
        virtual void move(Level& level) override;

        /**
         * @see Collidable::onTileCollision()
         */
        virtual void onTileCollision() override;

        /**
         * Returns direction of this projectile
         *
         * @return Direction in which this projectile moves
         */
        const Vector2f& getDirection() const
        { return m_direction; }

        /**
         * Sets direction in which this projetile moves
         *
         * @pararm m_direction Direction in which projectile should move
         */
        void setDirection(const Vector2f& m_direction)
        { Projectile::m_direction = m_direction; }

        /**
         * Launches this projectile
         */
        void launch()
        { m_launched = true; }

        /**
         * @see Actor::onActorCollision(Actor& other)
         */
        void onActorCollision(Actor& other) override;

        /**
         * Whether or not a texture flip is necessary
         *
         * @return SDL_FLIP flag
         */
        virtual SDL_RendererFlip getFlip() override;

        /**
         * @see Actor::getHitbox()
         */
        virtual SDL_Rect& getHitbox() override;

    protected:
        /// Direction in which this projectile moves
        Vector2f m_direction;

        /// True, if this projectile was launched, false else
        bool m_launched;

        /// Speed whith which this projectile moves
        float m_speed;
    private:
        /// Last position of this projectile
        Vector2f m_lastPosition = 0;

        /// Pointer to the actor who launched this projectile
        Actor* m_originActor;
    };
} /* namespace ikaruga */


#endif //IKARUGA_PROJECTILE_HPP
