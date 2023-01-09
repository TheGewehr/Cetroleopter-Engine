#include "ModuleAudio.h"
#include "Application.h"
#include "Globals.h"


ModuleAudio::ModuleAudio(bool start_enabled) : Module(start_enabled)
{
	
}

ModuleAudio::~ModuleAudio()
{
}

bool ModuleAudio::Init()
{
	LOG("Initializing ModuleAudio");


	return true;
}

update_status ModuleAudio::Update(float dt)
{
	

	return UPDATE_CONTINUE;
}

bool ModuleAudio::CleanUp()
{
	LOG("Cleaning ModuleAudio");

	return true;
}