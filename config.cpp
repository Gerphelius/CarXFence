class CfgPatches
{
    class CarXFence
    {
        requiredAddons[] =
        {
            "DZ_Data",
            "DZ_Scripts"
        };
    };
};

class CfgMods
{
    class CarXFence
    {
        author = "Gerphelius";
        credits = "Gerphelius";
        type = "mod";

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] =
                {
                    "CarXFence/scripts/3_Game",
                    "CarXFence/scripts/Gerphelius"
                };
            };
            class worldScriptModule
            {
                value = "";
                files[] =
                {
                    "CarXFence/scripts/4_World"
                };
            };
            class missionScriptModule
            {
                value = "";
                files[] =
                {
                    "CarXFence/scripts/5_Mission"
                };
            };
        };
    };
};
