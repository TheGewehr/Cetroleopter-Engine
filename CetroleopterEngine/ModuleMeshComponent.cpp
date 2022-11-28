#include "ModuleMeshComponent.h"
#include "ModuleGameObject.h"
#include "Component.h"

MeshComponent::MeshComponent(ModuleGameObject* base) : Component(base, ComponentTypes::MESH, "Mesh")
{
	
}

MeshComponent::~MeshComponent()
{
	
}


