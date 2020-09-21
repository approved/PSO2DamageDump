#pragma once
#include "defs\packet.h"
#include <unordered_map>

namespace PSO2DamageDump
{
	class GameData
	{
		public:
			static std::unordered_map<DWORD, std::wstring> PlayerNames;
			static std::unordered_map<DWORD, DWORD> PetOwner;
			static UINT32 SelfID;

			static void getDamage(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* header, USHORT packetId, UINT32 dataSize, LPBYTE data);
			static void getNames(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* header, USHORT packetId, UINT32 dataSize, LPBYTE data);
			static void getNames2(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* header, USHORT packetId, UINT32 dataSize, LPBYTE data);
			static void getPetInfo(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* header, USHORT packetId, UINT32 dataSize, LPBYTE data);
			static void getUserInfo(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* header, USHORT packetId, UINT32 dataSize, LPBYTE data);
			static void getUserActionInfo(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* header, USHORT packetId, UINT32 dataSize, LPBYTE data);
			static void getObjectInfo(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* header, USHORT packetId, UINT32 dataSize, LPBYTE data);
	};

	enum DamageFlags
	{
		DF_JA		= 0x1,	//Just Attack
		DF_UNK		= 0x2,	//Unknown
		DF_MISC		= 0x4,	//Healing, lava, etc.. all use this
		DF_DMG		= 0x8,	//Damage
		DF_MH		= 0x10,	//Multi-hit, probably. One Point and Infinite Fire have this set
		DF_MISC2	= 0x20, //Zanverse uses this
		DF_CRIT		= 0x40	//Critical Strike
	};
}