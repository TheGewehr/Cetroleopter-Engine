#include "ObjectsInspectorWindow.h"

#include "Application.h"
#include "ModuleGameObject.h"
#include "Globals.h"
#include "imgui.h"
#include "ModuleMeshComponent.h"
#include "ModuleTextureComponent.h"

ObjectsInspectorWindow::ObjectsInspectorWindow(const char* name, bool isActive) : ImGuiWindowBase("GameObjects Inspector", isActive = true)
{

}

ObjectsInspectorWindow::~ObjectsInspectorWindow()
{

}

bool ObjectsInspectorWindow::Draw(ImGuiIO& io)
{
	
	bool ret = true;


	ImGui::Begin(GetName(), nullptr, ImGuiWindowFlags_None);

	if (App->moduleUi->hoveringWindow == false)
		App->moduleUi->hoveringWindow = ImGui::IsWindowHovered(); // To know if the window is being moved

	InspectorWindowHeader();

	ImGui::End();

	return ret;
	
}

bool ObjectsInspectorWindow::CleanUp()
{
	return true;
}


bool ObjectsInspectorWindow::InspectorWindowHeader()
{
	InspectorObject = nullptr;

	for (int i = 0; i < App->scene_intro->gameObjects.size(); i++)
	{
		if (App->scene_intro->gameObjects.at(i)->GetObjectIsSelected())
		{
			InspectorObject = App->scene_intro->gameObjects.at(i);
		}
	}

	if (InspectorObject != nullptr)
	{
		if (InspectorObject->GetMeshComponent() != nullptr)
		{
			if (ImGui::CollapsingHeader("Mesh"))
			{
				ImGui::Text("Meshes:");

				//for (int j = 0; j < App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].meshes.size(); j++)
				//{
				//	ImGui::Text("	Mesh [%i]:", j);
				//	ImGui::Text("		%s", App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].meshes[j].path.c_str());
				//}
				ImGui::Text("	Mesh:");
				ImGui::Text("		%c", InspectorObject->GetMeshComponent()->meshPath);


			}
		}
		else
		{
			ImGui::Spacing();
			ImGui::Text("	This Game Object has no meshes");
			ImGui::Spacing();
		}


		if (InspectorObject->GetTransformComponent() != nullptr)
		{
			if (ImGui::CollapsingHeader("Transform"))
			{
				ImGui::Text("Transform:");

				ImGui::Spacing();
				ImGui::Spacing();

				//ImGui::PushID(App->moduleGameObject->currentSelectedObject);
				if (ImGui::Button("Translate"))
				{
					//LOG("T %i", App->moduleGameObject->currentSelectedObject);

					// for q
						//App->moduleGameObject->objects[i].meshes[q].transform.position
				}
				//ImGui::PopID();

				ImGui::SameLine();

				//ImGui::PushID(App->moduleGameObject->currentSelectedObject);
				if (ImGui::Button("Rotate"))
				{
					//LOG("R %i", App->moduleGameObject->currentSelectedObject);

					// for q
						//App->moduleGameObject->objects[i].meshes[q].transform.rotate
				}
				//ImGui::PopID();

				ImGui::SameLine();

				//ImGui::PushID(App->moduleGameObject->currentSelectedObject);
				if (ImGui::Button("Scale"))
				{
					//LOG("S %i", App->moduleGameObject->currentSelectedObject);

					// for q
						//App->moduleGameObject->objects[i].meshes[q].transform.scale
				}
				//ImGui::PopID();

				ImGui::Spacing();
				ImGui::Spacing();
			}			
		}
		else
		{
			ImGui::Spacing();
			ImGui::Text("	Objects with no meshes cannot be transformed");
			ImGui::Spacing();
		}
		if (InspectorObject->GetTextureComponent() != nullptr)
		{
			if (ImGui::CollapsingHeader("Texture"))
			{
				ImGui::Text("Textures:");
				
					//for (int k = 0; k < App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].textures.size(); k++)
					//{
					//	ImGui::Text("	Texture [%i]:", k);
					//	ImGui::Text("		%s", App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].textures[k].path.c_str());
					//	//ImGui::Text("		%s", App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].meshes[k].meshTexturesData.path.c_str());
					//}
				
				ImGui::Text("		%c", InspectorObject->GetTextureComponent()->texturePath);
			}
				
		}
		else
		{
			ImGui::Spacing();
			ImGui::Text("	This Game Object has no textures");
			ImGui::Spacing();
		}
	}
	else 
	{
		ImGui::Spacing();
		ImGui::Text("	No Game Object Selected");
		ImGui::Spacing();
	}


	return true;
}

