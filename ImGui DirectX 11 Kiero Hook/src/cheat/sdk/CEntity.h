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
	
	void SetBase(uintptr_t input)
	{
		base = input;
	}

	int GetHealth() const
	{
		return *(int*)(base + o::C_CSPlayerPawn::m_iHealth);
	}

	bool GetHandedness() const
	{
		return *(bool*)(base + o::C_CSPlayerPawn::m_bLeftHanded);
	}

	void Glow(float val)
	{
		*(float*)(base + o::C_CSPlayerPawn::m_pGlowServices) = val; // 100000.f = on			0.f = off
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
		return *(int*)(base + o::CCSPlayerController::m_iPing);
	}
	
};
