#include "ModuleSaveLoad.h"

ModuleSaveLoad::ModuleSaveLoad(bool start_enabled) : Module(start_enabled)
{
	
}

// Destructor
ModuleSaveLoad::~ModuleSaveLoad()
{
}

bool ModuleSaveLoad::Init()
{
	LOG("Initializing ModuleSaveLoad");

	return true;
}

update_status ModuleSaveLoad::PostUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}

bool ModuleSaveLoad::CleanUp()
{
	LOG("Cleaning ModuleSaveLoad");

	return true;
}