#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "ModuleSceneIntro.h"
#include "AboutWindow.h"


AboutWindow::AboutWindow(const char* name, bool isActive) : ImGuiWindowBase("AboutWindow")
{
	//fps = 0;
}

AboutWindow::~AboutWindow()
{
}

bool AboutWindow::Draw(ImGuiIO& io)
{
	bool ret = true;

	
	ImGui::Begin(GetName(), nullptr, ImGuiWindowFlags_None);

	if (App->moduleUi->hoveringWindow == false)
		App->moduleUi->hoveringWindow = ImGui::IsWindowHovered(); // To know if the window is being moved
	
	AboutHeader();
	
	ImGui::End();

	return ret;
}

bool AboutWindow::CleanUp()
{
	bool ret = true;

	return ret;
}

bool AboutWindow::AboutHeader()
{
	bool ret = true;
	/*Add an “About ..” modal window inside
			the “Help” menu that shows :
		○ Name of your Engine
			○ One(or few) line description
			○ Name of the Author with link to github page
			○ Libraries(with versions queried in real time)
			used with links to their web
			○ Full text of the license*/
	if (ImGui::CollapsingHeader("About")) //Cambiar a ListBoxHeader
	{
		ImGui::Text("Nothing to see here... yet.");
		ImGui::NewLine();
	}


	return ret;
}
