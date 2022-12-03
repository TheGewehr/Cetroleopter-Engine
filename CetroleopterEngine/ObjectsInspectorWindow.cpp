#include "ObjectsInspectorWindow.h"

#include "Application.h"
#include "ModuleGameObject.h"
#include "Globals.h"
#include "imgui.h"
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
					//LOG("T %i", App->moduleGameObject->currentSelectedObject);

					// for q
						//App->moduleGameObject->objects[i].meshes[q].transform.position
					

					float3 newPosition = InspectorObject->GetTransformComponent()->GetPosition();
					//newPosition.x = InspectorObject->GetTransformComponent()->GetPosition().x;
					//newPosition.y = InspectorObject->GetTransformComponent()->GetPosition().y;
					//newPosition.z = InspectorObject->GetTransformComponent()->GetPosition().z;
					
					if (ImGui::DragFloat3("Location", (float*)&newPosition, 0.05f, 0.0f, 0.0f, "%.3f", NULL))
					{
						InspectorObject->GetTransformComponent()->SetPosition(
							InspectorObject->GetTransformComponent()->GetPosition().x+ newPosition.x,
							InspectorObject->GetTransformComponent()->GetPosition().y + newPosition.y,
							InspectorObject->GetTransformComponent()->GetPosition().z + newPosition.z
						);			
						//InspectorObject->GetTransformComponent()->UpdateWorldTransform();
						//InspectorObject->GetTransformComponent()->UpdateWorldTransform();

					}
				}
				ImGui::PopID();

				//ImGui::SameLine();

				ImGui::PushID(1);
				if (ImGui::CollapsingHeader("Rotate"))
				{
					float3 rotation = InspectorObject->GetTransformComponent()->GetLocalEulerRotation() * RADTODEG;


					if (ImGui::DragFloat3("Location", (float*)&rotation, 0.05f, 0.0f, 0.0f, "%.3f", NULL))
					{
						
						InspectorObject->GetTransformComponent()->SetRotation(rotation * DEGTORAD);
					}
				}
				ImGui::PopID();

				//ImGui::SameLine();

				ImGui::PushID(2);
				if (ImGui::CollapsingHeader("Scale"))
				{
					float3 scale = InspectorObject->GetTransformComponent()->GetScale();
					if (ImGui::DragFloat3("S", (float*)&scale, 0.05f, 0.0f, 0.0f, "%.3f", NULL))
					{
						InspectorObject->GetTransformComponent()->SetScale(scale);
					}
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
				
					//for (int k = 0; k < App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].textures.size(); k++)
					//{
					//	ImGui::Text("	Texture [%i]:", k);
					//	ImGui::Text("		%s", App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].textures[k].path.c_str());
					//	//ImGui::Text("		%s", App->moduleGameObject->objects[App->moduleGameObject->currentSelectedObject].meshes[k].meshTexturesData.path.c_str());
					//}
				
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
				
				//->objMain_->GetTextureComponent()->objectTexture->path.c_str()
				
				//ImGui::Text("		%c", );
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
	}
	else 
	{
		ImGui::Spacing();
		ImGui::Text("	No Game Object Selected");
		ImGui::Spacing();
	}


	return true;
}

