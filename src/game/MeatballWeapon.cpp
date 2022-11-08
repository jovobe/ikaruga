/**
 * MeatballWeapon.cpp
 * 
 * @date 02.03.16
 * @author Dennis Altenhoff (daltenhoff@uni-osnabrueck.de)
 */
#include "MeatballWeapon.hpp"
#include "Projectile.hpp"

namespace ikaruga
{
    MeatballWeapon::MeatballWeapon(Game& game,
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
                     WeaponType::MEATBALL_GUN)
    {

    }
} /* namespace ikaruga */
