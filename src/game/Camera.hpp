/**
 * Camera.hpp
 * @brief Creates a camera
 *
 * @date 03.03.16
 * @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Vector.hpp"

namespace ikaruga
{
    /**
     * @brief A camera object to scroll within a level
     */
    class Camera
    {
    public:

        /**
         * @brief Constructs a camera at (0, 0)
         */
        Camera();

        /**
         * @brief Constructs a camera with the given pixel offsets
         *
         * @param pixel Current camera position
         * @param w Set view width
         * @param h Set view height
         */
        Camera(const Vector2f& pixel, int w, int h);

        /**
         * @brief 	Moves the camera to the given position. Reference point is the
         * 			middle of the represented screen.
         *
         * @param position	The new camera position
         */
        void move(const Vector2f& position);

        /**
         * @brief Returns the current x-position
         *
         * @return Current x-position.
         */
        float x();

        /**
         * @brief Returns the current y-position.
         *
         * @return Current y-position.
         */
        float y();

        /**
         * @brief Returns the curren position.
         *
         * @return Current camera position.
         */
        Vector2f& position();

        /**
         * @brief Destructor
         */
        virtual ~Camera();

        /**
         * @brief Returns the camera width.
         *
         * @return Camera width.
         */
        int w();

        /**
         * @brief Returns the camera height.
         *
         * @return Camera height.
         */
        int h();

        /**
         * @brief Get offset to the border which the player cannot cross.
         *
         * @return get offset to the border.
         */
        float getBorderOffset() const
        {
            return m_borderOffset;
        }

        /**
         * @brief Set offset to the border which the player cannot cross.
         *
         * @param borderOffset Offset to the border.
         */
        void setBorderOffset(float borderOffset)
        {
            m_borderOffset = borderOffset;
        }

        friend class MainWindow;

    private:

        /// Current camera position
        Vector2f m_position;

        /// Field of view width
        int m_width;

        /// Field of view height
        int m_height;

        // Border offset of the camera (in pixels) which the player cannot cross.
        float m_borderOffset;
    };
} /* namespace ikaruga */

#endif /* CAMERA_HPP_ */
