#pragma once


#include "../includes.h"
#include "../globals.h"
#include "../offsets.h"
#include "sdk/CEntity.h"

namespace entlist
{
	extern Entity players[32];

	extern int entcount;

	extern C_CSPlayerPawn pawn[65];
	extern CCSPlayerController controller[65];
	void IntIt();
	void Init();

}
