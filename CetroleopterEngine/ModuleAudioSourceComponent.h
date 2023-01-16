#ifndef _MODULE_AUDIO_SOURCE_COMPONENT_H_
#define _MODULE_AUDIO_SOURCE_COMPONENT_H_


#include "Application.h"
#include "Globals.h"
#include "Component.h"
#include <AK/SoundEngine/Common/AkTypes.h>

class ModuleGameObject;
class WwiseObject;

class AudioSourceComponent : public Component
{
public:
	AudioSourceComponent(ModuleGameObject* base);
	~AudioSourceComponent();

	bool Init();
	update_status Update();
	bool CleanUp();	

	void PlayAudio();

	bool SaveRequest(int positionInList);
	bool LoadRequest(int positionInList);

	void SetSoundID(AkUniqueID ID);

public:

	WwiseObject* sound = nullptr;
	AkUniqueID sound_ID = 0;
};


#endif // !_MODULE_AUDIO_SOURCE_COMPONENT_H_

