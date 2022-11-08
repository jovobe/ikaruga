/**
 * CppWeapon.hpp
 *
 * @date 03.03.16
 * @author Jochen Saalfeld (jsaalfeld@uni-osnabrueck.de)
 */
#include "CppWeapon.hpp"
#include "Projectile.hpp"

namespace ikaruga
{
    CppWeapon::CppWeapon(Game& game,
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
                     "Blaster",
                     1,
                     sound,
                     volume,
                     collisionDamage,
                     1,
                     speed,
                     numFrames,
                     WeaponType::CPP_GUN)
    { }
} /* namespace ikaruga */
