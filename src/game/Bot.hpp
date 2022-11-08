/**
 * Bot.hpp
 *
 *  @date   01.03.16
 *
 *  @author Timo Osterkamp <tosterkamp@uos.de>
 */

#ifndef SRC_BOT_HPP_
#define SRC_BOT_HPP_

#define _USE_MATH_DEFINES

#include "Actor.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include <math.h>
#include <time.h>
#include "Armed.hpp"
#include "../xml/XML.hpp"

namespace ikaruga
{
    class Game;

    namespace BotType
    {
        enum BotMoveType
        {
            NO_MOVE,
            SIN,
            SIN_UP,
            SIN_DOWN,
            AI,
            CIRCLE
        };
    }

    /**
     * @brief An actor that moves in a level according to a predefined movement pattern.
     * 		  The default implementation switches x-direction when it hits an object.
     */
    class Bot : public Actor, public Armed
    {
    public:

        /**
         * @brief	Constructs a bot from given renderer, texture
         * 			and frame information.
         * @param renderer		    A pointer to a SDL renderer struct
         * @param texture		    A pointer to valid SDL_Texture struct
         * @param frameWidth	    The width of the frames within the texture
         * @param frameHeight	    The height of the frames within the texture
         * @param numFrames		    The number of frames in the texture
         * @param game              The instance of Game
         * @param npc               The NPC struct from the XML file
         * @param health            The start health value
         * @param collisionDamage   The collision Damage
         * @param type              the ActorType
         */

        Bot(SDL_Renderer* renderer,
            SDL_Texture* texture,
            int frameWidth,
            int frameHeight,
            int numFrames,
            Game* game,
            XML::NPC npc,
            int health,
            int collisionDamage,
            ActorType type);

        /**
         * @brief   Destructor
         */
        virtual ~Bot();

        /**
         * @see Actor::move(Level& level)
         */
        virtual void move(Level& level) override;

        /**
         * @see Collidable::onTileCollision()
         */
        virtual void onTileCollision() override;

        /**
         * @see Actor::onActorCollision(Actor& other)
         */
        virtual void onActorCollision(Actor& other) override;

        /**
         * @see Armed::shoot()
         */
        virtual void shoot() override;

    private:

        /** The trace speed of an AI bot */
        const float AI_TRACE_SPEED = 0.7;

        /** the move type of the bot */
        int m_move_type;

        /** an struct with bot infos */
        XML::NPC m_npc;

        /** the game instance */
        Game* m_game;
    };

} /* namespace ikaruga */

#endif /* SRC_BOT_HPP_ */
