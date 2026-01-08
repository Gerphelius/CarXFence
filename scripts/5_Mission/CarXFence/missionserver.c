modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();

        CXFDestructionManager.Init();
    }

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);

        CXFConfigData config = CXFDestructionManager.GetConfig();

        if (config)
        {
            array<ref Param> params = {};
            params.Insert(new Param1<int>(config.objectOverrides.Count()));

            foreach(CXFObjectOverride objOverride : config.objectOverrides)
            {
                params.Insert(new Param3<string, string, vector>(objOverride.p3d, objOverride.direction, objOverride.originOffset));
            }

            player.RPC(CXFRPC.OVERRIDES_LOAD, params, false, identity);
        }

        CXFDestructionManager.SyncDestroyedObjectsOnClient(identity);
    }
}
