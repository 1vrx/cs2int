#pragma once
#include "../../../ext/patternscan.h"
#include "../../offsets.h"
#include "../../../ext/kiero/minhook/include/MinHook.h"
#include "../../src/includes.h"

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <span>
#include <sstream>

#include <Psapi.h>
#include <algorithm>
#include <string_view>
#include <cstdint>
#include <functional>
#include <string>


namespace hook
{


	typedef void(__fastcall* oCreateMoveFn)(int*, int, char);
	inline oCreateMoveFn oCreateMove = nullptr;

	void __fastcall hkCreateMove(int* a1, int a2, char a3);


	void init();
	





}