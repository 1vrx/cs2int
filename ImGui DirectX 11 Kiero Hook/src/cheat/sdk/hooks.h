#pragma once
#include "../../../ext/patternscan.h"
#include "../../offsets.h"
#include "../../../ext/kiero/minhook/include/MinHook.h"
#include "../../src/includes.h"
#include "../skins/skinchanger.h"

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

std::vector<std::pair<uint8_t, bool>> PatternToBytes(const std::string& pattern);
uintptr_t patternScan(const std::string& module, const std::string& pattern);

namespace hook
{


	typedef void(__fastcall* oCreateMoveFn)(int*, int, char);
	inline oCreateMoveFn oCreateMove = nullptr;

	void __fastcall hkCreateMove(int* a1, int a2, char a3);

	typedef void(__fastcall* oFSN)(void*, int);
	inline oFSN oFrameStageNotify = nullptr;

	void __fastcall hkFrameStageNotify(void* a1, int stage);

	void init();
	





}