#include "GameObjectsWindow.h"

#include "Application.h"
#include "ModuleGameObject.h"
#include "Globals.h"
#include "imgui.h"

GameObjectsWindow::GameObjectsWindow(const char* name, bool isActive) : ImGuiWindowBase("GameObjects", isActive = true)
{

}

GameObjectsWindow::~GameObjectsWindow()
{

}

bool GameObjectsWindow::Draw(ImGuiIO& io)
{
	
	bool ret = true;


	ImGui::Begin(GetName(), nullptr, ImGuiWindowFlags_None);

	if (App->moduleUi->hoveringWindow == false)
		App->moduleUi->hoveringWindow = ImGui::IsWindowHovered(); // To know if the window is being moved

	ObjectWindowHeader();

	ImGui::End();

	return ret;
	
}

bool GameObjectsWindow::CleanUp()
{
	return true;
}


bool GameObjectsWindow::ObjectWindowHeader()
{
	if (App->moduleGameObject->objects.size() > 0)
	{
		for (int i = 0; i < App->moduleGameObject->objects.size(); i++)
		{
			App->moduleGameObject->objects[i].objectID = i;

			ImGui::Text("[OBJ %i]:", i);
			ImGui::SameLine();

			ImGui::PushID(i);
			
			if (ImGui::Button("See Object"))
			{
				App->moduleGameObject->currentSelectedObject = App->moduleGameObject->objects[i].objectID;
				//LOG("Selected Object %i", App->moduleGameObject->currentSelectedObject);
			}

			ImGui::PopID();

			
		}
	}

	return true;
}