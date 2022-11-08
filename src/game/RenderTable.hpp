/**
* @file RenderTable.h
* @brief $BRIEF_DESCRIPTION
*
* @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
 * @author Marius Brockmöller
* @date 02 Mrz 2016
*/
#include "FontRender.hpp"
#include <stdexcept>

#ifndef IKARUGA_RENDERTABLE_HPP
#define IKARUGA_RENDERTABLE_HPP

namespace ikaruga
{
    class RenderTable : public FontRender
    {
    public:
        /**
         * @brief a struct that contains the necessary information for the RenterTalble
         */
        struct tableProperties
        {
            int positionX;
            int positionY;
            int width;
            int height;
        };

        /**
         * @brief Constructor of the RenderTable class
         * @param renderer SDL_Renderer* that renders the Game
         * @param defaultTexture SDL_Texture* texture for the font of the menu
         * @param tileHeight int the height for the font
         * @param tileWidth int  the width for the font
         */
        RenderTable(SDL_Renderer* renderer, SDL_Texture* defaultTtexture, int tileHeight, int tileWidth);


        /**
         * @brief Set string properties.
         * @param minusculeOffset Line of minuscule letters within font texture.
         * @param captialOffset Line of capital letters within font texture.
         * @param numberOffset Line of numbers within font texture.
         * @param content String for rendering.
         */
        void setStringProperties(int minusculeOffset, int capitalOffset, int numberOffset,
                                 std::vector<std::vector<std::string>> content);


        /**
         * @brief sets the properties for the RenderTable
         *
         * @param tableProperties the struct which contains the properties for the Rendertable
         */
        void setTableProperties(tableProperties properties);


        /**
         * @brief can change if a menu is scrollable
         *
         * @param boolean set true to make the menu scrollable
         */
        void setScrollable(bool scrollable);

        /**
         * @brief checks if the given char is a number
         *
         * @param char str the char which is checked
         * @returns boolean true if the char is a number
         */
        bool string_is_number(char const* str);

        /**
         * @brief retuns the current posistion of the index of the RenderTable
         *
         * @returns int the current position of the RenderTable index
         */
        unsigned long getM_pos() const;

        /**
         * @brief Function circles through the contents of the Randertable increasing the index
         */
        void increase();

        /**
         * @brief Function circles through the contents of the Randertable increasing the index
         */
        void decrease();

        /**
         * @brief resets the index of the RenderTable to the first in the vertex
         */
        void resetPos();

        /**
         * renders the RenderTabble
         */
        virtual void render();

    private:
        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
        int m_tileHeight;
        int m_tileWidth;
        int m_minusculeOffset;
        int m_capitalOffset;
        int m_numberOffset;
        tableProperties m_tableProperties;
        std::vector<std::vector<std::string>> m_content;
        vector<Vector2i> m_textLine;
        SDL_Rect m_rectSource;
        SDL_Rect m_rectTarget;
        bool m_stringPropertiesSet;
        bool m_tablePropertiesSet;
        unsigned long m_pos;
        bool m_scrollable;
    };
}  /* namespace ikaruga */

#endif //IKARUGA_RENDERTABLE_HPP
