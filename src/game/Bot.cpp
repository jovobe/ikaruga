/*
 * Bot.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#include "Bot.hpp"
#include "Projectile.hpp"

using std::cout;
using std::endl;

namespace ikaruga
{
    Bot::Bot(SDL_Renderer* renderer,
             SDL_Texture* texture,
             int frameWidth,
             int frameHeight,
             int numFrames,
             Game* game,
             XML::NPC npc,
             int health,
             int collisionDamage,
             ActorType type)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames, health, collisionDamage)
    {
        m_type = type;
        m_physicalProps.setMoveForce(Vector2f(0, 0));
        m_physicalProps.setMaxRunVelocity(50);

        m_game = game;

        m_npc = npc;
        if (npc.move_function == "SIN")
        {
            m_move_type = BotType::SIN;
        }
        else if (npc.move_function == "SIN_UP")
        {
            m_move_type = BotType::SIN_UP;
        }
        else if (npc.move_function == "SIN_DOWN")
        {
            m_move_type = BotType::SIN_DOWN;
        }
        else if (npc.move_function == "AI")
        {
            m_move_type = BotType::AI;
        }
        else if (npc.move_function == "CIRCLE")
        {
            m_move_type = BotType::CIRCLE;
        }
        else
        {
            m_move_type = BotType::NO_MOVE;
        }
    }

    void Bot::move(Level& level)
    {
        nextFrame();
        float dt = getElapsedTime();
        Vector2f d_move;
        shoot();
        switch (m_move_type)
        {
            case BotType::NO_MOVE:
                break;
            case BotType::AI:
            {
                float ds = (m_game->getPlayerPosition().y() - physics().position().y()) * AI_TRACE_SPEED;
                d_move.setY(ds);
                d_move.setX(m_npc.speed);
                physics().setPosition(physics().position() + d_move * dt);
                break;
            }
            case BotType::SIN:
            case BotType::SIN_UP:
            case BotType::SIN_DOWN:
            case BotType::CIRCLE:
            {
                if (dt > 0)
                {
                    d_move.setX(m_npc.speed);

                    switch (m_move_type)
                    {
                        case BotType::SIN:
                            d_move.setY(-cos(getLiveTime()) * m_npc.move_value * 2.6);
                            break;
                        case BotType::CIRCLE:
                            d_move.setY(-cos(getLiveTime()) * m_npc.move_value * 2.6);
                            d_move.setX(-cos(M_PI / 2 + getLiveTime()) * m_npc.move_value * 2.6);
                            break;
                        case BotType::SIN_UP:

                            d_move.setY(-cos(M_PI / 2 + getLiveTime()) * m_npc.move_value * 2.6);
                            break;
                        case BotType::SIN_DOWN:
                            d_move.setY(-cos(-M_PI / 2 + getLiveTime()) * m_npc.move_value * 2.6);
                            break;
                    }

                    physics().setPosition(physics().position() + d_move * dt);
                }
                break;
            }
        }

        // remove bots when out of focus
        if (position().x() + Game::PIXELS_OFFSET_SPAWN_BOTS < m_camera.x())
        {
            setHealth(0);
            setKilled(false);
        }
        if (type() == ActorType::BOSS)
        {
            m_game->setBossHealth(m_health);
        }
    }

    void Bot::onActorCollision(Actor& other)
    {
        // Hit by player's projectile with same color
        if (other.type() == PROJECTILE && getColor() == other.getColor())
        {
            Projectile* projectile = static_cast<Projectile*>(&other);
            if (projectile->getOriginActor()->type() == ActorType::PLAYER)
            {
                setHit(true);
                takeDamage(other.getCollisionDamage());
                setKilled(true);
            }
        }
        // Hit by player
        if (other.type() == PLAYER)
        {
            setHit(true);
            takeDamage(other.getCollisionDamage());
            setKilled(true);
        }
    }

    void Bot::onTileCollision()
    {
        return;
    }

    Bot::~Bot()
    {
        //TODO ~ Do something fancy here
    }

    void Bot::shoot()
    {
        // skip if no weapon is set
        if (m_weapon == 0)
        {
            return;
        }

        // calc direction
        Vector2f playerPos = m_game->getPlayerPosition();
        Vector2f direction = playerPos - position();
        direction.setY(0);
        direction.normalize();

        m_weapon->shoot(direction, position());
    }
} /* namespace ikaruga */
