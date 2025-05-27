#include "misc.h"

namespace world
{
	void Indicators() 
	{
		uintptr_t lp = *(uintptr_t*)(globals::modBase + o::client::dwLocalPlayer);
		unsigned int lphp = *(int*)(lp + o::C_CSPlayerPawn::m_iHealth);
		unsigned int lpkv = *(int*)(lp + o::C_CSPlayerPawn::m_ArmorValue);

		if (lphp > 0 && lpkv > 0)
		{
			//background box
			ImGui::GetForegroundDrawList()->AddRectFilled({ 18, 500 }, { 222, 512 }, ImColor(0, 0, 0));		/// (MIN X, MIN Y) (MAX X, MAX Y) (COLOR) 

			/*  || the box for health is 200 pixels long, 2px for 1point of health ||  */
			ImGui::GetForegroundDrawList()->AddRectFilled({ 20, 502 }, { 20 + ((float)lphp * 2), 510 }, ImColor(100, 255, 100));

			///KEVLAR
			ImGui::GetForegroundDrawList()->AddRectFilled({ 18, 520 }, { 222, 532 }, ImColor(0, 0, 0));

			ImGui::GetForegroundDrawList()->AddRectFilled({ 20, 522 }, { 20 + ((float)lpkv * 2), 530 }, ImColor(0, 134, 255));

		}
		if (lphp > 0)
		{
			///HEALTH
			//background box
			ImGui::GetForegroundDrawList()->AddRectFilled({ 18, 500 }, { 222, 512 }, ImColor(0, 0, 0));			/// (MIN X, MIN Y) (MAX X, MAX Y) (COLOR) 

			/*  || the box for health is 200 pixels long, 2px for 1point of health ||  */
			ImGui::GetForegroundDrawList()->AddRectFilled({ 20, 502 }, { 20 + ((float)lphp * 2), 510 }, ImColor(0, 255, 0));
		}
		else
		{
			ImGui::GetForegroundDrawList()->AddRectFilled({ 18, 500 }, { 222, 512 }, ImColor(0, 0, 0));		/// (MIN X, MIN Y) (MAX X, MAX Y) (COLOR) 
			ImGui::GetForegroundDrawList()->AddRectFilled({ 18, 520 }, { 222, 532 }, ImColor(0, 0, 0));
		}

	}
}