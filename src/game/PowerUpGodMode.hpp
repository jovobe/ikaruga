/**
 * PowerUpGodMode.hpp
 *
 *  @date   02.03.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#ifndef IKARUGA_POWERUPGODMODE_HPP
#define IKARUGA_POWERUPGODMODE_HPP

#include "PowerUp.hpp"

namespace ikaruga
{
    class PowerUpGodMode final : public PowerUp
    {
    public:
        /**
         * @see PowerUp::PowerUp(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
         */
        PowerUpGodMode(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

        /**
         * @see PowerUp::consume(Player& player)
         */
        virtual void consume(Player& player);

        /**
         * @see PowerUp::stop(Player& player)
         */
        virtual void stop(Player& player);
    };

} /* namespace ikaruga */


#endif //IKARUGA_POWERUPGODMODE_HPP
