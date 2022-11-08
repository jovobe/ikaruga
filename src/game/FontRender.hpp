/*
 * FontRenderer.hpp
 *
 * @author Jochen Saalfeld (jsaalfeld@uni-osnabrueck.de)
 * @date 27.02.2016
 */

#ifndef IKARUGA_FONTRENDER_H
#define IKARUGA_FONTRENDER_H

#include "StaticRenderable.hpp"
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

namespace ikaruga
{
    /**
     * @brief a class for rendereing fonts from a tilesheet
     */
    class FontRender : public StaticRenderable
    {
    public:
        /**
         * @brief Constructor
         *
         * @param tileHeight the tileheigth
         * @param tileWidth the tilewith
         * @param renderer the sdl renderer
         * @param texture the texture
         */
        FontRender(int tileHeight,
                   int tileWidth,
                   SDL_Renderer* renderer,
                   SDL_Texture* texture);

        /**
         * @brief Returns the x and y coordinates of a number on a tilesheet
         *
         * @param number number to render
         * @param numberOffset the numberoffset in the tilesheet
         * @returns the x and y coordinates of the given number on the tilesheet
         */
        vector<Vector2i> renderNumber(int number, int numberOffset);

        /**
         * Returns the x and y coordinates of a String on a tilesheet
         *
         * @param str string to render
         * @param minusculeOffset offset of the lower case letter
         * @param capitalOffset offset of the capital letters
         * @param numberOffset offset of the numbers
         * @returns the x and y coordinates of the given string on the tileseet
         */
        vector<Vector2i> renderString(string str, int minusculeOffset, int capitalOffset, int numberOffset);

    private:

        /// the heigth of the letters on the tilesheet
        int m_tileHeight;

        /// the width of the letters on the tilesheet
        int m_tileWidth;
    };
} /* namespace ikaruga */

#endif //IKARUGA_FONTRENDER_H
