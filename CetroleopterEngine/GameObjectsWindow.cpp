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
	//App->scene_intro->gameObjects.size()
	//App->scene_intro->gameObjects.at(i)
	
	if (App->scene_intro->gameObjects.size() > 0)
	{
		TreeProcessing(App->scene_intro->gameObjects);
	}

	return true;
}

const char* GameObjectsWindow::GetObjectName(std::string name) const
{
	return name.c_str();
}

void GameObjectsWindow::TreeProcessing(std::vector<ModuleGameObject*> objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		
		if (objects.at(i)->childs.empty())
		{
			flags |= ImGuiTreeNodeFlags_Leaf;
		}
		if (objects.at(i)->GetObjectIsSelected() != false && objects == App->scene_intro->gameObjects)
		{
			flags |= ImGuiTreeNodeFlags_Selected;
		}
		

		ImGui::PushID(i);
		
		if (ImGui::TreeNodeEx(objects.at(i)->GetName().c_str(), flags))
		{
			//ImGui::Text("n palabra (naranja)");
			if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
			{
				objects.at(i)->SelectObject();
			}


			if (!objects.at(i)->childs.empty())
			{
				for (uint j = 0; j < objects.at(i)->childs.size(); ++j)
				{
					TreeProcessing(objects.at(i)->childs);
				}
			}
			ImGui::TreePop();
		}
		ImGui::PopID();


	}
}
