class CXFConfigData
{
    float noCarDamageBelowImpulse = 1000.0;
    float maxCarDamageAboveImpulse = 5000.0;
    bool treeDestruction = true;
    ref array<ref CXFObjectInfo> destructible = {};
    ref array<ref CXFObjectInfo> destructibleAnimated = {};
    ref array<ref CXFObjectOverride> objectOverrides = {};
    ref array<ref CXFNoDestructionArea> noDestructionAreas = {};
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


        //s_cxfConfigDefault.noDestructionAreas.Insert(new CXFNoDestructionArea("13177.0 6.0 6904.0", 30.0));
    }
}
