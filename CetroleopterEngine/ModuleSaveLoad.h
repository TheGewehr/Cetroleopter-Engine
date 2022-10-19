#ifndef __ModuleSaveLoad_H__
#define __ModuleSaveLoad_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "parson.h"


class Application;

class ModuleSaveLoad : public Module
{
public:

	ModuleSaveLoad(bool start_enabled = true);

	// Destructor
	virtual ~ModuleSaveLoad();

	bool Init();
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool SaveInJson();

};

#endif // __ModuleSaveLoad_H__