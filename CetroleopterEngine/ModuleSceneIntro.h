#pragma once
#include "Module.h"
//#include "p2DynArray.h"
#include "Globals.h"

class Primitive;
//class  PhysBody3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();


private:
	
};
