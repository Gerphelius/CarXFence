class CXFDestructibleObject
{
    void CXFDestructibleObject(notnull Object obj)
    {
        m_objectLink = new OLinkT(obj);
        m_flags = obj.GetFlags();
        m_events = obj.GetEventMask();
        obj.GetTransform(m_transform);

        obj.SetScale(0.000001);
        obj.ClearFlags(m_flags, true);
        obj.ClearEventMask(m_events);
        obj.SetEventMask(EntityEvent.NOTVISIBLE);
        obj.Update();

        dBodyActive(obj, ActiveState.INACTIVE);
        dBodySetSolid(obj, false);
    }

    void ~CXFDestructibleObject()
    {
        Object obj = GetObject();

        obj.SetFlags(m_flags, true);
        obj.SetEventMask(m_events);
        obj.SetTransform(m_transform);
        obj.Update();

        dBodyActive(obj, ActiveState.ACTIVE);
        dBodySetSolid(obj, true);
    }

    Object GetObject()
    {
        return m_objectLink.Ptr();
    }

    private ref OLinkT m_objectLink = null;
    private int m_flags = 0;
    private int m_events = 0;
    private vector m_transform[4] = {};
}

class CXFDestructionManager : Managed
{
    static void Init()
    {

    }

    static void MarkForDestroy(notnull Object obj)
    {
        if (g_Game.IsDedicatedServer())
        {
            string objName = obj.GetDebugNameNative();
            int objId = obj.GetID();
            objName.ToLower();

            if (objName.Contains("wall_") && !s_markedObjects.Contains(objId))
            {
                s_markedObjects[objId] = obj;
            }
        }
    }

    static void DestroyMarkedObjects()
    {
        if (g_Game.IsDedicatedServer())
        {
            ScriptRPC rpc = new ScriptRPC();

            rpc.Write(s_markedObjects.Count());

            foreach(Object obj : s_markedObjects)
            {
                rpc.Write(obj);
                s_destroyedObjects.Insert(new CXFDestructibleObject(obj));
            }

            rpc.Send(null, 48151623, true, null);
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
            }

            rpc.Send(null, 48151623, true, identity);
        }
    }

    static void DestroyObjectOnClient(notnull Object obj)
    {
        if (!g_Game.IsDedicatedServer())
        {
            s_destroyedObjects.Insert(new CXFDestructibleObject(obj));
        }
    }

    static void ResetDestroyedObjects()
    {
        s_destroyedObjects.Clear();
    }

    private static ref map<int, Object> s_markedObjects = new map<int, Object>();
    private static ref array<ref CXFDestructibleObject> s_destroyedObjects = {};

    private void CXFDestructionManager() {}
    private void ~CXFDestructionManager() {}
}
