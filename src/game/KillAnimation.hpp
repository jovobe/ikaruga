/*
 * KillAnimation.hpp
 *
 *  Created on: Feb 21, 2016
 *      Author: twiemann
 */

#ifndef SRC_GAME_KILLANIMATION_HPP_
#define SRC_GAME_KILLANIMATION_HPP_

#include "Actor.hpp"

namespace ikaruga
{

    class KillAnimation : public Actor
    {
    public:
        KillAnimation(Actor* actor, std::string filepath);

        virtual ~KillAnimation();


        virtual void move(Level& level) override;
        //virtual void render();



        virtual void onTileCollision() override;

        virtual void onActorCollision(Actor& other) override;
    };

} /* namespace ikaruga */

#endif /* SRC_GAME_KILLANIMATION_HPP_ */
