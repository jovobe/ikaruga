//
// Created by isaak on 26.11.15.
//

#include "WorldProperty.hpp"

namespace ikaruga
{

    WorldProperty::WorldProperty()
            : m_damping(0.95, 0.95), m_scrollingSpeed(100, 0)
    {

    }

    WorldProperty::WorldProperty(const Vector2f& damping)
            : m_damping(damping)
    {

    }

    const Vector2f& ikaruga::WorldProperty::damping() const
    {
        return m_damping;
    }

    void ikaruga::WorldProperty::setDamping(const Vector2f& damping)
    {
        m_damping = damping;
    }

} /* namespace ikaruga */
