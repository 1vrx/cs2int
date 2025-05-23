#include "visuals.h"


namespace device
{
	extern float resX = GetSystemMetrics(SM_CXSCREEN);
	extern float resY = GetSystemMetrics(SM_CYSCREEN);

	const ImVec2 midPoint = { (resX / 2), (resY / 2) };
	const ImVec2 midTop = { (resX / 2), 0 };
}

namespace visual
{
	float(*ViewMatrix)[4][4] = (float(*)[4][4])(globals::modBase + o::client::dwViewMatrix);
	Vec2 screenfeet{};
	Vec2 screenhead{};

	Vec2 v2head{};
	Vec2 v2spine2{};
	Vec2 v2pelvis{};
	Vec2 v2_L_elbow{};
	Vec2 v2_L_hand{};
	Vec2 v2_R_elbow{};
	Vec2 v2_R_hand{};
	Vec2 v2_L_thigh{};
	Vec2 v2_L_foot{};
	Vec2 v2_R_thigh{};
	Vec2 v2_R_foot{};


	void PlayerESP()
	{
		for (int i = 0; i <= entlist::entcount; i++)
		{

			if (entlist::players[i].pos.x == entlist::players[0].pos.x)
				continue;
			
			if (!entlist::players[i].pos.W2S(screenfeet, ViewMatrix) && entlist::players[i].headpos.W2S(screenhead, ViewMatrix))
				continue;
			
			std::cout << "\n[BOX ESP DEBUG] feetpos (screen) = " << screenfeet.x << " / " << screenfeet.y;
			std::cout << "\n[BOX ESP DEBUG] headpos (screen) = " << screenhead.x << " / " << screenhead.y;
			screenhead.y = screenfeet.y - 67.f;
			float height = (screenfeet.y - screenhead.y) * 1.5f;
			float width = height / 2.f;
			float x = screenfeet.x - width / 2;
			ImGui::GetBackgroundDrawList()->AddRect({ screenfeet.x - width, screenhead.y - 10.f}, { (screenfeet.x - width / 2) + width, screenhead.y + height }, ImColor(255, 255, 255));
			
			std::cout << "\nboxesp_drawn";
			
			
			
		}
	}

	void NameESP()
	{
		for (int i = 0; i <= entlist::entcount; i++)
		{

			

			if (!entlist::players[i].pos.W2S(screenfeet, ViewMatrix) && entlist::players[i].headpos.W2S(screenhead, ViewMatrix))
				continue;

			std::string playername;

			playername = entlist::controller[i].GetName();


			
			ImGui::GetBackgroundDrawList()->AddText(ImVec2({ screenhead.x, screenhead.y - 10.f }), ImColor(255, 255, 255), playername.c_str());
		}
	}

	

	
	void BoneESP() 
	{
		for (int i = 0; i <= entlist::entcount; i++)
		{
			//check if localplayer - entlist::players[i].team can be done for a team check 
			if (entlist::players[i].pos.x == entlist::players[0].pos.x)
				continue;
			if (entlist::players[i].health < 0)
				continue;

			//step through to bone array
			uintptr_t entity	= *(uintptr_t*)(globals::modBase + o::client::dwEntityList + (0x10 * i));
			if (!entity)
				break;
			uintptr_t gamescene = *(uintptr_t*)(entity + 0x328);
			uintptr_t bonearray = *(uintptr_t*)(gamescene + 0x170 + 0x80);
			
			//initialize 3d co-ordinates of the bones
			Vec3 v3head			= *(Vec3*)(bonearray + 6 * 32);
			Vec3 v3spine2		= *(Vec3*)(bonearray + 3 * 32);
			Vec3 v3pelvis		= *(Vec3*)(bonearray + 0 * 32);
			Vec3 v3_L_elbow		= *(Vec3*)(bonearray + 8 * 32);
			Vec3 v3_L_hand		= *(Vec3*)(bonearray + 10 * 32);
			Vec3 v3_R_elbow		= *(Vec3*)(bonearray + 13 * 32);
			Vec3 v3_R_hand		= *(Vec3*)(bonearray + 15 * 32);
			Vec3 v3_L_thigh		= *(Vec3*)(bonearray + 22 * 32);
			Vec3 v3_L_foot		= *(Vec3*)(bonearray + 24 * 32);
			Vec3 v3_R_thigh		= *(Vec3*)(bonearray + 25 * 32);
			Vec3 v3_R_foot		= *(Vec3*)(bonearray + 27 * 32);
			
			
			//check they are in view :
			if (
				!v3head.W2S(v2head, ViewMatrix)			&&
				!v3spine2.W2S(v2spine2, ViewMatrix)		&&
				!v3pelvis.W2S(v2pelvis, ViewMatrix)		&&
				!v3_L_elbow.W2S(v2_L_elbow, ViewMatrix) &&
				!v3_L_hand.W2S(v2_L_hand, ViewMatrix)	&&
				!v3_R_elbow.W2S(v2_R_elbow, ViewMatrix) &&
				!v3_R_hand.W2S(v2_R_hand, ViewMatrix)	&&
				!v3_L_thigh.W2S(v2_L_thigh, ViewMatrix) &&
				!v3_L_foot.W2S(v2_L_foot, ViewMatrix)	&&
				!v3_R_thigh.W2S(v2_R_thigh, ViewMatrix) &&
				!v3_R_foot.W2S(v2_R_foot, ViewMatrix)
				)
				continue;

			//need to play around with this more, as the previous lines should do this for me but it wasnt running each W2S
			v3head.W2S(v2head, ViewMatrix);
			v3spine2.W2S(v2spine2, ViewMatrix);
			v3pelvis.W2S(v2pelvis, ViewMatrix);
			v3_L_elbow.W2S(v2_L_elbow, ViewMatrix);
			v3_L_hand.W2S(v2_L_hand, ViewMatrix);
			v3_R_elbow.W2S(v2_R_elbow, ViewMatrix);
			v3_R_hand.W2S(v2_R_hand, ViewMatrix);
			v3_L_thigh.W2S(v2_L_thigh, ViewMatrix);
			v3_L_foot.W2S(v2_L_foot, ViewMatrix);
			v3_R_thigh.W2S(v2_R_thigh, ViewMatrix);
			v3_R_foot.W2S(v2_R_foot, ViewMatrix);
			
			//draw the lines
			ImGui::GetBackgroundDrawList()->AddLine({ v2head.x, v2head.y }, { v2spine2.x, v2spine2.y }, ImColor(color::r_bone, color::g_bone, color::b_bone), cheatsetting::bone_thickness);	//head to spine [maybe i should do neck]
			ImGui::GetBackgroundDrawList()->AddLine({ v2spine2.x, v2spine2.y }, { v2pelvis.x, v2pelvis.y }, ImColor(color::r_bone, color::g_bone, color::b_bone), cheatsetting::bone_thickness);	//spine to pelvis
			ImGui::GetBackgroundDrawList()->AddLine({ v2spine2.x, v2spine2.y }, { v2_L_elbow.x, v2_L_elbow.y }, ImColor(color::r_bone, color::g_bone, color::b_bone), cheatsetting::bone_thickness);	//spine to left_elbow
			ImGui::GetBackgroundDrawList()->AddLine({ v2spine2.x, v2spine2.y }, { v2_R_elbow.x, v2_R_elbow.y }, ImColor(color::r_bone, color::g_bone, color::b_bone), cheatsetting::bone_thickness);	//spine to right_elbow
			ImGui::GetBackgroundDrawList()->AddLine({ v2_L_elbow.x, v2_L_elbow.y }, { v2_L_hand.x, v2_L_hand.y }, ImColor(color::r_bone, color::g_bone, color::b_bone), cheatsetting::bone_thickness);	//left elbow to left hand
			ImGui::GetBackgroundDrawList()->AddLine({ v2_R_elbow.x, v2_R_elbow.y }, { v2_R_hand.x, v2_R_hand.y }, ImColor(color::r_bone, color::g_bone, color::b_bone), cheatsetting::bone_thickness);	//right elbow to right hand
			ImGui::GetBackgroundDrawList()->AddLine({ v2pelvis.x, v2pelvis.y }, { v2_L_thigh.x, v2_L_thigh.y }, ImColor(color::r_bone, color::g_bone, color::b_bone), cheatsetting::bone_thickness);	//pelvis to left_thigh
			ImGui::GetBackgroundDrawList()->AddLine({ v2pelvis.x, v2pelvis.y }, { v2_R_thigh.x, v2_R_thigh.y }, ImColor(color::r_bone, color::g_bone, color::b_bone), cheatsetting::bone_thickness);	//pelvis to right_thigh
			ImGui::GetBackgroundDrawList()->AddLine({ v2_L_thigh.x, v2_L_thigh.y }, { v2_L_foot.x, v2_L_foot.y }, ImColor(color::r_bone, color::g_bone, color::b_bone), cheatsetting::bone_thickness);	//left_thigh to left_foot
			ImGui::GetBackgroundDrawList()->AddLine({ v2_R_thigh.x, v2_R_thigh.y }, { v2_R_foot.x, v2_R_foot.y }, ImColor(color::r_bone, color::g_bone, color::b_bone), cheatsetting::bone_thickness);	//right_thigh to right_foot
			



		}
	}

	void Tracers()
	{
		for (int i = 0; i <= entlist::entcount; i++)
		{
			//if in view, render
			if (!entlist::players[i].headpos.W2S(screenhead, ViewMatrix))
				continue;
			//if not local player, render
			if (entlist::players[i].pos.x == entlist::players[0].pos.x)
				continue;

		
			
		
			
				ImGui::GetBackgroundDrawList()->AddLine(device::midTop, {screenhead.x, screenhead.y}, ImColor(255, 255, 255));
			

			

		}
	}

	void HealthESP()
	{
		for (int i = 0; i <= entlist::entcount; i++)
		{
			if (!entlist::players[i].headpos.W2S(screenhead, ViewMatrix))
				continue;
			//if not local player, render
			if (entlist::players[i].pos.x == entlist::players[0].pos.x)
				continue;





			entlist::players[i].headpos.W2S(screenhead, ViewMatrix);
			entlist::players[i].pos.W2S(screenfeet, ViewMatrix);
			int enthp = entlist::pawn[i].GetHealth();

			


			//ImGui::GetBackgroundDrawList()->AddRectFilled({/*min X and Y VAL*/ });

		}
	}
	void Glow(bool val)
	{

		if (val == 1)
		{
			for (int i = 1; i <= entlist::entcount; i++)
			{
				entlist::pawn[i].Glow(100000.f);
			}
		}
		if (val == 0)
		{
			for (int i = 1; i <= entlist::entcount; i++)
			{
				entlist::pawn[i].Glow(0.f);
			}
		}
		
	}
}