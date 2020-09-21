//File to provide to users with the library
#ifndef PACKET_H
#define PACKET_H

#include <windows.h>

#ifdef PSO2PARSER_EXPORTS
#define HOOK_API __declspec(dllexport)
#else
#define HOOK_API __declspec(dllimport)
#endif

#ifdef __MINGW32__
#define ATTRPACK __attribute__((packed, ms_struct))
#else
#define ATTRPACK
#endif

#ifdef _MSC_VER
#define PACKED( __Declaration__ )\
	__pragma( pack(push, 1) ) \
	__Declaration__ \
	__pragma( pack(pop) )
#else
#define PACKED(x) x
#endif

#ifdef __cplusplus
#define EXT extern "C"
#else
#define EXT
#endif

#ifdef __cplusplus
namespace PSO2Hook
{
	//Useful if the plugin is in C++, but not necessary by any means
	PACKED(
	struct PacketHeader
		{
			UINT32 size;
			BYTE type;
			BYTE subtype;
			BYTE flags;
			BYTE padding; //Possibly also flag
		} ATTRPACK;
	)

	class HOOK_API Packet
	{
		public:
			Packet(PacketHeader *h);
			Packet(LPBYTE *packet);
			Packet *ref; //Change this when allocating for a new packet
			PacketHeader *header;
			USHORT pktID; //The unique type + subtype combination
			UINT32 dataSize; //Size of the data section without the header
			LPBYTE data;
			~Packet();
	};
#endif
	typedef void(*pktHandler)(PSO2Hook::Packet* ref, PSO2Hook::PacketHeader* header, USHORT packetId, UINT32 dataSize, LPBYTE data); //Pass by value is intentional to avoid plugins from interfering with each other

	EXT HOOK_API BOOL pso2hRegisterHandlerRecv(pktHandler func, BYTE type, BYTE subtype, LPCSTR comment);
	EXT HOOK_API BOOL pso2hRegisterHandlerSend(pktHandler func, BYTE type, BYTE subtype, LPCSTR comment);

	EXT HOOK_API LPVOID pso2hAlloc(DWORD size);
	EXT HOOK_API VOID pso2hFree(LPVOID obj);
	EXT HOOK_API size_t pso2hGetConfig(const char* key, char *buffer, size_t bufferlen); //Returns required length (including null term) if buffer is too small, otherwise 0 (logs errors). Different Plugin Configurations are isolated from each other.
	EXT HOOK_API VOID pso2hLogLine(const char* fmt, ...);
#ifdef __cplusplus
}
#endif

#endif
