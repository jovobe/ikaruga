/**
* @file Renderable.hpp
* @brief Base class for all objects that can be rendered
*
* @author Thomas Wiemann (twiemann@uos.de)
*/
#ifndef IKARUGA_RENDERABLE_H
#define IKARUGA_RENDERABLE_H

#include <SDL.h>
#include <string>
#include "Camera.hpp"

namespace ikaruga
{


    /**
     * @brief Base class for all objects that can be rendered.
     */
    class Renderable
    {
    public:

        /**
         * @brief Constructs a Renderable for the given renderer
         *
         * @param m_renderer pointer to a valid SDL_Renderer structure
         */
        Renderable(SDL_Renderer* m_renderer);

        /**
         * @brief Contructs a renderable from given texture and renderer.
         *
         * @param renderer pointer to a valid SDL_Renderer
         * @param texture pointer to a valid SDL_Texture
         */
        Renderable(SDL_Renderer* renderer, SDL_Texture* texture);

        /**
         * @brief   Renderer getter
         * @return  SDL_Renderer
         */
        SDL_Renderer* getRenderer() const;

        /**
         * @brief returns the texture pointer
         *
         * @return texture pointer
         */
        SDL_Texture* getTexture() const;

        /**
        * @brief   Renders the object.
        */
        virtual void render() = 0;

        /**
         * @brief returns the width of the rendered object
         *
         * @returns the width of the rendered object
         */
        int w() const;

        /**
         * @brief returns the height of the rendered object
         *
         * @returns the height of the rendered object
         */
        int h() const;

        /**
         * @brief global camera object
         * @description global camera object that is used to determine the offset wrt. the current camera position
         * when rendering
         */
        static Camera m_camera;

        /**
         * @brief Destructor
         */
        virtual ~Renderable();

    protected:

        /// Renderer
        SDL_Renderer* m_renderer;

        /// A texture object
        SDL_Texture* m_texture;

        /// Source rect in the texture
        SDL_Rect m_sourceRect;

    };
} /* namespace ikaruga */

#endif //IKARUGA_RENDERABLE_H
