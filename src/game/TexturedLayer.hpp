/*
 * TexturedLayer.hpp
 *
 *  Created on: Jan 2, 2016
 *      Author: twiemann
 */

#ifndef SRC_TEXTUREDLAYER_HPP_
#define SRC_TEXTUREDLAYER_HPP_

#include "StaticRenderable.hpp"

namespace ikaruga
{

    /**
     * @brief A class to render a background bitmap
     */
    class TexturedLayer : public StaticRenderable
    {
    public:

        /**
         * Constructs a layer for the given renderer
         *
         * @param renderer		The SDL-Renderer to render the layer
         */
        TexturedLayer(SDL_Renderer* renderer);

        /**
         * Constructs a layer for the given renderer
         *
         * @param renderer		The SDL-Renderer to render the layer
         * @param texture
         * @param tileHeightLevel
         */
        TexturedLayer(SDL_Renderer* renderer, SDL_Texture* texture, int tileHeightLevel);

        /**
         * Renders the texture to the given layer
         */
        virtual void render();

        /// Destructor.
        virtual ~TexturedLayer();

        /**
         * Sets the scroll speed for the layer
         *
         * @param speed
         */
        void setScrollSpeed(float speed);


        /**
         * Used to calc non render part at top
         */
        int m_tileHeightLevel;

    protected:

        /// Curent scroll speed
        float m_scrollSpeed;
    };

} /* namespace ikaruga */

#endif /* SRC_TEXTUREDLAYER_HPP_ */
