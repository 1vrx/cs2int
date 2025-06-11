#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>

#include <iostream>
#include <regex>


inline std::vector<int> PatternToBytes(const char* pattern);
inline uintptr_t PatternScan(const wchar_t* moduleName, const char* pattern);