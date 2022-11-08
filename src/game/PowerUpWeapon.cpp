/**
 * PowerUpWeapon.cpp
 * 
 * @date 02.03.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include "PowerUpWeapon.hpp"

namespace ikaruga
{
    PowerUpWeapon::PowerUpWeapon(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight,
                                 int numFrames, Weapon* weapon)
            : PowerUp(renderer, texture, frameWidth, frameHeight, numFrames), m_weapon(weapon)
    {

    }

    void PowerUpWeapon::consume(Player& player)
    {
        if (player.getWeapon()->getWeaponType() == m_weapon->getWeaponType())
        {
            // same weapon collected -> upgrade current weapon
            player.getWeapon()->upgrade();
            delete m_weapon;
        }
        else
        {
            // new weapon collected -> set new weapon
            m_weapon->setActor(&player);
            player.setWeapon(m_weapon);
        }
    }

    void PowerUpWeapon::stop(Player& player)
    {
        // do nothing yet
    }
} /* namespace ikaruga */
