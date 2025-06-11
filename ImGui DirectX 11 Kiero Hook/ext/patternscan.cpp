#include "patternscan.h"

inline std::vector<int> PatternToBytes(const char* pattern)
{
	std::vector<int> bytes;
	const char* current = pattern;
	while (*current) {
		if (*current == '?') {
			bytes.push_back(-1);  // Wildcard
			current++;
			if (*current == '?') current++;  // Skip second '?'
		}
		else {
			bytes.push_back(static_cast<int>(std::strtoul(current, nullptr, 16)));
			current += 2;
		}
		if (*current == ' ') current++;  // Skip spaces
	}
	return bytes;
}


inline uintptr_t PatternScan(const wchar_t* moduleName, const char* pattern)
{
	HMODULE hModule = GetModuleHandleW(moduleName);
	if (!hModule) return 0;

	std::uint8_t* moduleBase = reinterpret_cast<std::uint8_t*>(hModule);

	PIMAGE_NT_HEADERS ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(moduleBase + reinterpret_cast<PIMAGE_DOS_HEADER>(moduleBase)->e_lfanew);
	std::size_t moduleSize = ntHeaders->OptionalHeader.SizeOfImage;

	std::vector<int> patternBytes = PatternToBytes(pattern);
	std::size_t patternLength = patternBytes.size();

	for (std::size_t i = 0; i <= moduleSize - patternLength; i++) {
		bool found = true;
		for (std::size_t j = 0; j < patternLength; j++) {
			if (patternBytes[j] != -1 && patternBytes[j] != moduleBase[i + j]) {
				found = false;
				break;
			}
		}
		if (found)
			return reinterpret_cast<uintptr_t>(moduleBase + i);

	}

	return 0;
}

