/**
 * PowerUpHeal.hpp
 *
 *  @date   01.03.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#ifndef IKARUGA_POWERUPHEAL_HPP
#define IKARUGA_POWERUPHEAL_HPP

#include "PowerUp.hpp"

namespace ikaruga
{
    class PowerUpHeal : public PowerUp
    {

    public:
        /**
         * @see PowerUp::PowerUp(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
         */
        PowerUpHeal(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames,
                    int healPercentage);

        /**
         * @see PowerUp::consume(Player& player)
         */
        virtual void consume(Player& player) override;

        /**
         * @see PowerUp::stop(Player& player)
         */
        virtual void stop(Player& player) override;

    private:
        /// heal Percentage
        int m_healPercentage;
    };
} /* namespace ikaruga */


#endif //IKARUGA_POWERUPHEAL_HPP
