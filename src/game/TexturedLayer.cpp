/*
 * TexturedLayer.cpp
 *
 *  Created on: Jan 2, 2016
 *      Author: twiemann
 */

#include "TexturedLayer.hpp"

using std::cout;
using std::endl;

namespace ikaruga
{
    TexturedLayer::TexturedLayer(SDL_Renderer* renderer)
            : StaticRenderable(renderer)
    {
        m_scrollSpeed = 1.0f;
    }

    TexturedLayer::TexturedLayer(SDL_Renderer* renderer, SDL_Texture* texture, int tileHeightLevel)
            : StaticRenderable(renderer, texture)
    {
        m_scrollSpeed = 1.0f;

        m_tileHeightLevel = tileHeightLevel;
    }

    void TexturedLayer::render()
    {
        SDL_Rect target;

        // Determine x and y offset
        int xOff = ((int) std::floor(m_camera.x() * m_scrollSpeed)) % m_sourceRect.w;
        int yOff = ((int) std::floor(m_camera.y() * m_scrollSpeed)) % m_sourceRect.h;

        // Handle sign (why is there no signum function in C++?
        if (m_camera.x() > 0)
        {
            xOff = -xOff;
        }

        if (m_camera.y() > 0)
        {
            yOff = -yOff;
        }

        // Start rendering
        target.x = xOff;
        target.y = yOff + (m_camera.h() % m_tileHeightLevel);
        target.w = m_sourceRect.w;
        target.h = m_sourceRect.h;

        while (target.y < m_camera.h())
        {
            while (target.x < m_camera.w())
            {
                SDL_RenderCopy(m_renderer, m_texture, &m_sourceRect, &target);
                target.x += m_sourceRect.w;
            }
            target.y += m_sourceRect.h;
            target.x = xOff;
        }
    }

    TexturedLayer::~TexturedLayer()
    {
        // TODO Auto-generated destructor stub
    }

    void TexturedLayer::setScrollSpeed(float speed)
    {
        m_scrollSpeed = speed;
    }

} /* namespace ikaruga */
