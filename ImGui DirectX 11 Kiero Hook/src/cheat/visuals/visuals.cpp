#include "visuals.h"


namespace visual
{
	float(*ViewMatrix)[4][4] = (float(*)[4][4])(globals::modBase + o::client::dwViewMatrix);
	Vec2 screenfeet{};
	Vec2 screenhead{};

	void PlayerESP()
	{
		for (int i = 0; i <= entlist::entcount; i++)
		{
			
			if (!entlist::players[i].pos.W2S(screenfeet, ViewMatrix) && entlist::players[i].headpos.W2S(screenhead, ViewMatrix))
				continue;
			
			std::cout << "\n[DEBUG] feetpos (screen) = x/y " << screenfeet.x << " / " << screenfeet.y;
			std::cout << "\n[DEBUG] headpos (screen) = x/y " << screenhead.x << " / " << screenhead.y;
			
			float height = (screenfeet.y - screenhead.y) * 1.5f;
			float width = height / 1.5f;
			ImGui::GetBackgroundDrawList()->AddRect({ screenfeet.x - width / 2, screenhead.y }, { (screenfeet.x - width / 2) + width, screenhead.y + height }, ImColor(255, 255, 255));
			std::cout << "ESP Should be drawn";
			
			
			
		}
	}
	
	void BoneESP() 
	{
		
		
	}
}