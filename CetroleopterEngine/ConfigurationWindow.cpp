#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "ModuleSceneIntro.h"
#include "ConfigurationWindow.h"
#include "glew/include/GL/glew.h"

ConfigurationWindow::ConfigurationWindow(const char* name, bool isActive) : ImGuiWindowBase("Settings", isActive = true)
{
	fps = 0;
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	checkFullscreen = WIN_FULLSCREEN;
	checkResizable = WIN_RESIZABLE;
	checkBorderless = WIN_BORDERLESS;
	checkFullDesktop = WIN_FULLSCREEN_DESKTOP;
	checkVsync = VSYNC;
	
}

ConfigurationWindow::~ConfigurationWindow()
{
}


bool ConfigurationWindow::Draw(ImGuiIO& io)
{
	bool ret = true;

	
	ImGui::Begin(GetName(), nullptr, ImGuiWindowFlags_None);

	if (App->moduleUi->hoveringWindow == false)
		App->moduleUi->hoveringWindow = ImGui::IsWindowHovered(); // To know if the window is being moved
	
	WindowHeader();
	FPSHeader();
	AnotherHeader();	
	HardwareHeader();

	ImGui::End();

	return ret;
}

bool ConfigurationWindow::CleanUp()
{
	bool ret = true;

	return ret;
}



bool ConfigurationWindow::WindowHeader()
{
	bool ret = true;

	if (ImGui::CollapsingHeader("Window Settings"))
	{
		brightness = App->window->GetBrightness();
		if (ImGui::SliderFloat("Brightness", &brightness, 0.000f, 1.000f))
		{
			App->window->SetBrightness(brightness);
		}

		App->window->GetWindowsSize(App->window->window, width, height);
		if (ImGui::SliderInt("Width", &width, 720, 2560))
		{
			App->window->SetWindowSize(width, height);
		}
		if (ImGui::SliderInt("Height", &height, 480, 1440))
		{
			App->window->SetWindowSize(width, height);
		}

		checkResizable = App->window->GetResizable();
		ImGui::SameLine();
		if (ImGui::Checkbox("Resizable", &checkResizable))
		{

		}
			//checkResizable = !checkResizable;

		checkBorderless = App->window->GetBorderless();
		if (ImGui::Checkbox("Borderless", &checkBorderless))
		{

		}
			//checkBorderless = !checkBorderless;

		checkFullDesktop = App->window->GetFullscreenDesktop();
		ImGui::SameLine();
		if (ImGui::Checkbox("Full Screen", &App->AppTitleScreenFull))
		{

		}

		if (App->renderer3D->vsyncEnabled != NULL)
		{
			checkVsync = App->renderer3D->vsyncEnabled;
		}		
		ImGui::SameLine();
		if (ImGui::Checkbox("Vsync", &checkVsync))
		{
			App->renderer3D->SetVsync(checkVsync);
		}

		ImGui::Separator();
	}


	return ret;
}

bool ConfigurationWindow::AnotherHeader()
{
	bool ret = true;

	if (ImGui::CollapsingHeader("Extra Settings"))
	{
		ImGui::Text("More settings. Why not?");
		ImGui::Text("Nothing to see here... yet.");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Text("Put here wathever setting not about the window");
		ImGui::Separator();
	}


	return ret;
}

bool ConfigurationWindow::FPSHeader()
{
	bool ret = true;

	if (ImGui::CollapsingHeader("FPS"))	{
		
		fps = App->GetMaxFPS();
		ImGui::SliderInt("Max FPS", &fps, 5, 144);
		ImGui::Text("Limit Framerate is at %d", fps);
		App->SetMaxFPS(fps);
	
		ImGui::PlotHistogram("FPS", fpsData, IM_ARRAYSIZE(fpsData), 0, NULL, 0.0f, 144.0f, ImVec2(0, 80));
		ImGui::PlotHistogram("Miliseconds", msData, IM_ARRAYSIZE(msData), 0, NULL, 0.0f, 40.0f, ImVec2(0, 80));

		ImGui::Separator();	
	}

	return ret;
}

void ConfigurationWindow::UpdateFrameData(int frames, int ms)
{
	for (uint i = 0; i < (MAX_HISTOGRAM_SIZE - 1); ++i)
	{
		fpsData[i] = fpsData[i + 1];
		msData[i] = msData[i + 1];
	}
	fpsData[MAX_HISTOGRAM_SIZE - 1] = (float)frames;
	msData[MAX_HISTOGRAM_SIZE - 1] = (float)ms;
}

bool ConfigurationWindow::HardwareHeader()
{
	bool ret = true;

	if (ImGui::CollapsingHeader("Hardware Specifics"))
	{
		//int major, minor, patch;
		//App->GetSDLVersion(major, minor, patch);
		//ImGui::Text("SDL Version: %d.%d.%d", major, minor, patch);
		//ImGui::Separator();
		int count, size;
		App->GetCPU(count, size);
		ImGui::Text("CPUs: %d (%dKb)", count, size);
		float ram = App->GetRAM();
		ImGui::Text("RAM: %.2fGb", ram);
		ImGui::Separator();
		bool threeD, altiVec, avx, avx2, mmx, rdtsc, sse, sse2, sse3, sse41, sse42;
		App->GetCPUFeatures(threeD, altiVec, avx, avx2, mmx, rdtsc, sse, sse2, sse3, sse41, sse42);
		ImGui::Text("CPU features supported: %s%s%s%s%s%s", threeD ? "3DNow, " : "", altiVec ? "AltiVec, " : "", avx ? "AVX, " : "", avx2 ? "AVX2, " : "", mmx ? "MMX, " : "", rdtsc ? "RDTSC, " : "");
		//ImGui::Separator();
		ImGui::Text("", "%s%s%s%s%s", sse ? "SSE, " : "", sse2 ? "SSE2, " : "", sse3 ? "SSE3, " : "", sse41 ? "SSE41, " : "", sse42 ? "SSE42" : "");
		ImGui::Separator();
		ImGui::Text("GPU \nVendor: %s\nRenderer: %s\nDrivers: %s", Vendor.c_str(), GPU_Model.c_str(), Drivers.c_str());
	}

	return ret;
}

bool ConfigurationWindow::SaveRequest()
{
	
	json_object_dotset_number(json_object(App->save_load->configurationFile), "SettingsWindow.Brightness", brightness);
	json_object_dotset_number(json_object(App->save_load->configurationFile), "SettingsWindow.Width", width);
	json_object_dotset_number(json_object(App->save_load->configurationFile), "SettingsWindow.Height", height);

	json_object_dotset_boolean(json_object(App->save_load->configurationFile), "SettingsWindow.Fullscreen", checkFullscreen);
	json_object_dotset_boolean(json_object(App->save_load->configurationFile), "SettingsWindow.Resizable", checkResizable);
	json_object_dotset_boolean(json_object(App->save_load->configurationFile), "SettingsWindow.Borderless", checkBorderless);
	json_object_dotset_boolean(json_object(App->save_load->configurationFile), "SettingsWindow.FullDesktop", checkFullDesktop);
	json_object_dotset_boolean(json_object(App->save_load->configurationFile), "SettingsWindow.Vsync", checkVsync);

	return true;
}

bool ConfigurationWindow::LoadRequest()
{
	brightness = (float)json_object_dotget_number(json_object(App->save_load->configurationFile), "SettingsWindow.Brightness");
	App->window->SetBrightness(brightness);
	
	width = (int)json_object_dotget_number(json_object(App->save_load->configurationFile), "SettingsWindow.Width");
	height = (int)json_object_dotget_number(json_object(App->save_load->configurationFile), "SettingsWindow.Height");
	App->window->SetWindowSize(width, height);

	checkFullscreen = (bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "SettingsWindow.Fullscreen");
	checkResizable = (bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "SettingsWindow.Resizable");
	checkBorderless = (bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "SettingsWindow.Borderless");
	checkFullDesktop = (bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "SettingsWindow.FullDesktop");

	App->renderer3D->SetVsync((bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "SettingsWindow.Vsync"));

	return true;
}