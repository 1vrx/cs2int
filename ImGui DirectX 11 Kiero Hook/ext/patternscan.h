#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>

#include <iostream>
#include <regex>

HANDLE g_process_handle;

auto get_module(const char* modName, DWORD proc_id) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, proc_id);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do {
				if (!strcmp(modEntry.szModule, modName)) {
					CloseHandle(hSnap);
					return modEntry;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	return MODULEENTRY32();
}

template<typename T> T RPM(SIZE_T address) {
	T buffer; ReadProcessMemory(g_process_handle, (void*)address, &buffer, sizeof(T), nullptr);
	return buffer;
}

void str_replace_all(std::string& subject, const std::string& search, const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

//now accepts ida-style, single and double question marks, lower case and uppercase
uintptr_t find_pattern(const MODULEENTRY32& module, const std::string& str, std::string ida, int offset, int extra, bool relative = true) {
	ida.insert(0, " ");
	std::transform(ida.begin(), ida.end(), ida.begin(), tolower);
	str_replace_all(ida, " ??", " ?");
	str_replace_all(ida, " ?", " ??");
	str_replace_all(ida, " ", "");

	std::string pattern;

	for (unsigned int i = 0; i < ida.size(); i += 2) {
		std::string word = ida.substr(i, 2);
		if (word == "??") pattern += ".";
		else pattern += (char)strtol(word.c_str(), NULL, 16);
	}

	uintptr_t address;
	std::smatch sm;
	std::regex_search(str, sm, std::regex(pattern));

	if (sm.size() == 0) return 0x0;
	else address = sm.position(0);

	address += (uintptr_t)module.modBaseAddr + offset;
	address = RPM<uint32_t>(address) + extra;
	return relative ? address - (uintptr_t)module.modBaseAddr : address;
}

int main() {
	auto hwnd = FindWindow(NULL, "Counter-Strike: Global Offensive");
	DWORD proc_id; GetWindowThreadProcessId(hwnd, &proc_id);
	g_process_handle = OpenProcess(PROCESS_VM_READ, false, proc_id);
	auto client = get_module("client_panorama.dll", proc_id);

	std::string bytes(client.modBaseSize, ' ');
	ReadProcessMemory(g_process_handle, (void*)client.modBaseAddr, (void*)bytes.data(), client.modBaseSize, nullptr);

	printf("dwEntityList: 0x%X\n", find_pattern(client, bytes, "BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8", 0x1, 0x0));
	printf("dwViewMatrix: 0x%X\n", find_pattern(client, bytes, "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9", 0x3, 0xB0));

	bytes.~basic_string();
	system("pause");
}