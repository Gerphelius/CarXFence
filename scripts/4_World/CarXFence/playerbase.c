modded class PlayerBase
{
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        if (rpc_type == CXFRPC.OVERRIDES_LOAD)
        {
            Param1<int> count;
            ctx.Read(count);

            array<ref CXFObjectOverride> overrides = {};

            for (int i = 0; i < count.param1; ++i)
            {
                Param3<string, string, vector> param;
                ctx.Read(param);

                overrides.Insert(new CXFObjectOverride(param.param1, param.param2, param.param3));
            }

            CXFDestructionManager.SetObjectOverrides(overrides);
        }

        super.OnRPC(sender, rpc_type, ctx);
    }
}
