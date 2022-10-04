#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "ModuleSceneIntro.h"
#include "MainMenuBar.h"
#include "AboutWindow.h"


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

	if (App->moduleUi->hoveringWindow == false)
		App->moduleUi->hoveringWindow = ImGui::IsWindowHovered(); // To know if the window is being moved

	CreateMainMenuBar();

	//ImGui::End();

	return ret;
}

bool MainMenuBar::CleanUp()
{
	bool ret = true;

	return ret;
}

bool MainMenuBar::CreateMainMenuBar()
{
	bool ret = true;

	ImGui::BeginMainMenuBar();
	
	if (ImGui::BeginMenu("Help",true))
	{
		if (ImGui::MenuItem("Go to: https://github.com/TheGewehr/Cetroleopter-Engine"))
		{
			App->OpenBrowserWebPage("https://github.com/TheGewehr/Cetroleopter-Engine");
		}

		if (ImGui::MenuItem("About"))
		{
			//aboutON = !aboutON;
			App->moduleUi->aboutWindow->ChangeActive();

		}

		/*if (aboutON == false)
		{
			App->moduleUi->aboutWindow->Disable();
		}
		else if (aboutON == true)
		{
			App->moduleUi->aboutWindow->Enable();

		}*/

		ImGui::EndMenu();
	}
	
	
	ImGui::EndMainMenuBar();

	return ret;
}
