#include "ObjectsInspectorWindow.h"

#include "Application.h"
#include "ModuleGameObject.h"
#include "Globals.h"
#include "imgui.h"

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
	if (App->moduleGameObject->currentSelectedObject >= 0)
	{
		if (ImGui::CollapsingHeader("Mesh"))
		{
			ImGui::Text("Meshes:");
			if (App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].meshes.size() > 0)
			{
				for (int j = 0; j < App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].meshes.size(); j++)
				{
					ImGui::Text("	Mesh [%i]:", j);
					ImGui::Text("		%s", App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].meshes[j].path.c_str());
				}
			}
			else
			{
				ImGui::Text("	This Game Object has no meshes");
			}
		}
		if (ImGui::CollapsingHeader("Transform"))
		{
			ImGui::Text("Transform:");
			if (App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].meshes.size() > 0)
			{
				ImGui::Spacing();
				ImGui::Spacing();

				//for (int k = 0; k < App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].meshes.size(); k++)
				//{
				//	float3 position = App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].meshes[k].transform->GetPosition();
				//
				//	if (ImGui::DragFloat3("Position", (float*)&position, 0.05f, 0.0f, 0.0f, "%.3f", NULL))
				//	{
				//		App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].meshes[k].transform->SetPosition(position.x, position.y, position.z);
				//	}
				//}

				

				//float3 rotation = RadToDeg(comp->GetLocalEulerRotation());
				//if (ImGui::DragFloat3("Rotation", (float*)&rotation, 1.0f, 0.0f, 0.0f, "%.3f", NULL))
				//{
				//	comp->SetLocalEulerRotation(rotation);
				//}
				//
				//float3 scale = comp->GetScale();
				//if (ImGui::DragFloat3("Scale", (float*)&scale, 0.05f, 0.0f, 0.0f, "%.3f", NULL))
				//{
				//	comp->SetScale(scale.x, scale.y, scale.z);
				//}

				ImGui::Spacing();
				ImGui::Spacing();
			}
			else
			{
				ImGui::Text("	Objects with no meshes cannot be transformed");
			}
		}
		if (ImGui::CollapsingHeader("Texture"))
		{
			ImGui::Text("Textures:");
			if (App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].textures.size() > 0)
			{
				for (int k = 0; k < App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].textures.size(); k++)
				{
					ImGui::Text("	Texture [%i]:", k);
					ImGui::Text("		%s", App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].textures[k].path.c_str());
					//ImGui::Text("		%s", App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].meshes[k].meshTexturesData.path.c_str());
				}
			}
			else
			{
				ImGui::Text("	This Game Object has no textures");
			}
		}
	}

	return true;
}

