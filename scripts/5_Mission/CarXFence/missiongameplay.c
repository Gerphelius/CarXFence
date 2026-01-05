modded class MissionGameplay
{
    void ~MissionGameplay()
    {
        CXFDestructionManager.ResetDestroyedObjects();
    }
}
