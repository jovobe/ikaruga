#include "PlayerProperty.hpp"

namespace ikaruga
{
    PlayerProperty::PlayerProperty() :
            m_pos(0.0, 0.0),
            m_vel(0.0, 0.0),
            m_moveForce(800, 0),
            m_maxVelRun(122.0)
    {

    }

    PlayerProperty::PlayerProperty(
            const Vector2f& position,
            const Vector2f& moveForce,
            const Vector2f& velocity,
            double maxVel
    )
            : m_pos(position), m_vel(velocity), m_moveForce(moveForce), m_maxVelRun(maxVel)
    {

    }

    Vector2f& PlayerProperty::position()
    {
        return m_pos;
    }

    void PlayerProperty::setPosition(const Vector2f& pos)
    {
        m_pos = pos;
    }


    Vector2f& PlayerProperty::velocity()
    {
        return m_vel;
    }

    void PlayerProperty::setVelocity(const Vector2f& vel)
    {
        m_vel = vel;
    }

    const Vector2f& PlayerProperty::moveForce() const
    {
        return m_moveForce;
    }

    void PlayerProperty::setMoveForce(const Vector2f& move)
    {
        m_moveForce = move;
    }

    double PlayerProperty::maxRunVelocity() const
    {
        return m_maxVelRun;
    }

    void PlayerProperty::setMaxRunVelocity(double maxVelRun)
    {
        m_maxVelRun = maxVelRun;
    }

} /* namespace ikaruga */
