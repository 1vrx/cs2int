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
};

template <typename T>
T RadToDegree(T Radians);

float calcDist(Vec3 local, Vec3 target);

Vec3 calcAngle(Vec3 local, Vec3 target);
