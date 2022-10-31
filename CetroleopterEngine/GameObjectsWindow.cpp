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
			ImGui::Text("Game Object [%i]:", i);

			ImGui::Text("	Meshes:");
			if (App->moduleGameObject->objects[i].meshes.size() > 0)
			{
				for (int j = 0; j < App->moduleGameObject->objects[i].meshes.size(); j++)
				{
					ImGui::Text("		Mesh [%i]:", j);
					ImGui::Text("			%s", App->moduleGameObject->objects[i].meshes[j].path.c_str());
				}
			}
			else
			{
				ImGui::Text("		This Game Object has no meshes");
			}


			ImGui::Text("	Textures:");
			if (App->moduleGameObject->objects[i].textures.size() > 0)
			{
				for (int k = 0; k < App->moduleGameObject->objects[i].textures.size(); k++)
				{
					ImGui::Text("		Texture [%i]:", k);
					ImGui::Text("			%s", App->moduleGameObject->objects[i].meshes[k].meshTexturesData.path.c_str());
				}
			}
			else
			{
				ImGui::Text("		This Game Object has no textures");
			}


			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();
		}
	}

	return true;
}