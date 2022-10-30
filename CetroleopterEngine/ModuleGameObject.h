#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Application.h"
#include "Module.h"

class ModuleGameObject : public Module
{
public:
	ModuleGameObject(bool start_enabled = true);
	~ModuleGameObject();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();


public:


};

#endif // !_GAME_OBJECT