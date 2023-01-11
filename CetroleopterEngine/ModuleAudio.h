#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "SDL/include/SDL.h"


class Application;

class ModuleAudio : public Module
{
public:

	ModuleAudio(bool start_enabled = true);

	// Destructor
	virtual ~ModuleAudio();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();



};

#endif // __ModuleAudio_H__