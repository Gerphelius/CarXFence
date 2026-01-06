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

        CXFDestructionManager.SyncDestroyedObjectsOnClient(identity);
    }
}
