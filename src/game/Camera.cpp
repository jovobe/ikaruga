/*
 * Camera.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#include "Camera.hpp"

namespace ikaruga
{

    float Camera::x()
    {
        return m_position.x();
    }

    float Camera::y()
    {
        return m_position.y();
    }

    Camera::Camera()
            : m_width(0), m_height(0), m_borderOffset(5)
    {
        m_position.setX(0);
        m_position.setY(0);
    }

    void Camera::move(const Vector2f& p)
    {
        m_position = p;
    }

    Camera::Camera(const Vector2f& Vector2f, int w, int h)
            : m_position(Vector2f), m_width(w), m_height(h), m_borderOffset(5)
    {
    }

    Vector2f& Camera::position()
    {
        return m_position;
    }

    Camera::~Camera()
    {
        // Nothing to do yet
    }

    int Camera::w()
    {
        return m_width;
    }

    int Camera::h()
    {
        return m_height;
    }

} /* namespace ikaruga */
