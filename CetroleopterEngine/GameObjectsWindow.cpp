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
		//
		//
		//ImGui::Text("[OBJ %s]:", App->scene_intro->gameObjects.at(i)->GetName());
		//ImGui::SameLine();

		//const char* objectNameForHeader = "
		//
		//
		//
		//if (ImGui::CollapsingHeader(GetObjectName(objects.at(i)->GetName())))
		//{
		//	objects.at(i)->SelectObject();
		//	//LOG("Selected Object %i", App->moduleGameObject->currentSelectedObject);
		//}
		//
		//

		//ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;;
		//
		//if (objects.at(i)->childs.empty())
		//{
		//	flags |= ImGuiTreeNodeFlags_Leaf;
		//}
		//if (objects.at(i)->GetObjectIsSelected() != false && objects == App->scene_intro->gameObjects)
		//{
		//	flags |= ImGuiTreeNodeFlags_Selected;
		//}
		//if (app->sceneIntro->sceneRoot != nullptr && objs == app->sceneIntro->sceneRoot)
		//{
		//	flags |= ImGuiTreeNodeFlags_DefaultOpen;
		//}

		//if (ImGui::TreeNodeEx(GetObjectName(objects.at(i)->GetName())))
		if (ImGui::TreeNodeEx(std::to_string(i).c_str())) // Don't let them have the same name ;_-(
		{
			//ImGui::Text("n palabra (naranja)");
			//if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
			//{
			//	if (objects.at(i)->GetObjectIsSelected() == true)
			//	{
			//		objects.at(i)->SelectObject(); // Deselect
			//	}
			//	else
			//	{ // Review this part
			//		bool isOtherSelected = false;
			//		for (int j = 0; j < objects.size(); j++)
			//		{
			//			if (objects.at(j)->GetObjectIsSelected() == true && objects.at(i) != objects.at(j))
			//			{
			//				isOtherSelected = true;
			//				break;
			//			}
			//			
			//		}
			//		if (isOtherSelected == false)
			//		{
			//			objects.at(i)->SelectObject();
			//		}
			//	}
			//	
			//}


			if (!objects.at(i)->childs.empty())
			{
				for (uint j = 0; j < objects.at(i)->childs.size(); ++j)
				{
					TreeProcessing(objects.at(i)->childs);
				}
			}
			ImGui::TreePop();
		}


	}
}
