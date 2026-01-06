class CXFDestructibleObject
{
    void CXFDestructibleObject(notnull Object obj)
    {
        m_objectLink = new OLinkT(obj);
        m_flags = obj.GetFlags();
        m_events = obj.GetEventMask();
        //m_interactionLayer = dBodyGetInteractionLayer(obj);
        obj.GetTransform(m_transform);

        //obj.SetScale(0.000001);
        //obj.ClearFlags(m_flags, true);
        obj.ClearEventMask(m_events);
        obj.SetEventMask(EntityEvent.NOTVISIBLE);
        obj.Update();

#ifndef SERVER
        dBodyActive(obj, ActiveState.INACTIVE);
        dBodySetSolid(obj, false);
#endif

#ifdef SERVER
        dBodyDestroy(obj);
#endif
        /*
        * 	Not working for some objects on map (like wall_cbrk_5 located on <12998.141602, 6.768738, 10050.177734>).
        *	It applies layers to similar objects nearby instead of single selected object.
        *	Without this function call, car wheels interact with objects like if it still has collision.
        */
        // dBodySetInteractionLayer(obj, 0);
    }

    void ~CXFDestructibleObject()
    {
#ifndef SERVER
        Object obj = GetObject();

        obj.SetFlags(m_flags, true);
        obj.SetEventMask(m_events);
        obj.SetTransform(m_transform);
        obj.Update();


        dBodyActive(obj, ActiveState.ACTIVE);
        dBodySetSolid(obj, true);
        //dBodySetInteractionLayer(obj, m_interactionLayer);
#endif
    }

    Object GetObject()
    {
        return m_objectLink.Ptr();
    }

    private ref OLinkT m_objectLink = null;
    private int m_flags = 0;
    private int m_events = 0;
    private int m_interactionLayer = 0;
    private vector m_transform[4] = {};
}

class CXFDestructionManager : Managed
{
    static void Init()
    {
        CXFConfig.Load();
        s_config = CXFConfig.Get();
    }

    static void MarkForDestroy(notnull Object obj, vector contactPos, vector contactDir, CXFObjectType type)
    {
        if (g_Game.IsDedicatedServer())
        {
            int objId = obj.GetID();

            if (!s_markedObjects.Contains(objId))
            {
                s_markedObjects[objId] = new CXFMarkedObject(obj, contactPos, contactDir, !!type);
            }
        }
    }

    static void DestroyMarkedObjects()
    {
        if (g_Game.IsDedicatedServer())
        {
            ScriptRPC rpc = new ScriptRPC();

            rpc.Write(s_markedObjects.Count());

            foreach(CXFMarkedObject markedObj : s_markedObjects)
            {
                Object obj = markedObj.GetObject();

                rpc.Write(obj);
                rpc.Write(markedObj.GetContactPos());
                rpc.Write(markedObj.GetContactDir());
                rpc.Write(markedObj.IsAnimated());
                s_destroyedObjects.Insert(new CXFDestructibleObject(obj));
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
            }

            rpc.Send(null, CXFRPC.OBJECT_DESTROYED, true, identity);
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

    static CXFDestructbleData GetDestructibleData(Object object)
    {
        if (object.IsTree())
        {
            // TODO: add impulse config variable for trees
            return CXFDestructbleData(CXFObjectType.DESTRUCTIBLE_ANIMATED, 2000.0);
        }

        foreach(CXFObjectInfo destructible : s_config.destructible)
        {
            string destrName = object.GetDebugName();
            destrName.ToLower();

            if (destrName.Contains(destructible.p3dName))
            {
                return CXFDestructbleData(CXFObjectType.DESTRUCTIBLE, destructible.impulseThreshold);
            }
        }

        foreach(CXFObjectInfo animated : s_config.destructibleAnimated)
        {
            string animName = object.GetDebugName();
            animName.ToLower();

            if (animName.Contains(animated.p3dName))
            {
                return CXFDestructbleData(CXFObjectType.DESTRUCTIBLE_ANIMATED, animated.impulseThreshold);
            }
        }

        return CXFDestructbleData(CXFObjectType.NONE, 0.0);
    }

    static CXFConfigData GetConfig()
    {
        return s_config;
    }

    private static ref map<int, ref CXFMarkedObject> s_markedObjects = new map<int, ref CXFMarkedObject>();
    private static ref array<ref CXFDestructibleObject> s_destroyedObjects = {};
    private static ref CXFConfigData s_config = null;

    private void CXFDestructionManager() {}
    private void ~CXFDestructionManager() {}
}
