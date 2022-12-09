#include "ModuleMeshComponent.h"
#include "ModuleGameObject.h"
#include "Component.h"

MeshComponent::MeshComponent(ModuleGameObject* base) : Component(base, ComponentTypes::MESH, "Mesh")
{

	meshPath = mesh.path.c_str();
}

MeshComponent::~MeshComponent()
{
	
}

bool MeshComponent::Init()
{


	return true;
}

update_status MeshComponent::Update()
{


	return UPDATE_CONTINUE;
}

bool MeshComponent::CleanUp()
{


	return true;
}

bool MeshComponent::SaveComponent(int positionInList)
{
	std::string listPosition = std::to_string(positionInList);
	meshPath = mesh.path.c_str();
	json_object_dotset_string(json_object(App->save_load->sceneFile), std::string("Scene01.GameObjectsList." + listPosition + ".MeshComponent.Path").c_str(), meshPath);

	return false;
}

bool MeshComponent::LoadComponent(int positionInList)
{
	std::string listPosition = std::to_string(positionInList);

	meshPath = json_object_dotget_string(json_object(App->save_load->sceneFile), std::string("Scene01.GameObjectsList." + listPosition + ".MeshComponent.Path").c_str());

	return false;
}


