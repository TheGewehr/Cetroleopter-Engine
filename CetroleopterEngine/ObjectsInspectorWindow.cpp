#include "ObjectsInspectorWindow.h"

#include "Application.h"
#include "ModuleGameObject.h"
#include "Globals.h"
//#include "imgui.h"
#include "ModuleMeshComponent.h"
#include "ModuleTextureComponent.h"
#include "ModuleTransformComponent.h"

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
	bool noneSelected = true;

	for (int i = 0; i < App->scene_intro->gameObjects.size(); i++)
	{
		if (App->scene_intro->gameObjects.at(i)->GetObjectIsSelected())
		{
			InspectorObject = App->scene_intro->gameObjects.at(i);
			noneSelected = false;
			break;
		}
	}

	if (InspectorObject != nullptr && noneSelected == true)
	{
		InspectorObject = nullptr;
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
				ImGui::Text(InspectorObject->GetMeshComponent()->mesh.path.c_str());


			}
		}
		else
		{
			ImGui::Spacing();
			ImGui::Text("- This Game Object has no meshes");
			ImGui::Spacing();
		}


		if (InspectorObject->GetTransformComponent() != nullptr)
		{
			if (ImGui::CollapsingHeader("Transform"))
			{
				ImGui::Text("Transform:");

				ImGui::Spacing();
				ImGui::Spacing();

				ImGui::PushID(0);
				if (ImGui::CollapsingHeader("Translate"))
				{
					float3 newPosition = InspectorObject->GetTransformComponent()->GetPosition();
					
					ImGui::PushID(4);
					if (ImGui::DragFloat3("", (float*)&newPosition, 0.05f, 0.0f, 0.0f, "%.3f", NULL))
					{
						InspectorObject->GetTransformComponent()->SetPosition(
							newPosition.x,
							newPosition.y,
							newPosition.z
						);			
						
					}
					ImGui::PopID();

					ImGui::SameLine();

					ImGui::PushID(7);
					if (ImGui::Button("Reset"))
					{
						InspectorObject->GetTransformComponent()->SetPosition(0,0,0);
					}
					ImGui::PopID();
				}
				ImGui::PopID();

				
				ImGui::PushID(1);
				if (ImGui::CollapsingHeader("Rotate"))
				{
					float3 rotation = InspectorObject->GetTransformComponent()->GetLocalEulerRotation() * RADTODEG;

					ImGui::PushID(5);
					if (ImGui::DragFloat3("", (float*)&rotation, 0.05f, 0.0f, 0.0f, "%.3f", NULL))
					{
						
						InspectorObject->GetTransformComponent()->SetRotation(rotation * DEGTORAD);
					}
					ImGui::PopID();

					ImGui::SameLine();

					ImGui::PushID(8);
					if (ImGui::Button("Reset"))
					{

						InspectorObject->GetTransformComponent()->SetRotation(float3(0,0,0)*DEGTORAD);
					}
					ImGui::PopID();
				}
				ImGui::PopID();

				
				ImGui::PushID(2);
				if (ImGui::CollapsingHeader("Scale"))
				{
					float3 scale = InspectorObject->GetTransformComponent()->GetScale();

					ImGui::PushID(6);
					if (ImGui::DragFloat3("", (float*)&scale, 0.05f, 0.0f, 0.0f, "%.3f", NULL))
					{
						InspectorObject->GetTransformComponent()->SetScale(scale);
					}
					ImGui::PopID();

					ImGui::SameLine();

					ImGui::PushID(9);
					if (ImGui::Button("Reset"))
					{
						InspectorObject->GetTransformComponent()->SetScale(float3(1,1,1));
					}
					ImGui::PopID();
				}
				ImGui::PopID();

				ImGui::Spacing();

				ImGui::PushID(10);
				if (ImGui::Button("Reset All"))
				{
					InspectorObject->GetTransformComponent()->SetPosition(0, 0, 0);
					InspectorObject->GetTransformComponent()->SetRotation(float3(0, 0, 0) * DEGTORAD);
					InspectorObject->GetTransformComponent()->SetScale(float3(1, 1, 1));
				}
				ImGui::PopID();

				ImGui::Spacing();
				ImGui::Spacing();
			}			
		}
		else
		{
			ImGui::Spacing();
			ImGui::Text("- Objects with no meshes cannot be transformed");
			ImGui::Spacing();
		}
		if (InspectorObject->GetTextureComponent() != nullptr)
		{
			if (ImGui::CollapsingHeader("Texture"))
			{
				ImGui::Text("Textures:");				
				
				for (int j = 0; j < InspectorObject->GetTextureComponent()->textures.size(); j++)
				{
					if ( InspectorObject->GetTextureComponent()->textures[j]->path.c_str() != nullptr)
					{						
						ImGui::Text(InspectorObject->GetTextureComponent()->textures[j]->path.c_str());					
					}
					else
					{
						ImGui::Text(" No texture path");
					}
				}
				
			}
				
		}
		else
		{
			ImGui::Spacing();
			ImGui::Text("- This Game Object has no textures");
			ImGui::Spacing();
		}
		if (InspectorObject->GetCameraComponent() != nullptr)
		{
			if (ImGui::CollapsingHeader("Camera"))
			{
				ImGui::Text("Cameras:");

				
				ImGui::Text("\nNothing here yet...\n");

			}
		}
		else
		{
			ImGui::Spacing();
			ImGui::Text("- This Game Object has no cameras");
			ImGui::Spacing();
		}

		HierarchyOptions();
	}
	else 
	{
		ImGui::Spacing();
		ImGui::Text("	No Game Object Selected");
		ImGui::Spacing();
	}


	return true;
}

void ObjectsInspectorWindow::HierarchyOptions()
{
	
	ImGui::PushID(13);
	if (ImGui::CollapsingHeader("Hierarchy Options"))
	{
		ImGui::PushID(12);
		if (ImGui::Button("DOnete") == true)
		{
			if (hierarchyDummy != (int)NONE)
			{
				if (hierarchyDummy == (int)SETPARENT)
				{
					InspectorObject;
				}
				if (hierarchyDummy == (int)ADDCHILD)
				{

				}
				if (hierarchyDummy == (int)DELETEOBJECT)
				{

				}
			}
		}
		ImGui::PopID();

		ImGui::SameLine();

		ImGui::PushID(11);
		if (ImGui::Button("DO") == true)
		{
			if (hierarchyDummy != (int)NONE)
			{
				if (hierarchyDummy == (int)SETPARENT)
				{
					InspectorObject;
				}
				if (hierarchyDummy == (int)ADDCHILD)
				{

				}
				if (hierarchyDummy == (int)DELETEOBJECT)
				{

				}
			}
		}
		ImGui::PopID();

	}
	ImGui::PopID();
	
}

