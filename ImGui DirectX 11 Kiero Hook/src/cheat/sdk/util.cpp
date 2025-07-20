
#include "util.h"
#include <cstdint>
#include "../../globals.h"

namespace util
{
	bool ingame()
	{
		uintptr_t netclient = *(uintptr_t*)(globals::engine + 0x53FCE0); //dwNetworkGameClient
		if (!netclient) return 0;

		int curstate = *(int*)(netclient + 0x228); //dwNetworkGameClient_signOnState

		if (curstate == 6)
			return true;

		return false;
	}
}