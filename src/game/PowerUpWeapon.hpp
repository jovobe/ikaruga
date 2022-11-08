/**
 * PowerUpWeapon.hpp
 * 
 * @date 02.03.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef IKARUGA_POWERUPWEAPON_HPP
#define IKARUGA_POWERUPWEAPON_HPP

#include "PowerUp.hpp"

namespace ikaruga
{
    class PowerUpWeapon : public PowerUp
    {
    public:
        PowerUpWeapon(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames,
                      Weapon* weapon);

        /**
         * see PowerUp::consume(Player& player)
         */
        virtual void consume(Player& player);

        /**
         * see PowerUp::stop(Player& player)
         */
        virtual void stop(Player& player);

    private:
        Weapon* m_weapon;
    };
} /* namespace ikaruga */

#endif //IKARUGA_POWERUPWEAPON_HPP
