#include "misc.h"

namespace world
{

	uintptr_t lp = *(uintptr_t*)(globals::modBase + o::client::dwLocalPlayer);
	

	void Indicators() 
	{

		unsigned const int lphp = *(int*)(lp + o::C_CSPlayerPawn::m_iHealth);
		unsigned const int lpkv = *(int*)(lp + o::C_CSPlayerPawn::m_ArmorValue);

		if (lphp > 0 && lpkv > 0)
		{
			//background box
			ImGui::GetBackgroundDrawList()->AddRectFilled({ 18, 500 }, { 222, 512 }, ImColor(0, 0, 0));		/// (MIN X, MIN Y) (MAX X, MAX Y) (COLOR) 

			/*  || the box for health is 200 pixels long, 2px for 1point of health ||  */
			ImGui::GetBackgroundDrawList()->AddRectFilled({ 20, 502 }, { 20 + ((float)lphp * 2), 510 }, ImColor(100, 255, 100));

			///KEVLAR
			ImGui::GetBackgroundDrawList()->AddRectFilled({ 18, 520 }, { 222, 532 }, ImColor(0, 0, 0));

			ImGui::GetBackgroundDrawList()->AddRectFilled({ 20, 522 }, { 20 + ((float)lpkv * 2), 530 }, ImColor(0, 134, 255));

		}
		if (lphp > 0)
		{
			///HEALTH
			//background box
			ImGui::GetBackgroundDrawList()->AddRectFilled({ 18, 500 }, { 222, 512 }, ImColor(0, 0, 0));			/// (MIN X, MIN Y) (MAX X, MAX Y) (COLOR) 

			/*  || the box for health is 200 pixels long, 2px for 1point of health ||  */
			ImGui::GetBackgroundDrawList()->AddRectFilled({ 20, 502 }, { 20 + ((float)lphp * 2), 510 }, ImColor(0, 255, 0));
		}
		else
		{
			ImGui::GetBackgroundDrawList()->AddRectFilled({ 18, 500 }, { 222, 512 }, ImColor(0, 0, 0));		/// (MIN X, MIN Y) (MAX X, MAX Y) (COLOR) 
			ImGui::GetBackgroundDrawList()->AddRectFilled({ 18, 520 }, { 222, 532 }, ImColor(0, 0, 0));
		}

	}

	void changeFOV()
	{
		//uintptr_t lp = *(uintptr_t*)(globals::modBase + o::client::dwLocalPlayer);
		if (!lp)
			return;

		uintptr_t camserv = *(uintptr_t*)(lp + o::C_CSPlayerPawn::m_pCameraServices);
		if (!camserv)
			return;

		int curfov = *(int*)(camserv + o::CameraServices::m_iFOV);
		if (curfov == cheatsetting::fov)
			return;

		bool scoped = *(bool*)(lp + o::C_CSPlayerPawn::m_bIsScoped);
		if (scoped)
			return;

		*(int*)(camserv + 0x210) = cheatsetting::fov;

	}
	void drawVel()
	{
		if (!lp)
			return;
		/*
		||-------------------------------------||

		pseudo:

		get current velo
		store last tick velo
		store last 200 vals
		draw a point representing the velo
		should be velgraph


		||-------------------------------------||
		*/

		
	}
}