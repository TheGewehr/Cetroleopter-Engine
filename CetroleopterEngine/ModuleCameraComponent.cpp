#include "ModuleCameraComponent.h"
#include "ModuleGameObject.h"
#include "Component.h"

CameraComponent::CameraComponent(ModuleGameObject* base) : Component(base, ComponentTypes::TEXTURE, "Mesh")
{
	
}

CameraComponent::~CameraComponent()
{
	
}

bool CameraComponent::Init()
{


	return true;
}

update_status CameraComponent::Update()
{


	return UPDATE_CONTINUE;
}

bool CameraComponent::CleanUp()
{


	return true;
}
