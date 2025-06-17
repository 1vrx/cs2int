#pragma once
#include "globals.h"	
//#include "../ext/patternscan.h"


namespace o
{
	namespace client
	{
		constexpr int dumped_entityList = 0x1A020A8;
		constexpr int dwLocalPlayer		= 0x18560D0;		//ptr to C_CSPlayerPawn 0x3F0
		constexpr int dwLocalPlayerController = 0x1A50AD0;
		constexpr int dwEntityList		= 0x1863B80;		//localtion of entlist 10bytes between each ent	1858C10 client.dll+1858C10	1859B90
		constexpr int dwViewAngles		= 0x1A75620;		//this is eye angle, camera is different - silent aim soon  //OLD : 0x1A6A210
		constexpr int dwViewMatrix		= 0x1A6B230;		//float[4][4]		0x1A89070
	}
	namespace C_CSPlayerPawn		//Parent: C_BasePlayerPawn 
	{
		constexpr int m_iHealth			= 0x344;
		constexpr int m_iMaxHealth		= 0x340;
		constexpr int m_vOrigin			= 0x1324;	//0x1324
		constexpr int unknown_vCam		= 0x1438;
		constexpr int unknown_vCam2		= 0x124C;
		constexpr int m_iTeamNum		= 0x3E3;
		constexpr int m_hPlayerPawn		= 0x824;
		constexpr int m_bLeftHanded		= 0x22C1;
		constexpr int m_pGlowServices	= 0x1530;
		constexpr int m_ArmorValue		= 0x241C;

		//flags
		constexpr int m_bIsScoped		= 0x23E8;
		constexpr int m_bIsDefusing = 0x23EA;
		
		constexpr int m_pCameraServices = 0x11E0;
		constexpr int m_pViewModelServices = 0x1368;
	}
	namespace CCSPlayerController
	{
		constexpr int m_iPing			= 0x740;
		constexpr int m_sSanitizedPlayerName = 0x778;			// @vrx: CE [client.dll + dwLocalPlayerController] + m_sSanitzedPlayerName = YourName //:D gotta do 4 all ents [Crashing]
	}
	namespace CameraServices
	{
		constexpr int m_iFOV = 0x210;
	}
	namespace all
	{
		constexpr int m_hPlayerPawn		= 0x824;
	}
	namespace Signatures
	{
		const std::string EntityList = "48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1";
		const std::string LocalPlayerController = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 4F";
		const std::string ViewAngles = "48 8B 0D ?? ?? ?? ?? 48 8B 01 48 FF 60 30";
		const std::string ViewMatrix = "48 8D 0D ?? ?? ?? ?? 48 C1 E0 06";
		const std::string LocalPlayerPawn = "48 8D 05 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC 48 83 EC ?? 8B 0D";
	}
}

