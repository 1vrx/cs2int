#pragma once
#include "../../../ext/patternscan.h"
#include "../../offsets.h"
#include "../../../ext/kiero/minhook/include/MinHook.h"


namespace hook
{


	typedef void(__fastcall* oCreateMoveFn)(int*, int, char);
	inline oCreateMoveFn oCreateMove = nullptr;

	void __fastcall hkCreateMove(int* a1, int a2, char a3);


	void init();
	





}