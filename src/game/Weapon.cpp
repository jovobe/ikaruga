/**
 * Weapon.cpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include <SDL_timer.h>
#include "Weapon.hpp"
#include "Projectile.hpp"

using std::string;

namespace ikaruga
{
    Weapon::Weapon(Game& game,
                   Actor& actor,
                   SDL_Texture* projectileTexture,
                   const Vector2i& projectileTextureSize,
                   const Vector2f& weaponOffset,
                   const Vector2f& projectileColorOffset,
                   float coolDown,
                   string name,
                   int evolution,
                   std::string sound,
                   int volume,
                   int collisionDamage,
                   int evolutionScale,
                   float speed,
                   int numFrames,
                   WeaponType::WeaponType weaponType
    )
            : m_game(game), m_actor(&actor), m_lastShoot(0), m_coolDown(coolDown),
              m_projectileTexture(projectileTexture),
              m_projectileTextureSize(projectileTextureSize), m_weaponOffset(weaponOffset),
              m_projectileColorOffset(projectileColorOffset), m_name(name), m_evolution(evolution),
              m_sound(Sound(sound, SoundType::SOUND)),
              m_volume(volume), m_collisionDamage(collisionDamage),
              m_evolutionScale(evolutionScale),
              m_speed(speed), m_numFrames(numFrames), m_weaponType(weaponType)
    {

    }

    Weapon::~Weapon()
    {
        delete &m_projectileTextureSize;
        delete &m_weaponOffset;
        delete &m_projectileColorOffset;
    }

    void Weapon::shoot(const Vector2f& direction, const Vector2f& spawnPosition)
    {
        // Ignore shoots when weapon is not ready
        if (!weaponReady())
        {
            return;
        }

        // Number of projectiles
        int numProjectiles = getEvolutionStage() * m_evolutionScale;

        // Scale of spread of projectiles growing with projectile height
        float spreadScale = m_projectileTextureSize.y() * 0.005f;

        // Spawn position of projectiles
        Vector2f spawnPos = spawnPosition;

        // Adjust projectile spawn, considering shoot direction
        if (direction.x() > 0)
        {
            spawnPos += m_actor->w();
            spawnPos += Vector2f(-m_weaponOffset.x(), m_weaponOffset.y());
        }
        else
        {
            spawnPos += Vector2f(m_weaponOffset.x(), m_weaponOffset.y());
        }

        // yOffset for even projectile number
        float yOffset = -(((numProjectiles + 1) % 2) * 0.5f);

        // Pointer for created projectiles
        Projectile* projectile;

        for (int i = 0; i < numProjectiles; i++)
        {
            // Create new projectile
            projectile = new Projectile(m_actor->getRenderer(),
                                        m_projectileTexture,
                                        m_projectileTextureSize.x(),
                                        m_projectileTextureSize.y(),
                                        m_numFrames,
                                        m_collisionDamage,
                                        m_speed);

            // Calculate y-movement of current projectile
            float moveY = ((numProjectiles / 2) - i + yOffset) * spreadScale;

            // Set projectile properties
            projectile->setColorOffset(m_projectileColorOffset);
            projectile->setDirection(Vector2f(direction.x(), moveY));
            projectile->setType(ActorType::PROJECTILE);
            projectile->setPosition(spawnPos);
            projectile->setColor(m_actor->getColor());
            projectile->setOriginActor(m_actor);
            projectile->launch();

            // Add created projectile to actors
            m_game.addActor(projectile);
        }

        if (m_actor->type() == ActorType::PLAYER)
        {
            m_sound.play(m_volume, this->m_coolDown * 1000);
        }
    }

    void Weapon::upgrade()
    {
        setEvolutionStage(getEvolutionStage() + 1);
    }

    bool Weapon::weaponReady()
    {
        if (m_lastShoot == 0)
        {
            m_lastShoot = SDL_GetTicks();
            return true;
        }

        Uint32 ticks = SDL_GetTicks();
        float time = (ticks - m_lastShoot) / 1000.0f;
        if (time > m_coolDown)
        {
            m_lastShoot = ticks;
            return true;
        }

        return false;
    }
} /* namespace ikaruga */
