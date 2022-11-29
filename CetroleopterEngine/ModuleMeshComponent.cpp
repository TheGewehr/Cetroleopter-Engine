#include "ModuleMeshComponent.h"
#include "ModuleGameObject.h"
#include "Component.h"

MeshComponent::MeshComponent(ModuleGameObject* base) : Component(base, ComponentTypes::MESH, "Mesh")
{
	
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


