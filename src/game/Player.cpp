//
// Created by isaak on 26.11.15.
//


#include "Player.hpp"
#include "Projectile.hpp"

using std::cout;
using std::endl;

namespace ikaruga
{
    Player::Player(
            SDL_Renderer* renderer,
            SDL_Texture* texture,
            Game& game,
            int frameWidth,
            int frameHeight,
            int numFrames,
            int health,
            int collisionDamage)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames, health, collisionDamage),
              m_game(game),
              m_moveDirection(0, 0),
              m_initial_health(health),
              m_godMode(false),
              m_godModeCheat(false),
              m_powerUps()
    {
        SDL_GetTextureColorMod(texture, &m_colorModR, &m_colorModG, &m_colorModB);
        m_hitboxfactor = 0.8;
    }

    void Player::move(Level& level)
    {
        nextFrame();
        float dt = getElapsedTime();
        if (dt > 0)
        {
            Vector2f d_move;

            d_move = (physics().moveForce() * m_moveDirection * dt);

            // Update velocity
            physics().setVelocity(physics().velocity() + d_move);

            // Damp velocity according to extrinsic level damping
            physics().setVelocity(physics().velocity() * level.physics().damping());

            // Clamp velocities
            if (physics().velocity().x() > physics().maxRunVelocity() * dt)
            {
                physics().setVelocity(Vector2f(physics().maxRunVelocity() * dt,
                                               physics().velocity().y()));
            }

            if (physics().velocity().x() < -physics().maxRunVelocity() * dt)
            {
                physics().setVelocity(Vector2f(-physics().maxRunVelocity() * dt,
                                               physics().velocity().y()));
            }

            if (physics().velocity().y() > physics().maxRunVelocity() * dt)
            {
                physics().setVelocity(Vector2f(physics().velocity().x(), physics().maxRunVelocity() * dt));
            }

            if (physics().velocity().y() < -physics().maxRunVelocity() * dt)
            {
                physics().setVelocity(Vector2f(physics().velocity().x(), -physics().maxRunVelocity() * dt));
            }

            physics().setVelocity(level.collide(position(), w(), h(), physics().velocity(), this));

            // Set new player position
            physics().setPosition(physics().position() + physics().velocity());

            // Checks if the player moves up or down and updates the source rect
            updateMoveAnimation();

            //Collision c = level.onActorCollision(this);
            //cout << c.delta() << endl;
        }

    }

    void Player::shoot()
    {
        // skip if no weapon is set
        if (m_weapon == 0)
        {
            return;
        }

        Vector2f direction(1, 0);
        m_weapon->shoot(direction, position());
    }

    void Player::onTileCollision()
    {
        return;
    }

    void Player::updateMoveAnimation()
    {
        const char NORMAL = 0;
        const char UPHALF = 1;
        const char UPFULL = 2;
        const char DOHALF = 3;
        const char DOFULL = 4;

        // Player moves up
        if (getMoveDirection().y() < 0)
        {
            switch (m_currentTileRow)
            {
                case NORMAL:
                    m_nextTileRow = UPHALF;
                    break;
                case DOHALF:
                    m_nextTileRow = NORMAL;
                    break;
                case DOFULL:
                    m_nextTileRow = DOHALF;
                    break;
                default:
                    m_nextTileRow = UPFULL;
            }
        } // Player moves down
        else if (getMoveDirection().y() > 0)
        {
            switch (m_currentTileRow)
            {
                case NORMAL:
                    m_nextTileRow = DOHALF;
                    break;
                case UPHALF:
                    m_nextTileRow = NORMAL;
                    break;
                case UPFULL:
                    m_nextTileRow = UPHALF;
                    break;
                default:
                    m_nextTileRow = DOFULL;
            }
        } // Player does not move
        else
        {
            switch (m_currentTileRow)
            {
                case DOFULL:
                    m_nextTileRow = DOHALF;
                    break;
                case UPFULL:
                    m_nextTileRow = UPHALF;
                    break;
                default:
                    m_nextTileRow = NORMAL;
            }
        }
    }

    void Player::onActorCollision(Actor& other)
    {
        if (!isGodMode() && !isGodModeCheat())
        {
            if (other.type() == ENEMY || other.type() == BOSS)
            {
                setHit(true);
                playHitMark();
                takeDamage(other.getCollisionDamage());
                if (getHealth() <= 0)
                {
                    setKilled(true);
                }
            }

            if (other.type() == PROJECTILE && getColor() == other.getColor())
            {
                Projectile* projectile = static_cast<Projectile*>(&other);
                if (projectile->getOriginActor() != this)
                {
                    setHit(true);
                    takeDamage(other.getCollisionDamage());
                }
            }
        }

        if (other.type() == POWERUP)
        {
            PowerUp* powerUp = static_cast<PowerUp*>(&other);
            m_powerUps.push_back(powerUp);

            // Necessary, so the powerup will be removed from game, but will NOT be deleted.
            // So the powerup will not be rendered anymore, but its object will still be existing.
            // The player will handle the deletion if the player drops the powerup.
            // See Player::consumePowerUps()
            m_game.removeActor(powerUp);
        }
    }

    void Player::playHitMark()
    {
        m_hitMarkSound.play(m_hitMarkVolume);
    }

    void Player::consumePowerUps()
    {
        vector<PowerUp*> to_remove;

        for (auto powerUp : m_powerUps)
        {
            // consume collected powerup at least once
            powerUp->consume(*this);

            // check if powerup has expired
            if (getLiveTime() > powerUp->getExpirationTime())
            {
                powerUp->stop(*this);
                to_remove.push_back(powerUp);
            }
        }

        for (auto powerUp : to_remove)
        {
            auto itr = std::find(m_powerUps.begin(), m_powerUps.end(), powerUp);
            m_powerUps.erase(itr);
            delete powerUp;
        }
    }

    void Player::setHealth(int health)
    {
        if (health > m_initial_health)
        {
            health = m_initial_health;
        }

        m_health = health;
    }

    SDL_Rect& Player::getHitbox()
    {
        SDL_Rect& hitbox = Actor::getHitbox();

        if (m_moveDirection.y() < 0)
        {
            hitbox.h = (int) (frameHeight() * 0.5);
            hitbox.y = (int) position().y();
        }
        else if (m_moveDirection.y() > 0)
        {
            hitbox.h = (int) (frameHeight() * 0.5);
            hitbox.y = (int) position().y() + hitbox.h;
        }

        return hitbox;
    }
} /* namespace ikaruga */
