#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include <AK/SoundEngine/Common/AkTypes.h>

enum SoundEffectType_ID
{
	NONE,
	REVERB
};

class Application;

class ModuleAudio : public Module
{
public:

	ModuleAudio(bool start_enabled = true);

	// Destructor
	virtual ~ModuleAudio();

	bool Init();
	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void LoadWwiseBank(const char* path);

	void SetVolume(const char* rtpc, float volumeValue);

	AkGameObjectID MY_DEFAULT_LISTENER = 0;

	int soundEffectType_ID = 0;

};

class WwiseObject
{
public:
	WwiseObject(unsigned long idGO, const char* nameGO);
	~WwiseObject();
	unsigned long GetID();
	const char* GetName();
	void SetPosition(float x = 0, float y = 0, float z = 0, float x_front = 1, float y_front = 0, float z_front = 0, float x_top = 0, float y_top = 1, float z_top = 0);

	void SetListener(unsigned long* id);

	void PlayEvent(const char* name);
	void PlayEvent_ID(unsigned long id);

	void PlayMusic_ID(unsigned long music_id);
	void PlayMusic(const char* music_name);
	void SetAuxiliarySends(AkReal32 value, const char* target_bus, AkGameObjectID listener_id);

private:
	AkGameObjectID AkGOId;
	const char* name = nullptr;
	AkVector position = { 0, 0, 0 };
	AkVector top = { 0, 0, 0 };
	AkVector front = { 0, 0, 0 };
};

WwiseObject* CreateSoundObj(unsigned long id, const char* name, float x, float y, float z, bool is_default_listener = false);
AkBankID LoadBank(const char* name);

#endif // __ModuleAudio_H__