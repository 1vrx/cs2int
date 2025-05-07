#pragma once
#include "globals.h"	


namespace o
{
	namespace client
	{
		constexpr int dwLocalPlayer		= 0x1874040;		//ptr to C_CSPlayerPawn
		constexpr int dwLocalPlayerController = 0x1A6E900;
		constexpr int dwEntityList		= 0x1881350;		//localtion of entlist 10bytes between each ent
		constexpr int dwViewAngles		= 0x1A93300;		//this is eye angle, camera is different - silent aim soon
		constexpr int dwViewMatrix		= 0x1A89070;		//float[4][4]		0x1A89070
	}
	namespace C_CSPlayerPawn		//C_BasePlayerPawn offsets work here as its a parent, same with C_BasePlay
	{
		constexpr int m_iHealth			= 0x344;
		constexpr int m_iMaxHealth		= 0x340;
		constexpr int m_vOrigin			= 0x1324;
		constexpr int unknown_vCam		=  0x1438;
		constexpr int unknown_vCam2		= 0x124C;
		constexpr int m_iTeamNum		= 0x3E3;
		constexpr int m_hPlayerPawn		= 0x814;
		constexpr int m_bLeftHanded		= 0x22C1;
		constexpr int m_pGlowServices	= 0x1530;
	}
	namespace CCSPlayerController
	{
		constexpr int m_iPing			= 0x740;
	}
	namespace all
	{
		constexpr int m_hPlayerPawn		= 0x80C;
	}
}
