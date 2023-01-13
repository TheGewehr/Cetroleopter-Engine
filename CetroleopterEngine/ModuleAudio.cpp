#include "ModuleAudio.h"
#include "Application.h"
#include "Globals.h"

#include "ModuleCameraComponent.h"
#include "ModuleTransformComponent.h"

#include <AK/SoundEngine/Common/AkMemoryMgr.h>                   // Memory Manager interface
#include <AK/SoundEngine/Common/AkModule.h>                     // Default memory manager

#include <AK/SoundEngine/Common/IAkStreamMgr.h>                 // Streaming Manager
#include <AK/Tools/Common/AkPlatformFuncs.h>                    // Thread defines
#include <Wwise/IO/Win32/AkFilePackageLowLevelIOBlocking.h>     // Sample low-level I/O implementation
//#include <AkFilePackageLowLevelIOBlocking.h>

#include <AK/SoundEngine/Common/AkSoundEngine.h>                // Sound engine

#include <AK/MusicEngine/Common/AkMusicEngine.h>                // Music Engine

#include <AK/SpatialAudio/Common/AkSpatialAudio.h>              // Spatial Audio

ModuleAudio::ModuleAudio(bool start_enabled) : Module(start_enabled)
{
	
}

ModuleAudio::~ModuleAudio()
{
}

bool ModuleAudio::Init()
{
	LOG("Initializing ModuleAudio");

	AkMemSettings memSettings;
	AK::MemoryMgr::GetDefaultSettings(memSettings);

	if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
	{
		assert(!"Could not create the memory manager.");
		return false;
	}

    AkStreamMgrSettings stmSettings;
    AK::StreamMgr::GetDefaultSettings(stmSettings);

    // Customize the Stream Manager settings here.

    if (!AK::StreamMgr::Create(stmSettings))
    {
        assert(!"Could not create the Streaming Manager");
        return false;
    }

    //
    // Create a streaming device with blocking low-level I/O handshaking.
    // Note that you can override the default low-level I/O module with your own. 
    //
    AkDeviceSettings deviceSettings;
    AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

    // Customize the streaming device settings here.

    // CAkFilePackageLowLevelIOBlocking::Init() creates a streaming device
    // in the Stream Manager, and registers itself as the File Location Resolver.
    if (g_lowLevelIO.Init(deviceSettings) != AK_Success)
    {
        assert(!"Could not create the streaming device and Low-Level I/O system");
        return false;
    }

    //
    // Create the Sound Engine
    // Using default initialization parameters
    //

    AkInitSettings initSettings;
    AkPlatformInitSettings platformInitSettings;
    AK::SoundEngine::GetDefaultInitSettings(initSettings);
    AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

    if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
    {
        assert(!"Could not initialize the Sound Engine.");
        return false;
    }

    //
    // Initialize the music engine
    // Using default initialization parameters
    //

    AkMusicSettings musicInit;
    AK::MusicEngine::GetDefaultInitSettings(musicInit);

    if (AK::MusicEngine::Init(&musicInit) != AK_Success)
    {
        assert(!"Could not initialize the Music Engine.");
        return false;
    }

    //
    // Initialize Spatial Audio
    // Using default initialization parameters
    //

    AkSpatialAudioInitSettings settings; // The constructor fills AkSpatialAudioInitSettings with the recommended default settings. 
    if (AK::SpatialAudio::Init(&settings) != AK_Success)
    {
        assert(!"Could not initialize the Spatial Audio.");
        return false;
    }

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