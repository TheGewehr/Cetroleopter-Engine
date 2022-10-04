#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "ModuleSceneIntro.h"
#include "ConfigurationWindow.h"


ConfigurationWindow::ConfigurationWindow(const char* name, bool isActive) : ImGuiWindowBase("Settings", isActive = true)
{
	//fps = 0;
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	checkResizable = WIN_RESIZABLE;
	checkBorderless = WIN_BORDERLESS;
	checkFullDesktop = WIN_FULLSCREEN_DESKTOP;
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
	AnotherHeader();
	PlotFrameHistogram();
	
	ImGui::End();

	return ret;
}

bool ConfigurationWindow::CleanUp()
{
	bool ret = true;

	return ret;
}

bool ConfigurationWindow::PlotFrameHistogram()
{
	//ImGui::PlotHistogram("FPS", fpsData, IM_ARRAYSIZE(fpsData), 0, NULL, 0.0f, 144.0f, ImVec2(0, 80));
	//ImGui::PlotHistogram("MS", msData, IM_ARRAYSIZE(msData), 0, NULL, 0.0f, 40.0f, ImVec2(0, 80));
	return true;
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

		if (ImGui::Checkbox("Fullscreen", &checkFullscreen))
			checkFullscreen = !checkFullscreen;

		ImGui::SameLine();
		if (ImGui::Checkbox("Resizable", &checkResizable))
			checkResizable = !checkResizable;

		if (ImGui::Checkbox("Borderless", &checkBorderless))
			checkBorderless = !checkBorderless;

		ImGui::SameLine();
		if (ImGui::Checkbox("Full Desktop", &checkFullDesktop))
			checkFullDesktop = !checkFullDesktop;
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
	}


	return ret;
}
