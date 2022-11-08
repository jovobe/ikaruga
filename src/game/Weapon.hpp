/**
 * Weapon.hpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef IKARUGA_WEAPON_HPP
#define IKARUGA_WEAPON_HPP

#include <SDL_stdinc.h>
#include <SDL_render.h>
#include "Vector.hpp"
#include "Sound.hpp"

using std::string;

namespace ikaruga
{
    class Game;

    class Actor;
    namespace WeaponType
    {
        enum WeaponType
        {
            NONE,
            LASER_GUN,
            BLASTER_GUN,
            ROCKET_GUN,
            MEATBALL_GUN,
            CPP_GUN
        };
    }
    /**
     * @brief Absract class for weapons. Handles basic functionality like weapon cool down.
     */
    class Weapon
    {
    public:

        /**
         * Desctructor
         */
        virtual ~Weapon();

        /**
         * Creates projectiles and adds them to the game
         *
         * @param direction Direction in which the projectile should move
         * @param spawnPosition Position where the projectiles should spawn
         */
        void shoot(const Vector2f& direction, const Vector2f& spawnPosition);

        /**
         * Returns the Weapon Name
         *
         * @returns: Weapon Name
         */
        string getWeaponName(void)
        { return m_name; }

        /**
         * Sets the actor
         *
         * @param m_actor Actor to set
         */
        void setActor(Actor* m_actor)
        {
            Weapon::m_actor = m_actor;
        }

        /**
         * Returns the Weapon Evolution Stage
         *
         * @returns: Weapon Evolution Stage
         */
        int getEvolutionStage(void)
        { return m_evolution; }

        /**
         * Sets the Weapon Evolution Stage
         *
         * @param evolution Evolution stage
         */
        void setEvolutionStage(int evolution)
        { m_evolution = evolution; }

        /**
         * Upgrades the Weapon Evolution Stage
         *
         */
        void upgrade();

        /**
         * Returns type of the weapon
         *
         * @return Type of the weapon
         */
        const WeaponType::WeaponType& getWeaponType() const
        {
            return m_weaponType;
        }

    protected:

        /**
         * Creates a weapon
         *
         * @param game Game object where to add the projectiles
         * @param actor From which the projectiles are launched
         * @param projectileTexture Texture for the projectiles
         * @param projectileTextureSize Size of the the texture for the projectiles
         * @param weaponOffset Offset for the weapon from the top left cornor of the player
         * @param projectileColorOffset Offset for the second color in the projectile texture
         * @param coolDown Cool down for the weapon (time between shoots)
         * @param name Name of the weapon
         * @param evolution Evolution Stage of the Weapon
         * @param sound String to soundfile
         * @param volume Volume of shoot sound
         * @param collisionDamage Damage of collision
         * @param evolutionScale Scale of projectiles with evolution
         * @param speed Speed of projectiles launched by this weapon
         * @param numFrames Number of frames for the projectile animation
         * @param weaponType Type of weapon
         */
        Weapon(Game& game,
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
        );

        // Game where to add the projectiles
        Game& m_game;

        // Actor which shoots the projectiles
        Actor* m_actor;

        // Timestamp of the last shoot
        Uint32 m_lastShoot;

        // Cool down for the weapon
        float m_coolDown;

        // Texture for the projectile
        SDL_Texture* m_projectileTexture;

        // Size of the projectile texture
        const Vector2i& m_projectileTextureSize;

        // Offset for the weapon from the top left cornor of the actor
        const Vector2f& m_weaponOffset;

        // Offset for the second color in the projectile texture
        const Vector2f& m_projectileColorOffset;

        /**
         * Checks if the weapon is ready to fire (waits for weapon cool down)
         *
         * @return True if the weapon can be fired, false else
         */
        bool weaponReady();

        //Name of the Weapon
        string m_name;

        //Evolution Stage of Weapon
        int m_evolution;

        // The sound, the Weapon should make
        Sound m_sound;

        // Volume
        int m_volume;

        // Damage when colliding
        int m_collisionDamage;

        // Scale of projectiles with evolution
        int m_evolutionScale;

        // Speed of projectiles launched by this weapon
        float m_speed;

        // Number of frames for projectile animation
        int m_numFrames;

        // Type of weapon
        WeaponType::WeaponType m_weaponType;
    };
} /* namespace ikaruga */


#endif //IKARUGA_WEAPON_HPP
