#ifndef SRC_ACTOR_HPP_
#define SRC_ACTOR_HPP_

#include "AnimatedRenderable.hpp"
#include "PlayerProperty.hpp"
#include "WorldProperty.hpp"
#include "Level.hpp"
#include "Collidable.hpp"

#include <string>
#include <thread>
#include <chrono>
#include "Sound.hpp"

namespace ikaruga
{
    enum ActorType
    {
        ENEMY,
        PLATFORM,
        ITEM,
        PLAYER,
        PROJECTILE,
        BOSS,
        POWERUP
    };

    namespace ColorMode
    {
        enum ColorMode
        {
            NONE,
            BLACK,
            WHITE
        };
    }

    /**
     * @brief A class the represents a sprite that is moving and implements
     * collision detection.
     */
    class Actor : public AnimatedRenderable, public Collidable
    {
    public:

        /**
         * Constructs an actor from the given \ref filename
         * for the internal \ref renderer
         * @param renderer		A pointer to a SDL renderer struct
         * @param filename		A filename with animation definitions
         */
        Actor(
                SDL_Renderer* renderer,
                SDL_Texture* texture,
                int frameWidth,
                int frameHeight,
                int numFrames,
                int health,
                int collisionDamage);

        virtual ~Actor();

        /**
         * @brief Move the Actor
         * Every Actor can be moved in a certain level instance.
         * The movement will be handled by the Actor subclasses separately.
         * @param level The level instance
         */
        virtual void move(Level& level) = 0;

        /**
         * @brief Render the Actor
         * By invoking this method, the Actor gets rendered. This can be overriden by its subclasses.
         */
        virtual void render();

        /**
         * @brief Returns the player's physical properties
         * @return The PlayerProperty reference
         */
        PlayerProperty& physics();

        /**
         * @brief Change color of Actor
         * Every Actor represents it's state by one of two colors defined by ColorMode::ColorMode.
         * By invoking this method the color gets toggled to the opposite color.
         */
        void toggleColor();

        /**
         * @brief Set the spawning time.
         * By invoking this method the spawning time is set.
         */
        void setLiveTime();

        /**
         * @brief Play an explosion sound
         * If an Actor dies, its explosion sound will be played by invoking this function.
         */
        void playExplosionSound();

        /**
         * @brief Add damage to Actor
         * Any Actor's health can be reduced by the damage it takes.
         * @param damage The damage value
         */
        void takeDamage(int damage);

        /**
         * @brief Returns the representing color
         * An Actor can represent the black or white color defined
         * in ColorMode::ColorMode.
         *
         * @return The color that the Actor represents
         */
        const ColorMode::ColorMode& getColor() const
        { return m_color; }

        /**
         * @brief Returns the color offset
         * Depending on the Actor's current color state, the position of the Actor's sprite
         * is different. By defining a color offset, the proper texture will be rendered.
         *
         * @return The color offset as a Vector2f
         */
        const Vector2f& getColorOffset() const
        { return m_colorOffset; }

        /**
         * @brief Returns the Actor's hitbox
         * Every Actor owns a hitbox that can collide with other Actor's hitboxes.
         * @return A SDL_Rect reference representing the hitbox
         */
        virtual SDL_Rect& getHitbox();

        /**
         * @brief Returns if an Actor was hit
         * Returns true if the Actor was hit in the current update.
         * @return Flag if Actor was hit
         */
        bool isHit() const
        {
            return m_hit;
        }

        /**
         * @brief Returns if Actor is dead
         * Returns true if an Actor was killed and false otherwise.
         * @return killed status
         */
        bool isKilled() const
        {
            return m_isKilled;
        }

        /**
         * @brief Returns the current health of an Actor
         * @return health value
         */
        int getHealth() const;

        /**
         * @brief Returns the reward for killing this Actor
         * The player gets rewarded by this score for killing this Actor.
         * @return Reward value
         */
        int getScoreValue() const
        {
            return m_scoreValue;
        }

        /**
         * @brief Returns visibility
         * Returns true, if the Actor is visible (in camera rectangle).
         * @return Visibility status
         */
        bool visible();

        /**
         * @brief Returns Actor's position
         * Returns the Actor's current position
         * @return Position
         */
        Vector2f position();

        /**
         * @brief Returns Actor's type
         * Returns the type of Actor it represents.
         * @return Actor's type
         */
        const ActorType& type()
        { return m_type; }

        /**
         * @brief Set the ColorMode
         * Set the color the Actor shall represent.
         */
        void setColor(const ColorMode::ColorMode& m_color)
        { Actor::m_color = m_color; }

        /**
         * @brief Set color offset
         * Set the color offset where the second color is located in the Actor's sprite.
         */
        void setColorOffset(const Vector2f& colorOffset)
        { m_colorOffset = colorOffset; }

        /**
         * @brief Set the explosion sound
         * When this Actor gets killed then this set sound gets played.
         *
         * @param explosionSoundFilename The filepath to the explosion sound
         */
        void setExplosionSound(std::string explosionSoundFilename)
        {
            m_explosionSound = Sound(explosionSoundFilename, SoundType::SOUND);
        };

        /**
         * @brief Set explosion volume
         * The volume of the explosion sound.
         *
         * @param volume Volume value
         */
        void setExplosionVolume(int volume)
        {
            m_explosionVolume = volume;
        }

        /**
         * @brief Set Focus
         * Set the Actor's focus.
         * @param focus True if it shall have focus, false otherwise.
         */
        void setFocus(bool focus);

        /**
         * @brief Set health
         * Set the Actor's current health.
         * @param health Current health value
         */
        virtual void setHealth(int health)
        {
            m_health = health;
        }

        /**
         * @brief Set hit status
         * Set the hit status to trueif the Actor collided with an Projectile.
         * @param hit True if hit and false otherwise.
         */
        void setHit(bool hit)
        {
            m_hit = hit;
        }

        /**
         * @brief Set killed status
         * Set the killed status to true, if the Actor has been killed.
         * @param killed True if killed and false otherwise.
         */
        void setKilled(bool killed)
        {
            m_isKilled = killed;
        }

        /**
         * @brief Set physics
         * Set the Actor's physic properties.
         * @param p The physic properties
         */
        void setPhysics(PlayerProperty p);

        /**
         * Sets the player's position
         */
        void setPosition(Vector2f pos);

        /**
         * @brief Set score value
         * Set the score value that the player gets rewarded by killing this Actor.
         * @param score value
         */
        void setScoreValue(int value)
        {
            m_scoreValue = value;
        }

        /**
         * @brief Set Actor's type
         * Set the Actor's type that it should represent.
         * @param t The type
         */
        void setType(ActorType t)
        { m_type = t; }

    protected:
        /// The color that the Actor is currently representing
        ColorMode::ColorMode m_color;

        /// The color offset where the second color is located in the sprite.
        Vector2f m_colorOffset;

        /// The sound that is played at explosion.
        Sound m_explosionSound;

        // Explosion Volume
        int m_explosionVolume;

        /// Focus status.
        bool m_focus;

        /// The Actor's current health value.
        int m_health;

        /// Kill status
        bool m_isKilled;

        /// The physical properties of the player
        PlayerProperty m_physicalProps;

        /// Rewarding score value.
        int m_scoreValue;

        /// The time when the Actor has spawned.
        Uint32 m_spawnTime;

        /// The time at start.
        Uint32 m_startTicks;

        /// The type that the Actor is representing.
        ActorType m_type;

        /**
         * @brief Get elapsed time
         * Get the elapsed time in seconds since beginning.
         * @return The time elapsed.
         */
        float getElapsedTime();

        /**
         * @brief Get flip necessity
         * @return Whether or not a texture flip is necessary
         */
        virtual SDL_RendererFlip getFlip();

        /**
         * @brief Get the current time
         * Get the current time in seconds since the Actor has spawned.
         * @return Current time since spawning.
         */
        float getLiveTime();

    private:
        /**
         * @brief Render the hitbox
         * By invoking this method the hitbox gets rendered as well.
         */
        void renderHitbox();
    };

} /* namespace ikaruga */

#endif /* SRC_ACTOR_HPP_ */
