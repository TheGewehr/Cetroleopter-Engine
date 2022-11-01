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

			//ObjectWindowButton(App->moduleGameObject->objects[i].objectID);
			ImGui::Text("[OBJ_ID %i]:", i);
			ImGui::SameLine();

			ImGui::PushID(i);
			
			if (ImGui::Button("Game Object"))
			{
				App->moduleGameObject->currentSelectedObject = App->moduleGameObject->objects[i].objectID;
				LOG("Selected Object %i", App->moduleGameObject->currentSelectedObject);
			}

			ImGui::PopID();

			//ImGui::Text("Game Object [%i]:", i);

			//ImGui::Text("	Meshes:");
			//if (App->moduleGameObject->objects[i].meshes.size() > 0)
			//{
			//	for (int j = 0; j < App->moduleGameObject->objects[i].meshes.size(); j++)
			//	{
			//		ImGui::Text("		Mesh [%i]:", j);
			//		ImGui::Text("			%s", App->moduleGameObject->objects[i].meshes[j].path.c_str());
			//	}
			//}
			//else
			//{
			//	ImGui::Text("		This Game Object has no meshes");
			//}


			//ImGui::Text("	Textures:");
			//if (App->moduleGameObject->objects[i].textures.size() > 0)
			//{
			//	for (int k = 0; k < App->moduleGameObject->objects[i].textures.size(); k++)
			//	{
			//		ImGui::Text("		Texture [%i]:", k);
			//		ImGui::Text("			%s", App->moduleGameObject->objects[i].textures[k].path.c_str());
			//		//ImGui::Text("			%s", App->moduleGameObject->objects[i].meshes[k].meshTexturesData.path.c_str());
			//	}
			//}
			//else
			//{
			//	ImGui::Text("		This Game Object has no textures");
			//}

			//if (App->moduleGameObject->objects[i].meshes.size() > 0)
			//{
			//	ImGui::Spacing();
			//	ImGui::Spacing();

			//	if (ImGui::Button("Translate"))
			//	{
			//		// for q
			//			//App->moduleGameObject->objects[i].meshes[q].transform.position
			//	}

			//	ImGui::SameLine();

			//	if (ImGui::Button("Rotate"))
			//	{
			//		// for q
			//			//App->moduleGameObject->objects[i].meshes[q].transform.rotate
			//	}

			//	ImGui::SameLine();

			//	if (ImGui::Button("Scale"))
			//	{
			//		// for q
			//			//App->moduleGameObject->objects[i].meshes[q].transform.scale
			//	}

			//	ImGui::Spacing();
			//	ImGui::Spacing();
			//}


			//ImGui::Spacing();
			//ImGui::Separator();
			//ImGui::Spacing();
		}
	}

	return true;
}

bool GameObjectsWindow::ObjectWindowButton(int obj_id)
{
	ImGui::Text("[OBJ_ID %i]:", obj_id);
	ImGui::SameLine();
	if (ImGui::Button("Game Object"))
	{
		App->moduleGameObject->currentSelectedObject = obj_id;
		LOG("Selected Object %i", App->moduleGameObject->currentSelectedObject);
	}

	return true;
}