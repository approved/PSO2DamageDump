#include "pch.h"
#include <windows.h>
#include <fstream>
#include <time.h>
#include "dllmain.h"
#include <codecvt>

#include "..\PSO2HBinaries\packet.h"
#include "gamedata.h"

namespace PSO2DamageDump
{    
    std::wofstream Main::OutputStream;
    
    extern "C" BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD  ul_reason_for_call, LPVOID /*lpReserved*/)
    {
        switch (ul_reason_for_call)
        {
            case DLL_PROCESS_ATTACH:
                CreateThread(NULL, 0, setupDamageDump, NULL, 0, NULL);
                break;
            case DLL_THREAD_ATTACH:
                break;
            case DLL_THREAD_DETACH:
                break;
            case DLL_PROCESS_DETACH:
                Main::OutputStream.flush();
                Main::OutputStream.close();
                break;
        }
        return TRUE;
    }

    static DWORD WINAPI setupDamageDump(LPVOID /*param*/)
    {
        PSO2Hook::pso2hLogLine("Setting up Damage Dump");
        time_t timestamp = time(NULL);

        char docspath[MAX_PATH];
        char filename[MAX_PATH];

        size_t length = PSO2Hook::pso2hGetConfig("directory", NULL, 0);
        if (length && length < sizeof(docspath))
        {
            PSO2Hook::pso2hGetConfig("directory", docspath, sizeof(docspath));
        }
        else
        {
            sprintf_s(docspath, "./%s", OUTPUT_DIR);
        }

        PSO2Hook::pso2hLogLine("Docs Path: %s", docspath);

        CreateDirectoryA(docspath, NULL);
        sprintf_s(filename, "%s/%lli.csv", docspath, timestamp);

        Main::OutputStream.imbue(std::locale(Main::OutputStream.getloc(), new std::codecvt_utf8<wchar_t>));
        Main::OutputStream.open(filename, std::fstream::out);

        if (!Main::OutputStream.is_open())
        {
            return 1;
        }

        std::ios_base::sync_with_stdio(false);

        const char *csvHeader = "timestamp, instanceID, sourceID, sourceName, targetID, targetName, attackID, damage, IsJA, IsCrit, IsMultiHit, IsMisc, IsMisc2";
        PSO2Hook::pso2hLogLine("Writing CSV Header: %s", csvHeader);
        Main::OutputStream << csvHeader << std::endl;

        /* Register handlers for recieved packets */
        PSO2Hook::pso2hRegisterHandlerRecv(&GameData::getDamage,           0x04, 0x52, "Get damage linked to IDs");
        PSO2Hook::pso2hRegisterHandlerRecv(&GameData::getNames,            0x08, 0x04, "Get names to assign to IDs");
        PSO2Hook::pso2hRegisterHandlerRecv(&GameData::getNames2,           0x08, 0x0D, "Get enemy names to assign to IDs");
        PSO2Hook::pso2hRegisterHandlerRecv(&GameData::getPetInfo,          0x08, 0x11, "Get Pet ID to map to owner");
        PSO2Hook::pso2hRegisterHandlerRecv(&GameData::getUserInfo,         0x0F, 0x0D, "Get current player ID");
        PSO2Hook::pso2hRegisterHandlerRecv(&GameData::getUserActionInfo,   0x04, 0x15, "Get user action info (for turret mounting)");
        PSO2Hook::pso2hRegisterHandlerRecv(&GameData::getObjectInfo,       0x08, 0x10, "Get object ID to map to owner");

        // Sleep to prevent unloading the .dll
        while (true)
        {
            Sleep(1000);
        }

        return 0;
    }
}