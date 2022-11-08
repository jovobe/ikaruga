/*
 * Actor.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#include <SDL.h>
#include <iostream>
#include "Actor.hpp"
#include "Game.hpp"

using std::cout;
using std::endl;

namespace ikaruga
{
    Actor::Actor(SDL_Renderer* renderer,
                 SDL_Texture* texture,
                 int frameWidth,
                 int frameHeight,
                 int numFrames,
                 int health,
                 int collisionDamage)
            : AnimatedRenderable(renderer, texture, frameWidth, frameHeight, numFrames),
              m_color(ColorMode::BLACK),
              m_explosionVolume(0),
              m_focus(false),
              m_health(health),
              m_isKilled(false),
              m_scoreValue(0),
              m_startTicks(0),
              m_type(PLAYER)
    {
        m_physicalProps.setPosition(Vector2f(100, 0));
        m_collisionDamage = collisionDamage;
        setLiveTime();
    }

    void Actor::setPhysics(PlayerProperty p)
    {
        m_physicalProps = p;
    }

    Actor::~Actor()
    {

    }

    float Actor::getElapsedTime()
    {
        if (m_startTicks == 0)
        {
            m_startTicks = SDL_GetTicks();
        }

        Uint32 ticks = SDL_GetTicks();
        float time = (ticks - m_startTicks) / 1000.0;
        m_startTicks = ticks;
        return time;
    }

    void Actor::setLiveTime()
    {

        m_spawnTime = SDL_GetTicks();
    }

    float Actor::getLiveTime()
    {
        Uint32 ticks = SDL_GetTicks();
        float time = (ticks - m_spawnTime) / 1000.0;
        return time;
    }

    void Actor::render()
    {
        SDL_Rect target;

        target.x = (int) floor(m_physicalProps.position().x() - m_camera.x());
        target.y = (int) floor(m_physicalProps.position().y() - m_camera.y());
        target.w = m_frameWidth;
        target.h = m_frameHeight;

        // Do not render if actor is outside frustrum
        if (target.x + target.w > 0 && target.x < m_camera.w() + Game::PIXELS_OFFSET_RENDER)
        {
            // Render current animation frame
            SDL_Rect source = m_sourceRect;

            // switch color
            if (getColor() == ColorMode::WHITE)
            {
                source.x = source.x + (int) m_colorOffset.x();
                source.y = source.y + (int) m_colorOffset.y();
            }

            // Make the texture opaque when actor collides
            if (isHit())
            {
                SDL_SetTextureAlphaMod(m_texture, m_opacityLevelWhenHit);
                SDL_RenderCopyEx(getRenderer(), m_texture, &source, &target, 0, NULL, SDL_FLIP_NONE);
                SDL_SetTextureAlphaMod(m_texture, 255);
            }
            else
            {
                SDL_RenderCopyEx(getRenderer(), m_texture, &source, &target, 0, NULL, getFlip());
            }

//            renderHitbox();
        }

    }

    SDL_RendererFlip Actor::getFlip()
    {
        // No flip necessary if not projectile
        return SDL_FLIP_NONE;
    }

    SDL_Rect& Actor::getHitbox()
    {
        m_hitbox.w = (int) std::floor(m_frameWidth * m_hitboxfactor);
        m_hitbox.h = (int) std::floor(m_frameHeight * m_hitboxfactor);
        m_hitbox.x = (int) (std::floor((m_frameWidth - m_hitbox.w) / 2) + position().x());
        m_hitbox.y = (int) (std::floor((m_frameHeight - m_hitbox.h) / 2) + position().y());

        return m_hitbox;
    }

    void Actor::setPosition(Vector2f pos)
    {
        m_physicalProps.position() = pos;
    }

    PlayerProperty& Actor::physics()
    {
        return m_physicalProps;
    }

    Vector2f Actor::position()
    {
        return m_physicalProps.position();
    }

    void Actor::setFocus(bool focus)
    {
        m_focus = focus;
    }

    void Actor::toggleColor()
    {
        m_color = m_color == ColorMode::BLACK ? ColorMode::WHITE : ColorMode::BLACK;

    }

    bool Actor::visible()
    {
        SDL_Rect myRect;
        myRect.x = (int) position().x();
        myRect.y = (int) position().y();
        myRect.w = w();
        myRect.h = h();

        SDL_Rect otherRect;
        otherRect.x = (int) m_camera.x();
        otherRect.y = (int) m_camera.y();
        otherRect.w = m_camera.w();
        otherRect.h = m_camera.h();

        SDL_Rect intersection;
        SDL_IntersectRect(&myRect, &otherRect, &intersection);

        return intersection.w > 0 && intersection.h > 0;
    }

    int Actor::getHealth() const
    {
        return m_health;
    }

    void Actor::takeDamage(int damage)
    {
        m_health -= damage;
    }

    void Actor::renderHitbox()
    {
        SDL_Rect& hitbox = getHitbox();
        hitbox.x -= m_camera.x();
        hitbox.y -= m_camera.y();

        // Color hitbox depending on the current color state
        if (m_color == ColorMode::BLACK)
        {
            SDL_SetRenderDrawColor(getRenderer(), 255, 0, 0, 0);
        }
        else
        {
            SDL_SetRenderDrawColor(getRenderer(), 0, 255, 0, 0);
        }

        SDL_RenderDrawRect(getRenderer(), &hitbox);
    }

    void Actor::playExplosionSound()
    {
        m_explosionSound.play(m_explosionVolume);
    }
} /* namespace ikaruga */

