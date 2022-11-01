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

				ImGui::PushID(App->moduleGameObject->currentSelectedObject);
				if (ImGui::Button("Translate"))
				{
					//LOG("T %i", App->moduleGameObject->currentSelectedObject);

					// for q
						//App->moduleGameObject->objects[i].meshes[q].transform.position
				}
				ImGui::PopID();

				ImGui::SameLine();

				ImGui::PushID(App->moduleGameObject->currentSelectedObject);
				if (ImGui::Button("Rotate"))
				{
					//LOG("R %i", App->moduleGameObject->currentSelectedObject);

					// for q
						//App->moduleGameObject->objects[i].meshes[q].transform.rotate
				}
				ImGui::PopID();

				ImGui::SameLine();

				ImGui::PushID(App->moduleGameObject->currentSelectedObject);
				if (ImGui::Button("Scale"))
				{
					//LOG("S %i", App->moduleGameObject->currentSelectedObject);

					// for q
						//App->moduleGameObject->objects[i].meshes[q].transform.scale
				}
				ImGui::PopID();

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

