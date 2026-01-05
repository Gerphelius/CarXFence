modded class DayZGame
{
    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        if (rpc_type == 48151623)
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

                    CXFDestructionManager.DestroyObjectOnClient(obj);
                }
            }
        }

        super.OnRPC(sender, target, rpc_type, ctx);
    }
}
