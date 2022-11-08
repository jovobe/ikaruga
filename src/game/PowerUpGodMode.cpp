/**
 * PowerUpGodMode.cpp
 *
 *  @date   02.03.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#include "PowerUpGodMode.hpp"

namespace ikaruga
{
    PowerUpGodMode::PowerUpGodMode(
            SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
            : PowerUp(renderer, texture, frameWidth, frameHeight, numFrames)
    {

    }

    void PowerUpGodMode::consume(Player& player)
    {
        player.setGodMode(true);
    }

    void PowerUpGodMode::stop(Player& player)
    {
        player.setGodMode(false);
    }
} /* namespace ikaruga */
