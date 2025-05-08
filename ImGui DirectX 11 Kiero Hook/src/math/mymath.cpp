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

	const float midX = screenWidth / 2;
	const float midY = screenHeight / 2;

	//std::cout << "\n\nScreen Width / Height: " << screenWidth << " / " << screenHeight;	//returning 1920 x 1080

	out.x = midX + (((*ViewMatrix)[0][0] * x + (*ViewMatrix)[0][1] * y + (*ViewMatrix)[0][2] * z + (*ViewMatrix)[0][3]) / w * midX);
	out.y = midY - (((*ViewMatrix)[1][0] * x + (*ViewMatrix)[1][1] * y + (*ViewMatrix)[1][2] * z + (*ViewMatrix)[1][3]) / w * midY);

	return true;
}


float vec2Dist(Vec3 vec)
{
	return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}
