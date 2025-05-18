#include "entlist.h"



namespace entlist
{
	extern int entcount{};

	extern Entity players[32]{};

	
	

	C_CSPlayerPawn pawn[65];
	CCSPlayerController controller[65];
	
	// @Note: the UC method is a lot better, tmr fully convert to use it as it actually obtains my Controllers:D
	void IntIt()
	{
		
		std::cout << "\ninitializing IntIt func";

		const uintptr_t entity_list = *(uintptr_t*)(globals::modBase + o::client::dwEntityList);
		if (!entity_list)
			return;

		std::cout << "\nentity list obtained: " << entity_list;

		int pIndex = 0;

		std::cout << "\nstarting loop";
		
		for (pIndex = 0; pIndex < 64; pIndex++)
		{
			std::cout << "\n\n\nfinding entity entry " << pIndex + 1;
			uintptr_t entity = *(uintptr_t*)(globals::modBase + o::client::dwEntityList + (0x10 * pIndex));
		
			if (!entity)
				break;
			pawn[pIndex].SetBase(entity);

			std::cout << "\nFoundEntity @ " << std::hex << entity << std::dec;

			int ehp = pawn[pIndex].GetHealth();
			std::cout << "\nent " << pIndex + 1 << " " << ehp;

			bool lefthand = pawn[pIndex].GetHandedness();
			std::cout << "\nthe entity hand is [1 = left, 0 = right] " << lefthand;

			uintptr_t controllerentry = *(uintptr_t*)(entity_list + (8 * ((pIndex + 1) & 0x7FFF) >> 9) + 16);
			if (!controllerentry)
				break;

			const uintptr_t player = *(uintptr_t*)(controllerentry + 120 * ((pIndex + 1) & 0x1FF));
			if (!player)
				continue;

			/*const uint32_t playerpawn = *(uint32_t*)(player + o::C_CSPlayerPawn::m_hPlayerPawn);
			if (!playerpawn)
				continue;

			const uintptr_t entry2 = *(uintptr_t*)(entity_list + 0x8 * ((playerpawn & 0x7FFF) >> 9) + 16);
			if (!entry2)
				continue;

			const uintptr_t cspawn = *(uintptr_t*)(entry2 + 120 * (playerpawn & 0x1FF));
			if (!cspawn)
				continue;
				*/

			std::cout << "\nGH method was successful";

			/*const uintptr_t CCSPlayerController = *(uintptr_t*)(entity + 120 * ((pIndex + 1) & 0x1FF));
			if (!CCSPlayerController)
				continue;
			*/

			controller[pIndex].SetCCSPlayerController(player);
			std::cout << "\nFoundController";

			int eping = controller[pIndex].GetPing();		//crashing... maybe because my CCSPlayerController isnt really CCSPlayerController
			std::cout << "ent " << pIndex + 1 << " ping: " << eping;


			

			std::hex;
			//std::cout << "\nCCSPlayerController: " << CCSPlayerController << " " << &CCSPlayerController;
			std::cout << "\nC_CSPlayerPawn: " << entity << " " << &entity;
			std::cout << "\nGH Conroller: " << player << " " << &player;
			//std::cout << "\nCSPawnNEW: " << cspawn << " " << &cspawn;
			std::dec;
			

			std::cout << "\nend of loop iteration:	" << pIndex + 1;

		}
		std::cout << "\nUnable to find entity " << pIndex + 1 << " returning";
		
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
		

		for (int i = 0; i < 64; i++) //starts from local player (0)
		{
			std::cout << "\nLoop iteration: " << i + 1;
			//C_BaseEntity
			uintptr_t entity = *(uintptr_t*)(globals::modBase + o::client::dwEntityList + (0x10 * i));
			
			if (!entity)
				break;

			pawn[i].SetBase(entity);

			std::cout << "\nset pawn";

			uintptr_t controllerentry = *(uintptr_t*)(entity_list + (8 * ((i + 1) & 0x7FFF) >> 9) + 16);
			if (!controllerentry)
				break;

			const uintptr_t player = *(uintptr_t*)(controllerentry + 120 * ((i + 1) & 0x1FF));
			if (!player)
				continue;

			controller[i].SetCCSPlayerController(player);

			std::cout << "\nSetController";
			

			uintptr_t gamescene = *(uintptr_t*)(entity + 0x328);
			uintptr_t bonearray = *(uintptr_t*)(gamescene + 0x170 + 0x80);
			std::cout << "\ngot gamescene and bonearray";

		

			
			players[i].health = *(int*)(entity + o::C_CSPlayerPawn::m_iHealth);
			

			if (players[i].health > 100 || players[i].health <= 0)
				continue;



			players[i].headpos = *(Vec3*)(bonearray + 6 * 32);

			
			//Vec3 headPosition = pawn[i].GetBonePos(6);
			//std::cout << "\nGotNewHead";

			//std::cout << "\nheadpos 1 vs 2 " << headPosition.x << " " << players[i].headpos.x;

			players[i].pos = *(Vec3*)(entity + o::C_CSPlayerPawn::m_vOrigin);
			players[i].team = *(int*)(entity + o::C_CSPlayerPawn::m_iTeamNum);
			players[i].angle = *(Vec3*)(entity + o::C_CSPlayerPawn::unknown_vCam);		//unknwon_vCam is the players eye angle i believe, should work for all entites [cannot be written]
		
			//std::cout << "\n\n\nENTITY " << i + 1 << " position: X | Y | Z " << players[i].pos.x << " | " << players[i].pos.y << " | " << players[i].pos.z;
			

						std::cout << "\nENT INDEX: " << i + 1 << " " << "ENT HP: " << players[i].health << "\nEntPos: " << players[i].pos.x << " " << players[i].pos.y << " " << players[i].pos.z << " Team: " << players[i].team
							  << "\nHeadPos: " << players[i].headpos.x << " " << players[i].headpos.y << " " << players[i].headpos.z;
			entcount = i + 1;

			
		}
		//std::cout << "\nendofloop\n";

		

	}



}