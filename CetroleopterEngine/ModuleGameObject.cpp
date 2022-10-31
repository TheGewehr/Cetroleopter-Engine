
#include "Application.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleModelImport.h"
#include "ModuleGameObject.h"

ModuleGameObject::ModuleGameObject(bool start_enabled) : Module(start_enabled = true)
{

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

bool ModuleGameObject::CleanUp()
{
	

	return true;
}