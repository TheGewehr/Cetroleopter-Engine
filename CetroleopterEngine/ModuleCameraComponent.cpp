#include "ModuleCameraComponent.h"
#include "ModuleGameObject.h"
#include "Component.h"

CameraComponent::CameraComponent(ModuleGameObject* base) : Component(base, ComponentTypes::CAMERA, "Camera")
{
	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 50.0f, 50.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
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
