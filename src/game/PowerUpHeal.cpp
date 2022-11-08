/**
 * PowerUpHeal.cpp
 *
 *  @date   01.03.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#include "PowerUpHeal.hpp"

namespace ikaruga
{
    PowerUpHeal::PowerUpHeal(
            SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames,
            int healPercentage)
            : PowerUp(renderer, texture, frameWidth, frameHeight, numFrames), m_healPercentage(healPercentage)
    { }

    void PowerUpHeal::consume(Player& player)
    {
        float heal = player.getInitial_health() * m_healPercentage * 0.01f;
        player.setHealth(player.getHealth() + ((int) (heal * m_healPercentage)));
    }

    void PowerUpHeal::stop(Player& player)
    {
        // do nothing yet
    }
} /* namespace ikaruga */
