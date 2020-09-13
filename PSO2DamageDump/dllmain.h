#pragma once
#ifndef DllMain_Header
#define DllMain_Header

#define OUTPUT_DIR "damagelogs"

namespace PSO2DamageDump
{
	#define CheckDamageFlag(x, y) ((x & y) != 0)

	extern "C" BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
	static DWORD WINAPI setupDamageDump(LPVOID param);

	class Main
	{
		public:
			static std::wofstream OutputStream;
	};
}
#endif