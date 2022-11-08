/**
 * LaserWeapon.cpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include "LaserWeapon.hpp"
#include "Projectile.hpp"

namespace ikaruga
{
    LaserWeapon::LaserWeapon(Game& game,
                             Actor& actor,
                             SDL_Texture* projectileTexture,
                             const Vector2i& projectileTextureSize,
                             const Vector2f& weaponOffset,
                             const Vector2f& projectileColorOffset,
                             float coolDown,
                             std::string sound,
                             int volume,
                             int collisionDamage,
                             float speed,
                             int numFrames)
            : Weapon(game,
                     actor,
                     projectileTexture,
                     projectileTextureSize,
                     weaponOffset,
                     projectileColorOffset,
                     coolDown,
                     "LaserGun",
                     1,
                     sound,
                     volume,
                     collisionDamage,
                     1,
                     speed,
                     numFrames,
                     WeaponType::LASER_GUN)
    { }
} /* namespace ikaruga */
