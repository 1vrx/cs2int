#include "mymath.h"

template <typename T>
T RadToDegree(T Radians)
{
	return (Radians * 57.2957795131);		//57.2957795131 is 180/PI 
}


float calcDist(Vec3 local, Vec3 target)
{
	//pythagaras theorem 3d
	float dx = target.x - local.x;
	float dy = target.y - local.y;
	float dz = target.z - local.z;

	return sqrtf(dx * dx + dy * dy + dz * dz);
}

Vec3 calcAngle(Vec3 local, Vec3 target)
{
	float dx = target.x - local.x;
	float dy = target.y - local.y;
	float dz = target.z - local.z;
	float hyp = calcDist(local, target);

	Vec3 final{};
	final.x = std::atan2(-dz, std::hypot(dx, dy)) * (180.0f / std::numbers::pi_v<float>);
	final.y = std::atan2(dy, dx) * (180.0f / std::numbers::pi_v<float>);
	final.z = 0.0f;

	//ignore this for now

	//if (local.x == entlist::players[0].pos.x)
	//{
	//	std::cout << "\n[angle calculation debug]";
	//	std::cout << "\n[DELTA VALUES] dx/dy/dz " << dx << " / " << dy << " / " << dz;
	//	std::cout << "\n[DEBUG ANGLES] our initial angles - pitch/yaw/roll\n" << entlist::players[0].angle.x << " / " << entlist::players[0].angle.y << " / " << entlist::players[0].angle.z;
	//	std::cout << "\ncalculated angles in radians: pitch/yaw/roll\n" << atan2f(dy, dx) << " / " << atan2f(dz, dy) << " / " << entlist::players[0].angle.z;
	//	std::cout << "\ncalculated angles in degrees: pitch/yaw/roll\n" << RadToDegree<float>(atan2f(dy, dx)) << " / " << RadToDegree<float>(atan2f(dz, dy)) << " / " << entlist::players[0].angle.z;
	//}
	//
	return final;

	

}
const bool Vec3::W2S(Vec2& out, float(*ViewMatrix)[4][4])
{
	const float w = (*ViewMatrix)[3][0] * x + (*ViewMatrix)[3][1] * y + (*ViewMatrix)[3][2] * z + (*ViewMatrix)[3][3];

	if (w <= 0.01)
		return false;

	//inverse width
	const float invW = 1.0f / w;		

	const float screenWidth = GetSystemMetrics(SM_CXSCREEN);
	const float screenHeight = GetSystemMetrics(SM_CYSCREEN);

	out.x = (screenWidth / 2) + (((*ViewMatrix)[0][0] * x + (*ViewMatrix)[0][1] * y + (*ViewMatrix)[0][2] * z + (*ViewMatrix)[0][3]) * invW * (screenWidth / 2));
	out.y = (screenHeight / 2) - (((*ViewMatrix)[1][0] * x + (*ViewMatrix)[1][1] * y + (*ViewMatrix)[1][2] * z + (*ViewMatrix)[1][3]) * invW * (screenHeight / 2));

	return true;
}


