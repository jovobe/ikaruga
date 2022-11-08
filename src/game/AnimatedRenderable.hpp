/**
 * AnimatedRenderable.hpp
 *
 * @date 04.12.15
 * @author Thomas Wiemann (twiemann@uni-osnabrueck.de)
 */
#ifndef SRC_ANIMATEDRENDERABLE_HPP_
#define SRC_ANIMATEDRENDERABLE_HPP_

#include "Renderable.hpp"
#include <string>
#include <iostream>

namespace ikaruga
{

    /**
     * @brief Base class of renderables with several animation frames
     */
    class AnimatedRenderable : public Renderable
    {
    public:

        /***
         * @brief Constructs an animated renderable from the given \ref filename for the internal \ref renderer
         *
         * @param renderer		A pointer to a SDL renderer struct
         * @param filename		A filename with animation definitions
         */
        AnimatedRenderable(SDL_Renderer* renderer, std::string filename);

        /***
         * @brief Constructs an animated renderable from given renderer, texture and frame information.
         *
         * @param renderer		A pointer to a SDL renderer struct
         * @param texture		A pointer to valid SDL_Texture struct
         * @param frameWidth	The width of the frames within the texture
         * @param frameHeight	The height of the frames within the texture
         * @param numFrames		The number of frames in the texture
         */
        AnimatedRenderable(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight,
                           int numFrames);


        /**
         * @brief Destructor.
         */
        virtual ~AnimatedRenderable();

        /**
         * @brief Renders the current frame
         */
        virtual void render() = 0;

        /**
         * @brief Moves the source rect to the next frame
         */
        void nextFrame();

        /**
         * @brief Sets frames per second for animation
         *
         * @param frames the frames per second of an animation
         */
        void setFPS(int frames);

        /**
         * @brief returns the numbers of frames per second of an animation
         *
         * @returns the fps of an object
         */
        int numFrames() const
        { return m_numFrames; }

        /**
         * @brief returns the frame width
         *
         * @returns frame width
         */
        int frameWidth() const
        { return m_frameWidth; }

        /**
         * @brief returns the fram height
         *
         * @returns frame height
         */
        int frameHeight() const
        { return m_frameHeight; }

    protected:

        ///	Number of frames in the animation
        int m_numFrames;

        /// Current frame number
        int m_currentFrame;

        /// The width of a frame
        int m_frameWidth;

        /// The height of a frame
        int m_frameHeight;

        /// Ticks count when the last frame was rendered
        Uint32 m_lastRenderTicks;

        /// Timeout between frames
        Uint32 m_frameTimeout;

        /// The tile row that is rendered in the current frame
        char m_currentTileRow;

        /// The tile row that should be rendered in the next frame
        char m_nextTileRow;
    };

} /* namespace ikaruga */

#endif /* SRC_ANIMATEDRENDERABLE_HPP_ */
