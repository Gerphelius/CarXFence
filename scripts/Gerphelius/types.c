enum CXFObjectType
{
    NONE = -1,
    DESTRUCTIBLE,
    DESTRUCTIBLE_ANIMATED,
    TREE
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
    string p3d;

    void CXFDestructbleData(CXFObjectType type, float impulse, string p3dFullPath = "")
    {
        m_type = type;
        p3d = p3dFullPath;
        m_impulse = impulse;
    }
}

class CXFObjectInfo
{
    string p3d;
    string path;
    float impulseThreshold;

    void CXFObjectInfo(string p3dName, string p3dPath, float impulse)
    {
        p3d = p3dName;
        p3d.ToLower();
        path = p3dPath;
        impulseThreshold = impulse;
    }
}

class CXFObjectOverride
{
    string p3d;
    string direction;
    vector originOffset;

    void CXFObjectOverride(string p3dName, string dir, vector offsets)
    {
        p3d = p3dName;
        p3d.ToLower();
        originOffset = offsets;
        direction = dir;
        direction.ToLower();
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
