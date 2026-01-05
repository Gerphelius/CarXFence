modded class CarScript
{
    override void OnContact(string zoneName, vector localPos, IEntity other, Contact data)
    {
        CXFDestructionManager.MarkForDestroy(Object.Cast(other));

        super.OnContact(zoneName, localPos, other, data);
    }

    override void CheckContactCache()
    {
        CXFDestructionManager.DestroyMarkedObjects();

        super.CheckContactCache();
    }
}
