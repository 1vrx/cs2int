#include "aim.h"

namespace aim
{
	Entity GetNearest()
	{
		//temp val to compare dist;
		float old_dist = 99999;
		//new entity to send 

		Entity eNearest;
		eNearest.pos = { 100, 100, 100 };


		//loop till closest player
		for (int i = 1; i <= entlist::entcount; i++)
		{

			float entdist = calcDist(entlist::players[0].headpos, entlist::players[i].headpos);

			if (entlist::players[i].team != entlist::players[0].team)
			{
				if (entlist::players[i].health > 0)
				{
					if (entdist < old_dist)
					{
						eNearest.headpos = entlist::players[i].headpos;
						old_dist = entdist;
					}
					else
					{
						old_dist = old_dist;
						eNearest = eNearest;
					}
				}
				else
					continue;

			}
			else
				continue;



		}


		//return the nearest ent from loop.
		return eNearest;




	}

	Vec3 normalize(Vec3 angles)
	{
		if (angles.y > 180.f)
			angles.y -= 180.f;
		if (angles.y < -180.f)
			angles.y += 180.f;

		if (angles.x > 90.f)
			angles.x -= 90.f;
		if (angles.x < -90.f)
			angles.x += 90.f;

		return angles;
	}




	void Aimbot()
	{


		Vec3 raw_angles{};
		Vec3 angle_to_aim{};
		Vec3 old_angles{};


		//for now the target will be the nearest entity.
		Entity target = GetNearest();
		if (target.health < 0)
			return;

		//calculating the angle (in degrees) between me and the opponent
		raw_angles = calcAngle(entlist::players[0].headpos, target.headpos);

		std::cout << "[aimbot] raw_angles xyz: " << raw_angles.x << " " << raw_angles.y;

		//normalize angles to ensure the yaw and pitch to not exceed their possible values [prevent vaclive]
		angle_to_aim = normalize(raw_angles);

		std::cout << "[aimbot] nor_angles xyz: " << angle_to_aim.x << " " << angle_to_aim.y;


		std::cout << "\nNearest Ent Coords: " << target.pos.x << " | " << target.pos.y << " | " << target.pos.z << " Dist: " << calcDist(entlist::players[0].pos, target.pos);
		std::cout << "\naiming @: " << entlist::players[0].angle.x << " " << entlist::players[0].angle.y;
		std::cout << "\nshould be aiming @: " << angle_to_aim.x << " " << angle_to_aim.y;

		//commenting this out because im using a hold to aim currently so not needed.
		/*
		if (calcDist(entlist::players[0].headpos, target.pos) > 2000)
			return;
		*/

		//can play around with this to make silent aim 
		old_angles = *(Vec3*)(globals::modBase + o::client::dwViewAngles);		//read old angles and store them temp

		


		*(Vec3*)(globals::modBase + o::client::dwViewAngles) = angle_to_aim;

		//shoot function here to make ragebot 

		//*(Vec3*)(*globals::LocalPlayer + o::C_CSPlayerPawn::unknown_vCam) = old_angles;
		//*(Vec3*)(*globals::LocalPlayer + o::C_CSPlayerPawn::unknown_vCam2) = old_angles;


		std::cout << "\naimbot - end";


	}
}









