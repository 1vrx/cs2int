#include "entlist.h"



namespace entlist
{
	extern int entcount{};

	extern Entity players[32]{};

	
	

	extern C_CSPlayerPawn pawn[65]{};
	extern CCSPlayerController controller[65]{};
	
	// @Note: the UC method is a lot better, tmr fully convert to use it as it actually obtains my Controllers:D
	void IntIt()
	{
		int i{ 0 };

		const uintptr_t entity_list = *(uintptr_t*)(globals::modBase + o::client::dwEntityList);
		if (!entity_list)
			return;

		for (int i = 0; i < 64; i++)
		{
			uintptr_t entity = *(uintptr_t*)(globals::modBase + o::client::dwEntityList + (0x10 * i));
			if (!entity)
				break;

			pawn[i].SetBase(entity);

			/*uintptr_t controllerentry = *(uintptr_t*)(entity_list + (8 * ((i + 1) & 0x7FFF) >> 9) + 16);
			if (!controllerentry)
				break;

			const uintptr_t pcontroller = *(uintptr_t*)(controllerentry + 120 * ((i + 1) & 0x1FF));
			if (!pcontroller)
				continue;
			controller[i].SetCCSPlayerController(pcontroller);
			*/



			
			
		}
	}



	void Init()
	{

#ifdef __DEBUG
		std::cout << "\nCalledInit";
#endif
		const uintptr_t entity_list = *(uintptr_t*)(globals::modBase + o::client::dwEntityList);
		if (!entity_list)
			return;

#ifdef __DEBUG
		std::cout << "\n FoundENTLIST ";
#endif

#ifdef __DEBUG
		std::cout << "\nCalledEntlist";
#endif
		
		//commented for reminders 
		for (int i = 0; i < 64; i++) //starts from local player (0)
		{
			std::cout << "\nLoop iteration: " << i + 1;
			//C_BaseEntity
			uintptr_t entity = *(uintptr_t*)(globals::modBase + o::client::dwEntityList + (0x10 * i));
			
			if (!entity)
				break;

			pawn[i].SetBase(entity);

			//std::cout << "\nset pawn @ 0x" << std::hex << globals::relativeaddr(entity) << std::dec;
	

			/*uintptr_t controllerentry = *(uintptr_t*)(entity_list + (8 * ((i + 1) & 0x7FFF) >> 9) + 16);
			if (!controllerentry)
				break;

			const uintptr_t player = *(uintptr_t*)(controllerentry + 120 * ((i + 1) & 0x1FF));
			if (!player)
				continue;

			controller[i].SetCCSPlayerController(player);
			*/

			//std::cout << "\nSetController @: 0x" << std::hex << (player - globals::modBase) << std::dec;
			

			uintptr_t gamescene = *(uintptr_t*)(entity + 0x328);
			uintptr_t bonearray = *(uintptr_t*)(gamescene + 0x170 + 0x80);

#ifdef __DEBUG
			std::cout << "\ngot gamescene and bonearray";
#endif __DEBUG

		

			
			players[i].health = *(int*)(entity + o::C_CSPlayerPawn::m_iHealth);
			

			if (players[i].health > 100 || players[i].health <= 0)
				continue;



			players[i].headpos = *(Vec3*)(bonearray + 6 * 32);
			/*
			int ping = controller[i].GetPing();
			std::cout << "\n\nTEST:::: PING:::: " << ping;
			*/
			//Vec3 headPosition = pawn[i].GetBonePos(6);
			//std::cout << "\nGotNewHead";

			//std::cout << "\nheadpos 1 vs 2 " << headPosition.x << " " << players[i].headpos.x;

			players[i].pos = *(Vec3*)(entity + o::C_CSPlayerPawn::m_vOrigin);
			players[i].team = *(int*)(entity + o::C_CSPlayerPawn::m_iTeamNum);
			players[i].angle = *(Vec3*)(entity + o::C_CSPlayerPawn::unknown_vCam);		//unknwon_vCam is the players eye angle i believe, should work for all entites [cannot be written]
		
			//std::cout << "\n\n\nENTITY " << i + 1 << " position: X | Y | Z " << players[i].pos.x << " | " << players[i].pos.y << " | " << players[i].pos.z;
			
#ifdef __DEBUG
						std::cout << "\nENT INDEX: " << i + 1 << " " << "ENT HP: " << players[i].health << "\nEntPos: " << players[i].pos.x << " " << players[i].pos.y << " " << players[i].pos.z << " Team: " << players[i].team
							  << "\nHeadPos: " << players[i].headpos.x << " " << players[i].headpos.y << " " << players[i].headpos.z;
#endif __DEBUG
			entcount = i + 1;

			
		}
		//std::cout << "\nendofloop\n";

		

	}



}