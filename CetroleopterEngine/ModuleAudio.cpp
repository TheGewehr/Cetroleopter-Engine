#include "ModuleAudio.h"
#include "Application.h"
#include "Globals.h"

#include "ModuleCameraComponent.h"
#include "ModuleTransformComponent.h"

#include "AkTypes.h"
#include "AkRoomVerbFXFactory.h"
#include <SoundEngine/Common/AkModule.h>
#include <SoundEngine/Common/AkMemoryMgr.h>

ModuleAudio::ModuleAudio(bool start_enabled) : Module(start_enabled)
{
	
}

ModuleAudio::~ModuleAudio()
{
}

bool ModuleAudio::Init()
{
	LOG("Initializing ModuleAudio");

	// Initializing default memory manager
	//AkMemSettings memSettings;
	//memSettings.uMaxNumPools = 20;
	//
	//if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
	//{
	//	assert(!"Could not create the memory manager.");
	//	return false;
	//}

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