#include "ModuleAudio.h"
#include "Application.h"
#include "Globals.h"

#include "ModuleCameraComponent.h"
#include "ModuleTransformComponent.h"

#include "Include_Wwise.h"
#include "Wwise/IO/Win32/AkFilePackageLowLevelIOBlocking.h"
#include "Wwise/IO/Win32/AkDefaultIOHookBlocking.h"
#include "Wwise/SDK/include/AkDefaultIOHookBlocking.h"
#include "Wwise/SDK/include/AkFileHelpers.h"
#include <AK/Plugin/AkRoomVerbFXFactory.h>
#include "AK/SpatialAudio/Common/AkSpatialAudio.h"
//#include <AK/SoundEngine/Common/AkMemoryMgr.h>                   // Memory Manager interface
//#include <AK/SoundEngine/Common/AkModule.h>                     // Default memory manager
//
//#include <AK/SoundEngine/Common/IAkStreamMgr.h>                 // Streaming Manager
//#include <AK/Tools/Common/AkPlatformFuncs.h>                    // Thread defines
//#include <Wwise/IO/Win32/AkFilePackageLowLevelIOBlocking.h>     // Sample low-level I/O implementation
////#include <AK/SoundEngine/Common/AkSoundEngineExport.h>
////#include <AkFilePackageLowLevelIOBlocking.h>
//
//#include <AK/SoundEngine/Common/AkSoundEngine.h>                // Sound engine
//
//#include <AK/MusicEngine/Common/AkMusicEngine.h>                // Music Engine
//
//#include <AK/SpatialAudio/Common/AkSpatialAudio.h>              // Spatial Audio

CAkFilePackageLowLevelIOBlocking g_lowLevelIO;

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
    memSettings.uMaxNumPools = 20; // the original: AK::StreamMgr::GetDefaultSettings(memSettings);

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

    LoadWwiseBank("SoundBankName");
    

    //
    // Initialize Spatial Audio                     Gives errors don't know why since all the initialitation is copied from the library wiki
    // Using default initialization parameters
    //

    //AkSpatialAudioInitSettings settings; // The constructor fills AkSpatialAudioInitSettings with the recommended default settings.
    //if (AK::SpatialAudio::Init(&settings) != AK_Success) // original way: if (AK::SpatialAudio::Init(&settings) != AK_Success)
    //{
    //    assert(!"Could not initialize the Spatial Audio.");
    //    return false;
    //}

	return true;
}

update_status ModuleAudio::Update(float dt)
{
	

	return UPDATE_CONTINUE;
}

bool ModuleAudio::CleanUp() // The order below g_lowLevelIO.Term() (this one included) is important
{
	LOG("Cleaning ModuleAudio");
    // Documentation: https://www.audiokinetic.com/en/library/edge/?source=SDK&id=workingwithsdks_termination.html

    
    AK::MusicEngine::Term();

    AK::SoundEngine::Term();

    //AK::SpatialAudio::Term();  This one does not work despite being inn the documentation

    g_lowLevelIO.Term();

    if (AK::IAkStreamMgr::Get())
        AK::IAkStreamMgr::Get()->Destroy();

    AK::MemoryMgr::Term(); // Must be the last

	return true;
}

void ModuleAudio::LoadWwiseBank(const char* path)
{
    //SoundBank* new_bank = new SoundBank();
    std::string bank_path = "Library/Sounds";
    bank_path += path;
    bank_path += ".bnk";

    LoadBank(bank_path.c_str());

    std::string json_file = bank_path.substr(0, bank_path.find_last_of('.')) + ".json"; // Changing .bnk with .json
}

WwiseObject::WwiseObject(unsigned long idGO, const char* nameGO)
{
    AkGOId = idGO;
    name = nameGO;

    AKRESULT eResult = AK::SoundEngine::RegisterGameObj(AkGOId, name);
    if (eResult != AK_Success)
    {
        LOG("Failed to register GameObject to Wwise!");
    }
}

WwiseObject::~WwiseObject()
{
    AKRESULT eResult = AK::SoundEngine::UnregisterGameObj(AkGOId);
    if (eResult != AK_Success)
    {
        LOG("Failed to unregister GameObject from Wwise!");
    }
}

unsigned long WwiseObject::GetID()
{
    return AkGOId;
}

const char* WwiseObject::GetName()
{
    return name;
}

void WwiseObject::SetPosition(float x, float y, float z, float x_front, float y_front, float z_front, float x_top, float y_top, float z_top)
{
    position.X = -x;
    position.Y = y;
    position.Z = -z;

    front.X = x_front;
    front.Y = y_front;
    front.Z = z_front;
    top.X = x_top;
    top.Y = y_top;
    top.Z = z_top;

    float length_front = sqrt(pow(front.X, 2) + pow(front.Y, 2) + pow(front.Z, 2));
    float length_top = sqrt(pow(top.X, 2) + pow(top.Y, 2) + pow(top.Z, 2));

    //Normalize vectors
    front.X = front.X / length_front;
    front.Y = front.Y / length_front;
    front.Z = front.Z / length_front;
    top.X = top.X / length_top;
    top.Y = top.Y / length_top;
    top.Z = top.Z / length_top;

    //Check if the are orthogonals
    float dot_prod = top.X * front.X + top.Y * front.Y + top.Z * front.Z;

    if (dot_prod >= 0.0001)
        LOG("Vectors are not orthogonal!");

    AkSoundPosition sound_pos;
    sound_pos.Set(position, front, top);
    AKRESULT res = AK::SoundEngine::SetPosition((AkGameObjectID)AkGOId, sound_pos);
    if (res != AK_Success)
        LOG("Couldn't update position");
}

void WwiseObject::SetListener(unsigned long* id)
{
    AKRESULT res = AK::SoundEngine::SetListeners(AkGOId, (AkGameObjectID*)id, 1);
}

void WwiseObject::PlayEvent(const char* name)
{
    //if (AK::SoundEngine::PostEvent(name, AkGOId) == ERROR_INVALID_NAME)
    //{
    //    assert(!"invalid playing name");
    //}
    AK::SoundEngine::PostEvent(name, AkGOId);
    LOG("Playing event: %s", name);
}

void WwiseObject::PlayEvent_ID(unsigned long id)
{
    if (AK::SoundEngine::PostEvent(id, AkGOId) == AK_INVALID_PLAYING_ID)
    {
        assert(!"invalid playing id");
    }
}

void WwiseObject::PlayMusic_ID(unsigned long music_id)
{
    AK::SoundEngine::PostEvent(music_id, AkGOId, AK_EnableGetMusicPlayPosition);
}

void WwiseObject::PlayMusic(const char* music_name)
{
    AK::SoundEngine::PostEvent(music_name, AkGOId, AK_EnableGetMusicPlayPosition);
}

void WwiseObject::SetAuxiliarySends(AkReal32 value, const char* target_bus, AkGameObjectID listener_id)
{
    AkAuxSendValue reverb;
    reverb.listenerID = listener_id;
    reverb.auxBusID = AK::SoundEngine::GetIDFromString(target_bus);
    reverb.fControlValue = value;

    AKRESULT res = AK::SoundEngine::SetGameObjectAuxSendValues(AkGOId, &reverb, 1);
}

WwiseObject* CreateSoundObj(unsigned long id, const char* name, float x, float y, float z, bool is_default_listener)
{
    WwiseObject* emitter = nullptr;

    emitter = new WwiseObject(id, name);

    if (is_default_listener)
    {
        AkGameObjectID listener_id = emitter->GetID();
        AK::SoundEngine::SetDefaultListeners(&listener_id, 1);
        emitter->SetPosition(x, y, z, 1);
    }
    else
        emitter->SetPosition(x, y, z);

    return emitter;
}

AkBankID LoadBank(const char* name)
{
    AkBankID bankID;
    AKRESULT eResult = AK::SoundEngine::LoadBank(name, AK_DEFAULT_POOL_ID, bankID);
    if (eResult == AK_WrongBankVersion)
    {
        assert(!"WrongBankVersion!");
        return false;
    }
    else if (eResult != AK_Success)
    {
        assert(!"Could not load soundbank!");
        return false;
    }

    return bankID;
}
