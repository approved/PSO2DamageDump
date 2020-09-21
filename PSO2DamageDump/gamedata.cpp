#include "pch.h"
#include "gamedata.h"
#include "packetdef.h"
#include "utility.h"
#include <Windows.h>
#include <unordered_map>
#include <locale>
#include <codecvt>
#include <fstream>
#include "dllmain.h"

#include "defs/packet.h"

namespace PSO2DamageDump
{
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;

	std::unordered_map<DWORD, std::wstring> GameData::PlayerNames;
	std::unordered_map<DWORD, DWORD> GameData::PetOwner;
	UINT32 GameData::SelfID;

	void GameData::getDamage(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* /*header*/, USHORT packetId, UINT32 dataSize, LPBYTE data)
	{
		PacketDamage info = *(PacketDamage*)data;

		if (GameData::PetOwner.count(info.sourceID))
		{
			info.sourceID = GameData::PetOwner[info.sourceID];
		}

		if (GameData::PetOwner.count(info.targetID))
		{
			info.targetID = GameData::PetOwner[info.targetID];
		}

		std::wstring sourceName, targetName;
		if (GameData::PlayerNames.count(info.sourceID))
		{
			sourceName = GameData::PlayerNames[info.sourceID];
		}
		else
		{
			sourceName = std::wstring(L"Unknown");
		}

		if (GameData::PlayerNames.count(info.targetID))
		{
			targetName = GameData::PlayerNames[info.targetID];
		}
		else
		{
			targetName = std::wstring(L"Unknown");
		}

		Main::OutputStream <<
			time(NULL) << "," << 
			info.instanceID << "," << 
			info.sourceID << "," << 
			sourceName << "," << 
			info.targetID << "," << 
			targetName << "," << 
			info.atkID << "," << 
			info.value << "," << 
			CheckDamageFlag(info.flags, DF_JA) << "," << 
			CheckDamageFlag(info.flags, DF_CRIT) << "," << 
			CheckDamageFlag(info.flags, DF_MH) << "," << 
			CheckDamageFlag(info.flags, DF_MISC) << "," << 
			CheckDamageFlag(info.flags, DF_MISC2) << std::endl;

		ref->~Packet();
	}

	void GameData::getNames(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* /*header*/, USHORT packetId, UINT32 dataSize, LPBYTE data)
	{
		PacketCharacterInfo info = *(PacketCharacterInfo*)data;
		GameData::PlayerNames[info.playerID] = std::wstring(info.name);
		GameData::PetOwner.erase(info.playerID);
		strReplace(GameData::PlayerNames[info.playerID], L",", L"comma");
		strReplace(GameData::PlayerNames[info.playerID], L"|", L"pipe");
		ref->~Packet();
	}

	void GameData::getNames2(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* /*header*/, USHORT packetId, UINT32 dataSize, LPBYTE data)
	{
		PacketSpawnInfo info = *(PacketSpawnInfo*)data;
		GameData::PlayerNames[info.ID] = Converter.from_bytes(info.name);
		GameData::PetOwner.erase(info.ID);
		strReplace(GameData::PlayerNames[info.ID], L",", L"comma");
		strReplace(GameData::PlayerNames[info.ID], L"|", L"pipe");
		ref->~Packet();
	}

	void GameData::getPetInfo(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* /*header*/, USHORT packetId, UINT32 dataSize, LPBYTE data)
	{
		PacketPetSpawn info = *(PacketPetSpawn*)data;
		GameData::PetOwner[info.petID] = info.ownerID;
		ref->~Packet();
	}

	void GameData::getUserInfo(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* /*header*/, USHORT packetId, UINT32 dataSize, LPBYTE data)
	{
		PacketUserInfo info = *(PacketUserInfo*)data;
		if (GameData::SelfID != info.playerID)
		{
			GameData::SelfID = info.playerID;
			Main::OutputStream <<
				time(0) << "," << 
				0 << "," << 
				info.playerID << "," << 
				L"YOU" << "," << 
				0 << "," << 
				0 << "," << 
				0 << "," << 
				0 << "," << 
				0 << "," << 
				0 << "," << 
				0 << "," << 
				0 << "," << 
				0 << std::endl;
		}
		ref->~Packet();
	}

	void GameData::getUserActionInfo(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* /*header*/, USHORT packetId, UINT32 dataSize, LPBYTE data)
	{
		PacketPlayerAction info = *(PacketPlayerAction*)data;
		if (!std::string(info.action).compare("SitSuccess") && info.objID && info.userID)
		{
			GameData::PetOwner[info.objID] = info.userID;
		}
		ref->~Packet();
	}

	void GameData::getObjectInfo(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* /*header*/, USHORT packetId, UINT32 dataSize, LPBYTE data)
	{
		PacketVehicleSpawn info = *(PacketVehicleSpawn*)data;
		GameData::PetOwner[info.objID] = info.ownerID;
		ref->~Packet();
	}
}
