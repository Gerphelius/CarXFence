modded class CarScript
{
    override void OnContact(string zoneName, vector localPos, IEntity other, Contact data)
    {
        super.OnContact(zoneName, localPos, other, data);

        if (g_Game.IsDedicatedServer())
        {
            Object object = Object.Cast(other);
            CXFDestructbleData destrData = CXFDestructionManager.GetDestructibleData(object);

            if (destrData.m_type != CXFObjectType.NONE && data.Impulse >= destrData.m_impulse)
            {
                CXFDestructionManager.MarkForDestroy(object, data.Position, GetSpeed().Normalized(), destrData.m_type);

                if (!m_ContactCache.Contains(zoneName)) return;

                CXFConfigData config = CXFDestructionManager.GetConfig();
                ref CarContactData contactData = m_ContactCache[zoneName][0];
                float impulseMultiplier = Math.Remap(config.noCarDamageBelowImpulse, config.maxCarDamageAboveImpulse, 0.0, 1.0, destrData.m_impulse);
                contactData.impulse = contactData.impulse * impulseMultiplier;
            }
        }
    }

    override void CheckContactCache()
    {
        super.CheckContactCache();

        CXFDestructionManager.DestroyMarkedObjects();
    }
    /*
    proto native SurfaceInfo WheelGetSurface( int wheelIdx );

    */
}
