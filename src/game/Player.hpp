/**
 * Player.hpp
 *
 *  @date   01.03.16
 *
 *  @author Timo Osterkamp <tosterkamp@uos.de>
 */

#ifndef IKARUGA_PLAYER_H
#define IKARUGA_PLAYER_H

#include <fstream>
#include <iostream>
#include <string>
#include <SDL.h>
#include "Actor.hpp"
#include "Vector.hpp"
#include "Armed.hpp"
#include "Sound.hpp"
#include "PowerUp.hpp"

namespace ikaruga
{
    class PowerUp;

    /**
     * @brief	A class to represent an animated sprite controlled
     * 			by the user.
     */
    class Player : public Actor, public Armed
    {
    public:

        /**
         * Constructs a player.
         *
         * @param renderer		    A pointer to a valid SDL_Renderer struct that is
         * 						    used for rendering
         * @param texture		    A pointer to a valid SDL_Texture struct
         * @param frameWidth	    Frame width of the animation frames
         * @param frameHeight	    Frame height of the animation frames
         * @param numFrames		    Number of frames
         * @param health            start health
         * @param collisionDamage   the collision Damage a bot get
         */
        Player(SDL_Renderer* renderer,
               SDL_Texture* texture,
               Game& game,
               int frameWidth,
               int frameHeight,
               int numFrames,
               int health,
               int collisionDamage);

        /**
         * @see Actor::move(Level& level)
         */
        virtual void move(Level& level) override;

        /**
         * @see Collidable::onTileCollision()
         */
        virtual void onTileCollision() override;

        /**
         * @see Armed::shoot()
         */
        virtual void shoot() override;

        /**
         * @see Actor::onActorCollision(Actor& other)
         */
        virtual void onActorCollision(Actor& other) override;

        /**
         * @brief getter for move direction
         */
        const Vector2f& getMoveDirection() const
        {
            return m_moveDirection;
        }

        /**
         * @brief setter for move direction
         */
        void setMoveDirection(const Vector2f& moveDirection)
        {
            m_moveDirection = moveDirection;
        }

        /**
         * @brief Prints the player's position to the given stream
         * @param stream the given stream
         * @param vec the position
        */
        template<typename T>
        friend std::ostream& operator<<(std::ostream& stream, const Vector2<T>& vec);

        /**
         * @brief Sets the sound the player should make, when hit
         *
         * @param soundfile the path to the sound
         */
        void setHitMarkSound(std::string soundfile)
        {
            m_hitMarkSound = Sound(soundfile, SoundType::SOUND);
        }

        /**
         * Sets the volume the hitmarksound should be played with
         *
         * @param volume the volume
         */
        void setHitMarkVolume(int volume)
        {
            m_hitMarkVolume = volume;
        }

        /**
         * @brief  plays the hitmarksound
         */
        void playHitMark();

        /**
         * @brief This method iterates through all powerups that the player is owning.
         *        It consumes each powerup and removes those that are expired.
         */
        void consumePowerUps();

        /**
         * @see Actor::setHealth(int health)
         */
        virtual void setHealth(int health) override;

        /**
         * @brief getter for initial health
         */
        int getInitial_health() const
        {
            return m_initial_health;
        }

        /**
         * @brief return true if player is in godmode
         * @param isGodMode
         */
        bool isGodMode() const
        {
            return m_godMode;
        }

        /**
         * @brief return true if player is in godmode by cheat
         * @param isGodModeByCheat
         */
        bool isGodModeCheat() const
        {
            return m_godModeCheat;
        }

        /**
         * @brief set Player Godmode for the whole level
         */
        void setGodModeCheat()
        {
            m_godModeCheat = true;
            setGodModeDisplay();
        }

        /**
         * @brief set display of player to godmode
         */
        void setGodModeDisplay()
        {
            SDL_SetTextureColorMod(m_texture, m_ColorGod_R, m_ColorGod_G, m_ColorGod_B);
        }

        /**
         * @brief set display of player to normal
         */
        void resetGodModeDisplay()
        {
            SDL_SetTextureColorMod(m_texture, m_colorModR, m_colorModG, m_colorModB);
        }

        /**
         * @brief set or reset player to godmode
         * @param godMode if true then set, if false then reset
         */
        void setGodMode(bool godMode)
        {
            m_godMode = godMode;

            // This changes the color mod of the player when it is in godmode
            if (godMode || isGodModeCheat())
            {
                setGodModeDisplay();
            } // Change it to the initial value if godmode is gone.
            else
            {
                resetGodModeDisplay();
            }
        }

        /**
         * @see Actor::getHitbox()
         */
        virtual SDL_Rect& getHitbox() override;

    private:
        /** Game instance */
        Game& m_game;

        /** move direction */
        Vector2f m_moveDirection;

        /** inition health */
        int m_initial_health;

        /** Initial red value of the texture color mod */
        Uint8 m_colorModR;

        /** Initial green value of the texture color mod */
        Uint8 m_colorModG;

        /** Initial blue value of the texture color mod */
        Uint8 m_colorModB;

        //the sound file
        Sound m_hitMarkSound;

        //the volume of the hitmarksound
        int m_hitMarkVolume;

        /** A flag that is true when the player does not lose health when hit */
        bool m_godMode;

        /** A flag that is true when the player does not lose health when hit by cheat*/
        bool m_godModeCheat;

        /** Vector of all powerups that the player is currently owning */
        std::vector<PowerUp*> m_powerUps;

        /**
         * Gets invoked when the player moves up or down.
         * So the player gets rendered with a different texture,
         * and the hitbox is updated to a proper size and position.
         */
        void updateMoveAnimation();

        /** GodMode red value of the texture */
        const Uint8 m_ColorGod_R = 150;

        /** GodMode yellow value of the texture */
        const Uint8 m_ColorGod_G = 150;

        /** GodMode blue value of the texture */
        const Uint8 m_ColorGod_B = 239;
    };
} /* namespace ikaruga */

#endif //IKARUGA_PLAYER_H
