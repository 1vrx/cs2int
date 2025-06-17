#pragma once
#pragma once
#include <Windows.h>
#include <iostream>

#include "../../globals.h"

namespace offsets
{
	extern uintptr_t modbase;
	extern uintptr_t secondengine;
	extern uintptr_t eng_dwnetworkwhatever;


	namespace client {
		//organization is my strength in this 5 minute project
		constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x18560D0;

		constexpr std::ptrdiff_t m_pWeaponServices = 0x11A8;

		constexpr std::ptrdiff_t m_pClippingWeapon = 0x13A0;

		constexpr std::ptrdiff_t m_AttributeManager = 0x1148; //econ entity

		constexpr std::ptrdiff_t m_Item = 0x50;

		constexpr std::ptrdiff_t m_iItemDefinitionIndex = 0x1BA;

		constexpr std::ptrdiff_t m_nFallbackPaintKit = 0x15F8;

		constexpr std::ptrdiff_t m_iItemID = 0x1C8;

		constexpr std::ptrdiff_t m_iItemIDHigh = 0x1D0;

		constexpr std::ptrdiff_t m_iItemIDLow = 0x1D4;

		constexpr std::ptrdiff_t m_flFallbackWear = 0x1600;

	}
	namespace engine
	{
		constexpr std::ptrdiff_t dwNetworkGameClient = 0x53FCE0;
		constexpr std::ptrdiff_t dwNetworkGameClient_deltaTick = 0x27C;
	}


}

void dotheskinchangershit();