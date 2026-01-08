/*
* TODO:
*       configure impulse to destroy per object or type
*
*       add extendended config to fix some objects rotations on destroy
*       add sounds
*       remove wires from electric poles
*       area with no object damage with admin debug
*       clear deletedObjects array on disconnect
*       add particles
*
*       refactor according to dayz guidelines
*       ToLower all p3d name checks
*/

class CXFDestructibleObject
{
    void CXFDestructibleObject(notnull Object obj, vector contactPos, vector contactDir, string p3dFullPath = "")
    {
        m_objectLink = new OLinkT(obj);
        m_events = obj.GetEventMask();
        obj.GetTransform(m_transform);
        m_contactPos = contactPos;
        m_contactDir = contactDir;
        m_p3dFullPath = p3dFullPath;
    }

    void ~CXFDestructibleObject()
    {
#ifndef SERVER
        Object obj = GetObject();

        obj.SetEventMask(m_events);
        obj.SetTransform(m_transform);
        obj.Update();
#endif
    }

    void Destroy()
    {
        Object obj = GetObject();

        obj.SetScale(0.000001);
        obj.SetPosition(vector.Zero);
        obj.ClearEventMask(m_events);
        obj.SetEventMask(EntityEvent.NOTVISIBLE);
        obj.Update();

#ifdef SERVER
        dBodyDestroy(obj);
#endif
    }

    Object GetObject()
    {
        return m_objectLink.Ptr();
    }

    vector GetContactPos()
    {
        return m_contactPos;
    }

    vector GetContactDir()
    {
        return m_contactDir;
    }

    string GetP3DFullPath()
    {
        return m_p3dFullPath;
    }

    private ref OLinkT m_objectLink = null;
    private int m_events = 0;
    private vector m_transform[4] = {};
    private vector m_contactPos = vector.Zero;
    private vector m_contactDir = vector.Zero;
    private string m_p3dFullPath = "";
}

class CXFDestructionManager : Managed
{
    static void Init()
    {
        CXFConfig.Load();
        s_config = CXFConfig.Get();
    }

    static void MarkForDestroy(notnull Object obj, vector contactPos, vector contactDir, string p3dFullPath)
    {
        if (g_Game.IsDedicatedServer())
        {
            int objId = obj.GetID();

            if (!s_markedObjects.Contains(objId))
            {
                s_markedObjects[objId] = new CXFDestructibleObject(obj, contactPos, contactDir, p3dFullPath);
            }
        }
    }

    static void DestroyMarkedObjects()
    {
        if (g_Game.IsDedicatedServer())
        {
            ScriptRPC rpc = new ScriptRPC();

            rpc.Write(s_markedObjects.Count());

            foreach(CXFDestructibleObject markedObj : s_markedObjects)
            {
                Object obj = markedObj.GetObject();

                rpc.Write(obj);
                rpc.Write(markedObj.GetContactPos());
                rpc.Write(markedObj.GetContactDir());
                rpc.Write(markedObj.GetP3DFullPath());

                markedObj.Destroy();
                s_destroyedObjects.Insert(markedObj);
            }

            rpc.Send(null, CXFRPC.OBJECT_DESTROYED, true, null);
            s_markedObjects.Clear();
        }
    }

    static void SyncDestroyedObjectsOnClient(PlayerIdentity identity)
    {
        int destroyedCount = s_destroyedObjects.Count();

        if (g_Game.IsDedicatedServer() && destroyedCount)
        {
            ScriptRPC rpc = new ScriptRPC();

            rpc.Write(destroyedCount);

            foreach(CXFDestructibleObject destructibleObj : s_destroyedObjects)
            {
                rpc.Write(destructibleObj.GetObject());
                rpc.Write(destructibleObj.GetContactPos());
                rpc.Write(destructibleObj.GetContactDir());
                rpc.Write(destructibleObj.GetP3DFullPath());
            }

            rpc.Send(null, CXFRPC.OBJECT_DESTROYED, true, identity);
        }
    }

    static void DestroyObjectOnClient(notnull Object obj, vector contactPos, vector contactDir, string p3dFullPath)
    {
        if (!g_Game.IsDedicatedServer())
        {
            ref CXFDestructibleObject destructibleObj = new CXFDestructibleObject(obj, contactPos, contactDir, p3dFullPath);

            destructibleObj.Destroy();
            s_destroyedObjects.Insert(destructibleObj);
        }
    }

    static void ResetDestroyedObjects()
    {
        s_destroyedObjects.Clear();
    }

    static CXFDestructbleData GetDestructibleData(Object object)
    {
        if (object.IsTree())
        {
            // TODO: add impulse config variable for trees
            return CXFDestructbleData(CXFObjectType.TREE, 2000.0);
        }

        foreach(CXFObjectInfo destructible : s_config.destructible)
        {
            string destrName = object.GetDebugName();
            destrName.ToLower();

            if (destrName.Contains(destructible.p3d))
            {
                return CXFDestructbleData(CXFObjectType.DESTRUCTIBLE, destructible.impulseThreshold);
            }
        }

        foreach(CXFObjectInfo animated : s_config.destructibleAnimated)
        {
            string animName = object.GetDebugName();
            animName.ToLower();

            if (animName.Contains(animated.p3d))
            {
                string path = animated.path + animated.p3d + ".p3d";

                return CXFDestructbleData(CXFObjectType.DESTRUCTIBLE_ANIMATED, animated.impulseThreshold, path);
            }
        }

        return CXFDestructbleData(CXFObjectType.NONE, 0.0);
    }

    static CXFConfigData GetConfig()
    {
        return s_config;
    }

    static void SetObjectOverrides(array<ref CXFObjectOverride> overrides)
    {
        s_config.objectOverrides = overrides;
    }

    static void DebugSpawnDestructibleObjects()
    {
        vector startPos = "4250.0 340.0 10372.0";
        float span = 10.0;

        float rows = Math.Sqrt(s_config.destructible.Count());
        float cols = Math.Ceil(rows);

        for (int row = 0; row < rows; ++row)
        {
            float x = startPos[0] + (row * span);

            for (int col = 0; col < cols; ++col)
            {
                float z = startPos[2] + (col * span);

                CXFObjectInfo info = s_config.destructible.Get((row + col) + row * cols);

                if (!info) return;

                string p3dFullPath = info.path + info.p3d + ".p3d";
                Object created = g_Game.CreateStaticObjectUsingP3D(p3dFullPath, Vector(x, startPos[1], z), vector.Zero, 1.0, false);

                if (!created)
                {
                    Print(info.p3d);
                }
            }
        }

        startPos = Vector(4250.0 + cols * span, 340.0, 10372.0);

        rows = Math.Sqrt(s_config.destructibleAnimated.Count());
        cols = Math.Ceil(rows);

        for (int rowA = 0; rowA < rows; ++rowA)
        {
            x = startPos[0] + (rowA * span);

            for (int colA = 0; colA < cols; ++colA)
            {
                z = startPos[2] + (colA * span);

                info = s_config.destructibleAnimated.Get((rowA + colA) + rowA * cols);

                if (!info) return;

                p3dFullPath = info.path + info.p3d + ".p3d";
                created = g_Game.CreateStaticObjectUsingP3D(p3dFullPath, Vector(x, startPos[1], z), vector.Zero, 1.0, false);

                if (!created)
                {
                    Print(info.p3d);
                }
            }
        }
    }

    private static ref map<int, ref CXFDestructibleObject> s_markedObjects = new map<int, ref CXFDestructibleObject>();
    private static ref array<ref CXFDestructibleObject> s_destroyedObjects = {};
    private static ref CXFConfigData s_config = new CXFConfigData();

    private void CXFDestructionManager() {}
    private void ~CXFDestructionManager() {}
}
