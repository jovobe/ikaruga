/**
 * PowerUp.hpp
 *
 *  @date   01.03.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#ifndef IKARUGA_POWERUP_HPP
#define IKARUGA_POWERUP_HPP

#include "Actor.hpp"
#include "Player.hpp"

namespace ikaruga
{

    class Player;

    class PowerUp : public Actor
    {
    public:
        /**
         * @brief	            Constructs a PowerUp from given renderer, texture
         * 			            and frame information.
         * @param renderer      the given renderer
         * @param texture       the given texture
         * @param frameWidth    the width of a frame
         * @param frameHeight   the height of a frame
         * @param numFrames     the count of frames
         */
        PowerUp(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

        /**
         * @brief the destructor
         */
        ~PowerUp();

        /**
         * @see Actor::move(Level& level)
         */
        virtual void move(Level& level) override final;

        /**
         * @see Collidable::onTileCollision()
         */
        virtual void onTileCollision() override final;

        /**
         * @see Collidable::onActorCollision(Actor& other)
         */
        virtual void onActorCollision(Actor& other) override final;

        /**
         * @brief This method will be invoked by the player on every game update, as long as he has not dropped the powerup.
         *
         * @param player The player passes itself, so the powerup can manipulate the player
         */
        virtual void consume(Player& player) = 0;

        /**
         * @brief This method will be invoked by the player as soon as the player drops the powerup.
         *
         * @param player The player passes itself, so the powerup can manipulate the player
         */
        virtual void stop(Player& player) = 0;

        /**
         * @brief getter for expiration time
         * @return expiration time
         */
        int getExpirationTime() const
        {
            return m_expirationTime;
        }

        /**
         * @brief setter for expiration time
         * @param expirationTime expiration time
         */
        void setExpirationTime(int expirationTime)
        {
            m_expirationTime = expirationTime;
        }

    private:
        /// expiration Time
        int m_expirationTime;
    };
} /* namespace ikaruga */

#endif //IKARUGA_POWERUP_HPP
