#include "includes.h"
#include <cstdio>
#include <thread>
#include <string>

#include "cheat/entlist.h"
#include "globals.h"
#include "cheat/aim/aim.h"
#include "cheat/visuals//visuals.h"
#include "../ext/font.h"




extern "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam) { return CallNextHookEx(NULL, code, wParam, lParam); } //ong this is detected and pasted

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;



void cheat()
{
	//system("cls");
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		toggle::menu = !toggle::menu;
	}
	if (GetAsyncKeyState(VK_F1) & 1)
	{
		toggle::enabled = !toggle::enabled;
	}
	if (GetAsyncKeyState(VK_F2) & 1)
	{
		toggle::aimbot = !toggle::aimbot;
	}
	if (GetAsyncKeyState(VK_F4) & 1)
	{
		toggle::esp = !toggle::esp;
	}
	if (GetAsyncKeyState(VK_F5) & 1)
	{
		toggle::tracers = !toggle::tracers;
	}
	if (GetAsyncKeyState(VK_F6) & 1)
	{
		toggle::skeleton = !toggle::skeleton;
	}
	
	
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	
}



void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
	
	ImFontConfig font;
	font.FontDataOwnedByAtlas = false;

	io.Fonts->AddFontFromMemoryTTF((void*)frank_goth, sizeof(frank_goth), 18, &font);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}




bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	

	cheat();
	

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	
	if (toggle::menu)
	{
		ImGui::Begin("jaipurhook");

		{ ImGui::SameLine(); 
		if (ImGui::Button(("aim"), ImVec2(150, 30)))
		{
			menu::tab = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button(("visual"), ImVec2(150, 30)))
		{
			menu::tab = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button(("misc"), ImVec2(150, 30)))
		{
			menu::tab = 2;
		}
		}
		ImGui::NewLine();

		if (menu::tab == 0)
		{
			ImGui::TextColored(ImColor(255, 255, 255), "aim:");
			ImGui::Checkbox("aimbot", &toggle::aimbot);
			ImGui::Checkbox("mouse_aimbot", &toggle::maimbot);
			ImGui::SliderFloat("smoothing", &cheatsetting::aimSmooth, 0.1f, 100.f);
			ImGui::SliderFloat("fov", &cheatsetting::aimfov, 0.1f, 180.f);
			ImGui::SliderFloat("max distance to aim", &cheatsetting::aimDist, 10.f, 5000.f);
			ImGui::End();
		}
		if (menu::tab == 1)
		{
			ImGui::TextColored(ImColor(255, 255, 255), "visual:");
			ImGui::Checkbox("boneESP", &toggle::skeleton);
			ImGui::SliderInt("r_bone", &color::r_bone, 0, 255);
			ImGui::SliderInt("g_bone", &color::g_bone, 0, 255);
			ImGui::SliderInt("b_bone", &color::b_bone, 0, 255);
			ImGui::SliderFloat("bone_thickness", &cheatsetting::bone_thickness, 1.f, 25.f);
			ImGui::Checkbox("tracers", &toggle::tracers);
			ImGui::Checkbox("healthESP", &toggle::healthESP);
			ImGui::Checkbox("boxESP", &toggle::esp);
			ImGui::Checkbox("nameESP", &toggle::nameESP);
			ImGui::SliderFloat("width", &cheatsetting::fwidth, 0.f, 100.f);
			ImGui::SliderFloat("height", &cheatsetting::fheight, 0.f, 100.f);
			ImGui::End();
		}
		if (menu::tab == 2)
		{
			
			ImGui::TextColored(ImColor(255, 255, 255), "misc");
			ImGui::Checkbox("watermark", &toggle::watermark);
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::Checkbox("test", &toggle::newentlist);

			ImGui::TextColored(ImColor(255, 255, 255), "extra:");
			ImGui::Text("source: https://github.com/1vrx/cs2int");
			ImGui::End();
			
		}
		
		
	}
	
	/*
	if (toggle::menu)
	{
		ImGui::Begin("jaipurhook");


		ImGui::NewLine();


		ImGui::TextColored(ImColor(255, 255, 255), "aim:");
		ImGui::Checkbox("aimbot", &toggle::aimbot);
		ImGui::Checkbox("mouse_aimbot", &toggle::maimbot);
		ImGui::SliderFloat("smoothing", &cheatsetting::aimSmooth, 0.1f, 100.f);
		ImGui::SliderFloat("fov", &cheatsetting::aimfov, 0.1f, 180.f);
		ImGui::SliderFloat("max distance to aim", &cheatsetting::aimDist, 10.f, 5000.f);

		ImGui::TextColored(ImColor(255, 255, 255), "visual:");
		ImGui::Checkbox("boneESP", &toggle::skeleton);
		ImGui::SliderInt("r_bone", &color::r_bone, 0, 255);
		ImGui::SliderInt("g_bone", &color::g_bone, 0, 255);
		ImGui::SliderInt("b_bone", &color::b_bone, 0, 255);
		ImGui::SliderFloat("bone_thickness", &cheatsetting::bone_thickness, 1.f, 25.f);
		ImGui::Checkbox("tracers", &toggle::tracers);
		ImGui::Checkbox("healthESP", &toggle::healthESP);
		ImGui::Checkbox("boxESP", &toggle::esp);
		ImGui::Checkbox("nameESP", &toggle::nameESP);
		ImGui::SliderFloat("width", &cheatsetting::fwidth, 0.f, 100.f);
		ImGui::SliderFloat("height", &cheatsetting::fheight, 0.f, 100.f);

		ImGui::TextColored(ImColor(255, 255, 255), "misc");
		ImGui::Checkbox("watermark", &toggle::watermark);
		ImGui::NewLine();
		ImGui::NewLine();
		ImGui::Checkbox("test", &toggle::newentlist);

		ImGui::TextColored(ImColor(255, 255, 255), "extra:");
		ImGui::Text("source: https://github.com/1vrx/cs2int");



		ImGui::End();
	}
	*/
	if (toggle::enabled)
	{
		entlist::Init();
	}
	if (toggle::aimbot)
	{
		if (GetAsyncKeyState(VK_RBUTTON))
			aim::Aimbot();
	}
	
	if (toggle::maimbot)
	{
		ImGui::GetBackgroundDrawList()->AddCircle({ 960, 540 }, cheatsetting::aimfov / 2, ImColor(255, 255, 255));
		if (GetAsyncKeyState(VK_RBUTTON))
			aim::mouse_aimbot();
	}
	
	if (toggle::esp)
	{
		visual::PlayerESP();
	}
	if (toggle::tracers)
	{
		visual::Tracers();
	}
	if (toggle::skeleton)
	{
		visual::BoneESP();
	}
	if (toggle::healthESP)
	{
		visual::HealthESP();
	}
	if (toggle::newentlist)
	{
		entlist::IntIt();
	}
	if (toggle::watermark)
	{
		ImGui::GetBackgroundDrawList()->AddText({ 29, 21 }, ImColor(0, 0, 0), "JAiPURhook");			//shadow
		ImGui::GetBackgroundDrawList()->AddText({ 30, 20 }, ImColor(255, 255, 255), "JAiPURhook");		//main text
	}
	if (toggle::nameESP)
	{
		visual::NameESP();
	}
	
	

	

	
	
	

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	


	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	SetConsoleTitle("debug window");


	std::cout << "[ :: ] cheat loaded\n" <<
		"[ :: ] located base 0x" << std::hex << globals::modBase << "\nPress F1 to initialize the entity list [required for cheat to work]" << 
		"\n[ + ] NameESP (dont use in single player)\n[ + ] Added BoneESP customization\n[ - ] Broke Aimbot\n[ * ] Ready to start adding tabs to menu";

	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}