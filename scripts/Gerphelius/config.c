class CXFConfigData
{
    float noCarDamageBelowImpulse = 1000.0;
    float maxCarDamageAboveImpulse = 5000.0;
    bool treeDestruction = true;
    ref array<ref CXFObjectInfo> destructible = {};
    ref array<ref CXFObjectInfo> destructibleAnimated = {};
    ref array<ref CXFNoDestructionArea> noDestructionAreas = {};
    ref array<ref CXFObjectOverride> objectOverrides = {};
}

class CXFConfig
{
    private static const string root = "$profile:\\Gerphelius\\";
    private static const string configName = "carxfence_config.json";
    private static const int version = 1; // TODO: create versioning logic

    private static ref CXFConfigData s_cxfConfig = CXFConfigData();
    private static ref CXFConfigData s_cxfConfigDefault = CXFConfigData();

    static void Load()
    {
        if (FileExist(root + "\\" + configName))
        {
            JsonFileLoader<CXFConfigData>.JsonLoadFile(root + configName, s_cxfConfig);

            return;
        }

        Save();
    }

    static void Save()
    {
        if (!FileExist(root))
        {
            MakeDirectory(root);
        }

        FillDefaultConfig();
        JsonFileLoader<CXFConfigData>.JsonSaveFile(root + "\\" + configName, s_cxfConfigDefault);
    }

    static CXFConfigData Get()
    {
        return s_cxfConfig;
    }

    private static void FillDefaultConfig()
    {
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_haybale", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_pallet", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_tire", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_doghouse", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_chickencoop", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("garbage_bin", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_bench", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_boogieman", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_chair", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_haystack", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_noticeboard", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_postbox", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_sunshade", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_table", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_windbreak", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_woodblock", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_woodpile", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_woodtable", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("cemetery_smallcross", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("cemetery_tombstone", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("garbage_pile", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("canister_dz", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_woodencrate", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("slum_roof", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("forest_beetletrap", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("forest_deerskeleton", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_crabcages", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_fishinggear", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("mil_camonet", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_gunrack", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_range", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("garbage_container", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("stretcher", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("patient_monitor", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("hospital_transport_bed", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("pillow", 2000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("wall_stone", 10000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_boundaryStone", 10000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_boxwooden", 10000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_feedrack", 10000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_tree_protector", 10000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_woodreserve", 10000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("wall_barricade", 10000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("mil_guardshed", 10000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_range_roof", 10000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("airfield_light_papi", 10000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("airfield_light_edge", 10000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("airfield_light_reflector", 10000.0));
        s_cxfConfigDefault.destructible.Insert(new CXFObjectInfo("misc_razorwire", 10000.0));

        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("misc_obstacle", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("sign_", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("trailmap_", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("citymap_", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("trail_woodenpole", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_tin", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_tincom", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_vilvar", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_wood", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_gate_fen", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_gate_ind", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_gate_tin", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_backalley", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_fen4", 4000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_fen", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_indfnc", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_pipefence", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_polewall", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_railing", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_gate_village", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_gate_wood", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_forfieldfen", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("cemetery_fence", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("power_pole_conc", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("power_pole_wood5", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("power_pole_wood", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("misc_crashbarrier", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("misc_roadbarrier", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("misc_trafficlights", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("lamp_decorative", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("lamp_halogen", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("lamp_harbour", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("lamp_stadium", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("lamp_", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_gate_indcnc", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_indcnc", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_pipefencewall", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("airfield_light_navig", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_cbrk", 2000.0));
        s_cxfConfigDefault.destructibleAnimated.Insert(new CXFObjectInfo("wall_indvar", 2000.0));

        s_cxfConfigDefault.objectOverrides.Insert(new CXFObjectOverride("wall_gate_ind1_l", "front", "0.0 0.0 1.15"));
        s_cxfConfigDefault.objectOverrides.Insert(new CXFObjectOverride("sign_", "impact", "0.0 0.0 0.0"));
        s_cxfConfigDefault.objectOverrides.Insert(new CXFObjectOverride("wall_railing", "aside", "0.0 0.0 0.0"));

        //s_cxfConfigDefault.noDestructionAreas.Insert(new CXFNoDestructionArea("13177.0 6.0 6904.0", 30.0));
    }
}
