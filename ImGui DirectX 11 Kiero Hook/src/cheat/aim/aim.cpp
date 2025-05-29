#include "aim.h"

namespace aim
{

	float(*ViewMatrix)[4][4] = (float(*)[4][4])(globals::modBase + o::client::dwViewMatrix);
	


	Entity GetNearest()
	{
		//temp val to compare dist;
		float old_dist = 99999;
		//new entity to send 

		Entity eNearest;
		eNearest.pos = { 100.f, 100.f, 100.f };


		//loop till closest player
		for (int i = 1; i <= entlist::entcount; i++)
		{
#ifdef _DEBUG
			std::cout << "\n\ninitializing loop to find nearest ent: here are the coords: \n" << entlist::players[i].headpos.x << " | " << entlist::players[i].headpos.y << " | " << entlist::players[i].headpos.z << "\n";
#endif _DEBUG
			float entdist = calcDist(entlist::players[0].headpos, entlist::players[i].headpos);
			
			if (entlist::players[i].headpos.x == 0.f && entlist::players[i].headpos.y == 0.f && entlist::players[i].headpos.z == 0.f)
				continue;

			if (entlist::players[i].headpos.x == 100.f && entlist::players[i].headpos.y == 100.f && entlist::players[i].headpos.z == 100.f)
				continue;

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
						continue;
					/* {
						old_dist = old_dist;
						eNearest = eNearest;
					}*/
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
		std::cout << "\ncalled aimbot";

		Vec3 raw_angles{};
		Vec3 angle_to_aim{};
		Vec3 old_angles{};

		std::cout << "\nlookign for nearest ent";

		//for now the target will be the nearest entity.
		Entity target = GetNearest();
		if (target.health <= 0)
			return;

		std::cout << "\ngot nearest ent";

		//float desiredfov = cheatsetting::aimfov;

		//calculating the angle (in degrees) between me and the opponent
		raw_angles = calcAngle(entlist::players[0].headpos, target.headpos);

#ifdef _DEBUG
		std::cout << "[aimbot] raw_angles xyz: " << raw_angles.x << " " << raw_angles.y;
#endif _DEBUG

		//normalize angles to ensure the yaw and pitch to not exceed their possible values [prevent vaclive]
		angle_to_aim = normalize(raw_angles);

#ifdef _DEBUG
		std::cout << "[aimbot] nor_angles xyz: " << angle_to_aim.x << " " << angle_to_aim.y;


		std::cout << "\nNearest Ent Coords: " << target.headpos.x << " | " << target.headpos.y << " | " << target.headpos.z << " Dist: " << calcDist(entlist::players[0].headpos, target.headpos);
		std::cout << "\naiming @: " << entlist::players[0].angle.x << " " << entlist::players[0].angle.y;
		std::cout << "\nshould be aiming @: " << angle_to_aim.x << " " << angle_to_aim.y;
#endif _DEBUG
		//commenting this out because im using a hold to aim currently so not needed.

		old_angles = *(Vec3*)(globals::modBase + o::client::dwViewAngles);
		
		if (calcDist(entlist::players[0].headpos, target.pos) > cheatsetting::aimDist)
			return;
		

		/*
		const auto curfov = std::hypot(angle_to_aim.x, angle_to_aim.y);

		
		if (curfov < desiredfov)
		{
			desiredfov = curfov;
			angle_to_aim = angle_to_aim;
		}
		if (curfov > desiredfov)
		{
			return;
		}
		*/
		
		

		//auto delta = (angle_to_aim - old_angles);

		//auto final = (angle_to_aim + delta);

		//*(Vec3*)(globals::modBase + o::client::dwViewAngles) = angle_to_aim;
		*(Vec3*)(globals::modBase + o::client::dwViewAngles) = angle_to_aim; // cheatsetting::aimSmooth;

#ifdef _DEBUG
		std::cout << "\naimbot - end";
#endif _DEBUG

	}

	void mouse_aimbot()
	{
		Entity target = GetNearest();
		if (target.health <= 0)
			return;

		Vec2 v2_screen;

		target.headpos.W2S(v2_screen, ViewMatrix);

		if (calcDist(entlist::players[0].headpos, target.pos) > cheatsetting::aimDist)
			return;
		
		//mouse_event(MOUSEEVENTF_MOVE, v2_screen.x, v2_screen.y, 0, 0);

		
	}


}









