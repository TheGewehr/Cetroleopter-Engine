
#include "Application.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleModelImport.h"
#include "ModuleGameObject.h"

ModuleGameObject::ModuleGameObject(uint obj_ID, std::string name, bool isActive) : id_(obj_ID), name_(name), is_active(isActive)
{
	this->id_ = obj_ID;
	this->name_ = name;
	this->is_active = isActive;

	AddComponent(ComponentTypes::MESH);
	AddComponent(ComponentTypes::TEXTURE);
	AddComponent(ComponentTypes::TRANSFORM);
}

ModuleGameObject::~ModuleGameObject()
{
}

bool ModuleGameObject::Init()
{
	

	return true;
}

update_status ModuleGameObject::Update(float dt)
{

	return UPDATE_CONTINUE;
}

void ModuleGameObject::Render()
{

}

bool ModuleGameObject::CleanUp()
{
	

	return true;
}

bool ModuleGameObject::GetObjectIsActive()
{


	return true;
}

void ModuleGameObject::SetObjectActive(bool state)
{

}

bool ModuleGameObject::GetObjectIsSelected()
{


	return true;
}

void ModuleGameObject::CurrentSelectObject()
{

}

void ModuleGameObject::SetName(const char* newName)
{

}

std::string ModuleGameObject::GetName()
{


	return std::string();
}

std::string ModuleGameObject::GetMeshPath()
{


	return std::string();
}

std::string ModuleGameObject::GetTexturePath()
{


	return std::string();
}

bool ModuleGameObject::AddChild(ModuleGameObject* child)
{


	return true;
}

bool ModuleGameObject::DeleteChild(ModuleGameObject* child)
{


	return true;
}
