#include "entlist.h"



namespace entlist
{
	extern int entcount{};

	extern Entity players[32]{};



	void Init()
	{

		std::cout << "\nCalled INIT";
		for (int i = 0; i < 64; i++) //starts from local player (0)
		{

			uintptr_t entity = *(uintptr_t*)(globals::modBase + o::client::dwEntityList + (0x10 * i));


			
			if (!entity)
				break;

			uintptr_t gamescene = *(uintptr_t*)(entity + 0x328);
			uintptr_t bonearray = *(uintptr_t*)(gamescene + 0x170 + 0x80);




			
			players[i].health = *(int*)(entity + o::C_CSPlayerPawn::m_iHealth);

			if (players[i].health > 100 || players[i].health <= 0)
				continue;



			players[i].headpos = *(Vec3*)(bonearray + 6 * 32);

			
			players[i].pos = *(Vec3*)(entity + o::C_CSPlayerPawn::m_vOrigin);
			players[i].team = *(int*)(entity + o::C_CSPlayerPawn::m_iTeamNum);
			players[i].angle = *(Vec3*)(entity + o::C_CSPlayerPawn::unknown_vCam);		//unknwon_vCam is the players eye angle i believe, should work for all entites [cannot be written]
			players[i].pos.z += 65.f;

			//			std::cout << "\nENT INDEX: " << i << " " << "ENT HP: " << players[i].health << "\nEntPos: " << players[i].pos.x << " " << players[i].pos.y << " " << players[i].pos.z << " Team: " << players[i].team
			//				  << "\nHeadPos: " << players[i].headpos.x << " " << players[i].headpos.y << " " << players[i].headpos.z;
			entcount = i + 1;

			
		}
		//std::cout << "\nendofloop\n";

		

	}



}