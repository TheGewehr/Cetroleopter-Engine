#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "DebugSceneViewWindow.h"


//#include "assimp/Include/version.h" // From assimp

DebugSceneViewWindow::DebugSceneViewWindow(const char* name, bool isActive) : ImGuiWindowBase("DebugSceneViewWindow", isActive = false)
{
	
}

DebugSceneViewWindow::~DebugSceneViewWindow()
{
}

bool DebugSceneViewWindow::Draw(ImGuiIO& io)
{
	bool ret = true;


	ImGui::Begin(GetName(), nullptr, ImGuiWindowFlags_None);

	if (App->moduleUi->hoveringWindow == false)
		App->moduleUi->hoveringWindow = ImGui::IsWindowHovered(); // To know if the window is being moved

	//App->moduleUi->hoveringWindow = flase;

	DrawScene();

	ImGui::End();

	return ret;
}

bool DebugSceneViewWindow::CleanUp()
{
	bool ret = true;

	return ret;
}

bool DebugSceneViewWindow::DrawScene()
{
	bool ret = true;
	
	cursor_pos = ImVec2((ImGui::GetWindowSize().x - tex_size.x) * 0.5f, (ImGui::GetWindowSize().y - tex_size.y) * 0.5f);
	
	ImGui::SetCursorPos(cursor_pos);

	ImVec2 screen_cursor_pos = ImGui::GetCursorScreenPos();

	if (screen_cursor_pos.x > 1920)																			
	{
		screen_cursor_pos.x = screen_cursor_pos.x - 1920;
	}

	
	tex_origin = ImVec2(screen_cursor_pos.x, screen_cursor_pos.y + tex_size.y);
	
	tex_origin.y = (float)App->window->GetHeight() - tex_origin.y;		

	


	return ret;
}
