#include "globals.h"

namespace globals
{
	template <typename T>
	uintptr_t relativeaddr(T addr)
	{
		return ((uintptr_t)addr - globals::modBase);
	}
}

namespace toggle
{
	bool enabled = false;
	bool menu = false;
	bool aimbot = false;
	bool esp = false;
	bool tracers = false;
	bool skeleton = false;
	bool healthESP = false;
	bool maimbot = false;
	bool glow = false;
	bool nameESP = false;

	bool newentlist = false;
	bool watermark = false;

	bool indicators = false;
	bool fovchanger = false;

	bool hooks = false;
	
	
}

namespace menu
{
	int tab = 0;
}

namespace cheatsetting
{
	float smoothing = 15.0f;
	float renderDist = 1000.f;
	float aimDist = 1000.f;
	float aimSmooth = 1.f;


	float fwidth = 0.f;
	float fheight = 0.f;

	float aimfov = 0.f;


	float bone_thickness = 1.f;

	int fov = 60;
}

namespace color
{


	int r_bone = 255.f;
	int g_bone = 255.f;
	int b_bone = 255.f;
}

namespace draw
{

}