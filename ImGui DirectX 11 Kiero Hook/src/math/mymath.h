#pragma once
#include "../includes.h"

#include <numbers>
#include <math.h>
#include <iostream>
#include <WinUser.h>


class Vec2
{
public:
	float x, y;
};



class Vec3
{
public:
	float x, y, z;

	const bool W2S(Vec2& out, float(*ViewMatrix)[4][4]);

	Vec3 operator+(Vec3& rhs) {
		Vec3 temp;
		temp.x = this->x + rhs.x;
		temp.y = this->y + rhs.y;
		temp.z = this->z + rhs.z;
		return temp;
	}
	Vec3 operator-(Vec3& rhs) {
		Vec3 temp;
		temp.x = this->x - rhs.x;
		temp.y = this->y - rhs.y;
		temp.z = this->z - rhs.z;
		return temp;
	}
	Vec3 operator*(Vec3& rhs) {
		Vec3 temp;
		temp.x = this->x * rhs.x;
		temp.y = this->y * rhs.y;
		temp.z = this->z * rhs.z;
		return temp;
	}
	Vec3 operator/(Vec3& rhs) {
		Vec3 temp;
		temp.x = this->x / rhs.x;
		temp.y = this->y / rhs.y;
		temp.z = this->z / rhs.z;
		return temp;
	}
	Vec3& operator=(const Vec3& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	//floats
	Vec3 operator+(float& rhs) {
		Vec3 temp;
		temp.x = this->x + rhs;
		temp.y = this->y + rhs;
		temp.z = this->z + rhs;;
		return temp;
	}
	Vec3 operator-(float& rhs) {
		Vec3 temp;
		temp.x = this->x - rhs;
		temp.y = this->y - rhs;
		temp.z = this->z - rhs;;
		return temp;
	}
	Vec3 operator*(float& rhs) {
		Vec3 temp;
		temp.x = this->x * rhs;
		temp.y = this->y * rhs;
		temp.z = this->z * rhs;;
		return temp;
	}
	Vec3 operator/(float& rhs) {
		Vec3 temp;
		temp.x = this->x / rhs;
		temp.y = this->y / rhs;
		temp.z = this->z / rhs;;
		return temp;
	}
	Vec3 operator=(float& rhs) {
		Vec3 temp;
		temp.x = this->x = rhs;
		temp.y = this->y = rhs;
		temp.z = this->z = rhs;;
		return temp;
	}
	
};

template <typename T>
T RadToDegree(T Radians);

float calcDist(Vec3 local, Vec3 target);

Vec3 calcAngle(Vec3 local, Vec3 target);

float vec2Dist(Vec3 vec);