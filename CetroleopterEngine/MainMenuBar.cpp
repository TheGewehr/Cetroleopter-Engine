#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "ModuleSceneIntro.h"
#include "MainMenuBar.h"


MainMenuBar::MainMenuBar(const char* name, bool isActive) : ImGuiWindowBase("MainMenuBar")
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
			/*Add an “About ..” modal window inside
				the “Help” menu that shows :
			○ Name of your Engine
				○ One(or few) line description
				○ Name of the Author with link to github page
				○ Libraries(with versions queried in real time)
				used with links to their web
				○ Full text of the license*/
		}

		ImGui::EndMenu();
	}
	
	
	ImGui::EndMainMenuBar();

	return ret;
}
