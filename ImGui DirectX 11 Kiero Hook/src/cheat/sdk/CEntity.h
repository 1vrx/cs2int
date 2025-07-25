#pragma once
#include <cstdint>
#include "../../globals.h"


struct CEntity {
	
	uintptr_t CSSPlayerController{};
	uintptr_t C_CSPlayerPawn{};

	int health{};
	int shield{};

	Vec3 pos{};
	Vec3 headpos{};	//x = pitch. y = yaw. z = roll
	Vec3 angle{};	//x = pitch. y = yaw. z = roll	

	int team{};	//1 = SPEC. 2 = T. 3 = CT

	int GetHealth()
	{
		return *(int*)(C_CSPlayerPawn + o::C_CSPlayerPawn::m_iHealth);
	}
};


struct C_CSPlayerPawn {
private:
	uintptr_t base;

public:
	
	//sets address of the pawns base
	void SetBase(uintptr_t input)
	{
		base = input;
	}

	//int pawnHealth
	int GetHealth() const
	{
		return *(int*)(base + o::C_CSPlayerPawn::m_iHealth);
	}

	//bool 1 = left, 0 = right
	bool GetHandedness() const
	{
		return *(bool*)(base + o::C_CSPlayerPawn::m_bLeftHanded);
	}

	//float shouldGlow
	void Glow(float val)
	{
		*(float*)(base + o::C_CSPlayerPawn::m_pGlowServices) = val; // 100000.f = on			0.f = off
	}

	//Vec3 bonePosition
	Vec3 GetBonePos(unsigned int bone)
	{
		uintptr_t gamescene = *(uintptr_t*)(base + 0x328);
		uintptr_t bonearray = *(uintptr_t*)(gamescene + 0x170 + 0x80);

		
		return *(Vec3*)(bonearray + bone * 32);
	}

	//Vec3 pawnOrigin
	Vec3 GetOrigin()
	{
		return *(Vec3*)(base + o::C_CSPlayerPawn::m_vOrigin);
	}

	int GetTeam()
	{
		return *(int*)(base + o::C_CSPlayerPawn::m_iTeamNum);
	}

};



struct CCSPlayerController {
private:
	uintptr_t base;

public:
	void SetCCSPlayerController(uintptr_t input)
	{
		base = input;
	}

	int GetPing() const
	{
	
		int ping = *(int*)(base + o::CCSPlayerController::m_iPing);
		if (!ping)
			return 0;
		return ping;
	}

	std::string GetName() const
	{	
		uintptr_t nameaddr = *(uintptr_t*)(base + o::CCSPlayerController::m_sSanitizedPlayerName);
		if (!nameaddr)
			return "Unknown";
		
		return *(std::string*)(base + o::CCSPlayerController::m_sSanitizedPlayerName);
	}
	
};

/*
namespace util
{
	bool ingame();
}
*/