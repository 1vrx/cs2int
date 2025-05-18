#pragma once

#include "includes.h"
#include "math/mymath.h"
#include "offsets.h"

namespace globals
{
	const uintptr_t modBase = (uintptr_t)GetModuleHandleW(L"client.dll");
	//const uintptr_t* LocalPlayer = (uintptr_t*)(modBase + o::client::dwLocalPlayer);	//currently causing LNK2005 issue... 
	const Vec3 dwViewAngles = *(Vec3*)(modBase + o::client::dwViewAngles);
}

namespace toggle
{
	extern bool enabled;
	extern bool menu;
	extern bool aimbot;
	extern bool esp;
	extern bool tracers;
	extern bool skeleton;
	extern bool healthESP;
	extern bool maimbot;
	extern bool glow;

	extern bool newentlist;
	extern bool watermark;
	


}

namespace cheatsetting
{
	extern float smoothing;
	extern float renderDist;
	extern float aimDist;
	extern float aimSmooth;



	extern float fwidth;
	extern float fheight;

	extern float aimfov;

	extern float bone_thickness;
	
}

namespace color
{


	extern int r_bone;
	extern int g_bone;
	extern int b_bone;
}






class Entity
{

public:

	uintptr_t CCSPlayerController{};
	uintptr_t C_CSPlayerPawn{};

	int health{};
	int shield{};

	Vec3 pos{};
	Vec3 headpos{};	//x = pitch. y = yaw. z = roll
	Vec3 angle{};	//x = pitch. y = yaw. z = roll	

	int team{};	//1 = SPEC. 2 = T. 3 = CT


};



