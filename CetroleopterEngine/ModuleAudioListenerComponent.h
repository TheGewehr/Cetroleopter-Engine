#ifndef _MODULE_AUDIO_LISTENER_COMPONENT_H_
#define _MODULE_AUDIO_LISTENER_COMPONENT_H_


#include "Application.h"
#include "Globals.h"
#include "Component.h"
#include <AK/SoundEngine/Common/AkTypes.h>

class ModuleGameObject;
class WwiseObject;

class AudioListenerComponent : public Component
{
public:
	AudioListenerComponent(ModuleGameObject* base);
	~AudioListenerComponent();

	bool Init();
	update_status Update();
	bool CleanUp();	

	bool SaveRequest(int positionInList);
	bool LoadRequest(int positionInList);

public:

	WwiseObject* listener = nullptr;

};


#endif // !_MODULE_AUDIO_LISTENER_COMPONENT_H_

