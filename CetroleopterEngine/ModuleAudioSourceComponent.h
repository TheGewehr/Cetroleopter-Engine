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

	bool SaveRequest(int positionInList);
	bool LoadRequest(int positionInList);

public:

	WwiseObject* sound = nullptr;

};


#endif // !_MODULE_CAMERA_COMPONENT_H_

