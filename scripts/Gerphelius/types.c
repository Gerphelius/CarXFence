enum CXFObjectType
{
    NONE = -1,
    DESTRUCTIBLE,
    DESTRUCTIBLE_ANIMATED
}

enum CXFRPC
{
    OBJECT_DESTROYED = 48151623,
    OVERRIDES_LOAD
}

class CXFDestructbleData
{
    CXFObjectType m_type;
    float m_impulse;

    void CXFDestructbleData(CXFObjectType type, float impulse)
    {
        m_type = type;
        m_impulse = impulse;
    }
}

class CXFNoDestructionArea
{
    vector position;
    float radius;

    void CXFNoDestructionArea(vector pos, float r)
    {
        position = pos;
        radius = r;
    }
}

class CXFObjectInfo
{
    string p3dName;
    float impulseThreshold;

    void CXFObjectInfo(string name, float impulse)
    {
        p3dName = name;
        impulseThreshold = impulse;
    }
}

class CXFObjectOverride
{
    string p3dName;
    string direction;
    vector originOffset;

    void CXFObjectOverride(string name, string dir, vector offsets)
    {
        p3dName = name;
        originOffset = offsets;
        direction = dir;
    }
}

class CXFMarkedObject
{
    void CXFMarkedObject(notnull Object object, vector contactPos, vector contactDir, bool animated)
    {
        m_object = object;
        m_contactPos = contactPos;
        m_contactDir = contactDir;
        m_animated = animated;
    }

    Object GetObject()
    {
        return m_object;
    }

    vector GetContactPos()
    {
        return m_contactPos;
    }

    vector GetContactDir()
    {
        return m_contactDir;
    }

    bool IsAnimated()
    {
        return m_animated;
    }

    private Object m_object = null;
    private vector m_contactPos = "0 0 0";
    private vector m_contactDir = "0 0 0";
    private bool m_animated = false;
}
