modded class DayZGame
{
#ifndef SERVER
    private ref array<ref CXFAnimatedObject> m_animObjects = {};

    override void OnUpdate(bool doSim, float timeslice)
    {
        super.OnUpdate(doSim, timeslice);

        array<ref CXFAnimatedObject> animObjects = {};

        foreach(CXFAnimatedObject animObj : m_animObjects)
        {
            bool animationEnded = animObj.Animate(timeslice);

            if (!animationEnded)
            {
                animObjects.Insert(animObj);
            }
        }

        m_animObjects = animObjects;
    }

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        if (rpc_type == CXFRPC.OBJECT_DESTROYED)
        {
            if (!g_Game.IsDedicatedServer())
            {
                int objectsNum = 0;
                ctx.Read(objectsNum);

                for (int i = 0; i < objectsNum; ++i)
                {
                    Object obj = null;
                    ctx.Read(obj);

                    if (!obj) continue;

                    vector contactPos = vector.Zero;
                    ctx.Read(contactPos);
                    vector contactDir = vector.Zero;
                    ctx.Read(contactDir);
                    string p3dFullPath = "";
                    ctx.Read(p3dFullPath);

                    if (p3dFullPath.Length())
                    {
                        CXFConfigData config = CXFDestructionManager.GetConfig();
                        string objName = obj.GetDebugNameNative();
                        objName.ToLower();

                        CXFObjectOverride foundOverride = null;

                        foreach(CXFObjectOverride objOverride : config.objectOverrides)
                        {
                            if (objName.Contains(objOverride.p3d))
                            {
                                foundOverride = objOverride;

                                break;
                            }
                        }

                        Object dummyObj = g_Game.CreateStaticObjectUsingP3D(p3dFullPath, obj.GetPosition(), vector.Zero, 1.0, true);
                        vector objTransform[4] = {};
                        obj.GetTransform(objTransform);
                        dummyObj.SetTransform(objTransform);
                        dBodyDestroy(dummyObj);
                        m_animObjects.Insert(new CXFAnimatedObject(dummyObj, contactDir, foundOverride));

                        /*if (obj.IsBuilding())
                        {
                            Building gate = Building.Cast(obj);
                            string type = gate.GetType();
                            type.ToLower();

                            if (type.Contains("_gate"))
                            {
                                gate.LockDoor(0, true);
                            }
                        }*/
                    }

                    CXFDestructionManager.DestroyObjectOnClient(obj, contactPos, contactDir, p3dFullPath);
                }
            }
        }

        super.OnRPC(sender, target, rpc_type, ctx);
    }
#endif
}
