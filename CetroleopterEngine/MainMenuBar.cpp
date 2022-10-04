#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "ModuleSceneIntro.h"
#include "MainMenuBar.h"
#include "AboutWindow.h"
#include "ConfigurationWindow.h"


MainMenuBar::MainMenuBar(const char* name, bool isActive) : ImGuiWindowBase("MainMenuBar", isActive = true)
{
	
}

MainMenuBar::~MainMenuBar()
{
}

bool MainMenuBar::Draw(ImGuiIO& io)
{
	bool ret = true;
	

	//ImGui::Begin(GetName(), nullptr, ImGuiWindowFlags_None);
	ImGui::BeginMainMenuBar();

	if (App->moduleUi->hoveringWindow == false)
		App->moduleUi->hoveringWindow = ImGui::IsWindowHovered(); // To know if the window is being moved

	FileMenuBar();
	EditMenuBar();
	ViewMenuBar();
	HelpMenuBar();

	//ImGui::End();
	ImGui::EndMainMenuBar();

	return ret;
}

bool MainMenuBar::CleanUp()
{
	bool ret = true;

	return ret;
}

bool MainMenuBar::FileMenuBar()
{
	bool ret = true;

	if (ImGui::BeginMenu("File"))
	{

		if (ImGui::MenuItem("Save Project"))
		{
			
		}
		if (ImGui::MenuItem("Load Project"))
		{
			
		}
		if (ImGui::MenuItem("Exit"))
		{
			App->appExit = true;
		}

		ImGui::EndMenu();
	}

	return ret;
}

bool MainMenuBar::EditMenuBar()
{
	bool ret = true;

	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem("Cut"))
		{

		}
		if (ImGui::MenuItem("Copy"))
		{

		}
		if (ImGui::MenuItem("Paste"))
		{

		}
		ImGui::Separator();
		if (ImGui::MenuItem("Settings", "", App->moduleUi->configurationWindow->isActive))
		{
			App->moduleUi->configurationWindow->ChangeActive();
		}

		ImGui::EndMenu();
	}

	return ret;
}

bool MainMenuBar::ViewMenuBar()
{
	bool ret = true;

	if (ImGui::BeginMenu("View"))
	{
		
		if (ImGui::Checkbox("Wireframe Mode", &wireframeMode))
		{

		}
		if (ImGui::Checkbox("Cull Faces", &faceCullingMode))
		{

		}
		if (ImGui::Checkbox("Disable Lights", &disableLights))
		{

		}
		if (ImGui::Checkbox("Show Windows Console", &showConsole))
		{

		}

		ImGui::EndMenu();
	}

	return ret;
}

bool MainMenuBar::HelpMenuBar()
{
	bool ret = true;
	
	if (ImGui::BeginMenu("Help",true))
	{
		if (ImGui::MenuItem("Go to: https://github.com/TheGewehr/Cetroleopter-Engine"))
		{
			App->OpenBrowserWebPage("https://github.com/TheGewehr/Cetroleopter-Engine");
		}

		if (ImGui::MenuItem("About", "", App->moduleUi->aboutWindow->isActive))
		{
			App->moduleUi->aboutWindow->ChangeActive();

		}

		ImGui::EndMenu();
	}

	return ret;
}
