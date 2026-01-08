class CXFAnimatedObject
{
    void CXFAnimatedObject(notnull Object object, vector contactDir, CXFObjectOverride objOverride)
    {
        m_object = object;
        object.GetTransform(m_initialTransform);
        m_rotationDir = Math.Sign(vector.Dot(object.GetDirection().Normalized(), contactDir.Normalized()));
        m_axis = m_object.GetDirection().Perpend() * -m_rotationDir;

        if (objOverride)
        {
            m_offset = m_offset + m_object.GetDirection() * objOverride.originOffset[2];
            m_offset = m_offset + m_object.GetDirectionAside() * objOverride.originOffset[0];
            m_offset = m_offset + m_object.GetDirectionUp() * objOverride.originOffset[1];

            switch (objOverride.direction)
            {
            case "front":

                break;

            case "aside":
                m_axis = -m_object.GetDirection();

                break;

            case "impact":
                m_axis = -contactDir.Perpend();

                break;
            }
        }

        /* Get ground position under object origin */
        vector contactPos;
        vector tmp;
        int tmp1;
        // TODO: calculate Y offset for endPos with object bounding box
        DayZPhysics.RaycastRV(m_initialTransform[3], m_initialTransform[3] + m_offset - vector.Up * 10.0, contactPos, tmp, tmp1, null, null, null, false, true);
        m_groundPos = contactPos;
    }

    /*
    * Returns if animation ended
    */
    bool Animate(float dt)
    {
        if (Math.AbsFloat(m_currentAngle) >= m_maxRotationAngle)
        {
            return true;
        }

        m_currentAngle = Math.Min(m_currentAngle + m_animationSpeed * dt, m_maxRotationAngle);
        float angleRad = m_currentAngle * Math.DEG2RAD;
        float cosAngle = Math.Cos(angleRad);
        float sinAngle = Math.Sin(angleRad);

        vector newTransform[4];
        newTransform[0] = vector.RotateAroundZero(m_initialTransform[0], m_axis, cosAngle, sinAngle);
        newTransform[1] = vector.RotateAroundZero(m_initialTransform[1], m_axis, cosAngle, sinAngle);
        newTransform[2] = vector.RotateAroundZero(m_initialTransform[2], m_axis, cosAngle, sinAngle);
        vector finalOffset = m_initialTransform[3] - m_groundPos - m_offset;
        newTransform[3] = vector.RotateAroundZero(finalOffset, m_axis, cosAngle, sinAngle) + m_groundPos;

        m_object.SetTransform(newTransform);

        return false;
    }

    private Object m_object = null;
    private vector m_initialTransform[4] = {};
    private vector m_groundPos = vector.Zero;
    private vector m_offset = vector.Zero;
    private vector m_axis = vector.Zero;
    private float m_rotationDir = 0.0;
    private float m_animationSpeed = 70.0;
    private float m_currentAngle = 0.0;
    private float m_maxRotationAngle = 85.0;
}
