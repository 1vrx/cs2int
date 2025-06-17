#include "skinchanger.h"

uintptr_t offsets::modbase = (uintptr_t)GetModuleHandleW(L"client.dll");
uintptr_t offsets::secondengine = (uintptr_t)GetModuleHandleW(L"engine2.dll");
uintptr_t offsets::eng_dwnetworkwhatever = *(uintptr_t*)(secondengine + engine::dwNetworkGameClient);

constexpr const int GetWeaponPaint(const short itemDef)
{
	switch (itemDef) {
	case 1: return 711;
	case 2: return 38;
	case 7: return cheatsetting::akID;
	case 9: return 344;
	case 61: return 653;
	default: return 0;
	}
}

const int firstskinID{};

void dotheskinchangershit()
{
	std::cout << "\n\n\n||___|| Called SkinChanger";

	uintptr_t local = *(uintptr_t*)(offsets::modbase + offsets::client::dwLocalPlayerPawn);
	if (!local)
	{
		std::cout << "\n||___|| Failed to find local player";
		return;
	}
	int localhp = *(int*)(local + 0x344);
	if (localhp <= 0)
		return;

	std::cout << "\n||___|| Debug: PlayerHP: " << localhp;

	uintptr_t curWeapon = *(uintptr_t*)(local + offsets::client::m_pClippingWeapon);
	if (!curWeapon) {
		std::cout << "\n||___|| Failed to get current weapon";
		return;
	}

	short itemDef = *(short*)(curWeapon + offsets::client::m_AttributeManager + offsets::client::m_Item + offsets::client::m_iItemDefinitionIndex);
	std::cout << "\n||___|| currently holding : " << itemDef;

	if (const auto paint = GetWeaponPaint(itemDef))
	{
		int curFB = *(int*)(curWeapon + offsets::client::m_nFallbackPaintKit);
		std::cout << "\n||___|| current fallback id : " << curFB << "\n||___|| paint: " << paint;
		const bool bChangeSkin = (*(uintptr_t*)curWeapon + offsets::client::m_nFallbackPaintKit) != paint;
		std::cout << "\n||___|| Inside SkinChanger: bSwap = " << bChangeSkin << "\n||___|| Current skin = " << *(uint32_t*)(curWeapon + offsets::client::m_nFallbackPaintKit);
		std::cout << "\n||___|| Initial SkinID: " << firstskinID;

		*(DWORD*)(curWeapon + offsets::client::m_AttributeManager + offsets::client::m_Item + offsets::client::m_iItemID) = -1;
		*(DWORD*)(curWeapon + offsets::client::m_AttributeManager + offsets::client::m_Item + offsets::client::m_iItemIDHigh) = -1;
		*(uint32_t*)(curWeapon + offsets::client::m_AttributeManager + offsets::client::m_Item + offsets::client::m_iItemIDLow) = -1;

		*(uint32_t*)(curWeapon + offsets::client::m_nFallbackPaintKit) = paint;

		*(float*)(curWeapon + offsets::client::m_flFallbackWear) = 0.01f;


		if (bChangeSkin)
		{
			std::cout << "\n||___|| Updating skin";
			uintptr_t u = *(uintptr_t*)(offsets::eng_dwnetworkwhatever + offsets::engine::dwNetworkGameClient);
			*(uintptr_t*)(u + offsets::engine::dwNetworkGameClient_deltaTick) = -1;
		}
	}

}

