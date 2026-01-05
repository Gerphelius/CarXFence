modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
    }

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);

        CXFDestructionManager.SyncDestroyedObjectsOnClient(identity);
    }
}
