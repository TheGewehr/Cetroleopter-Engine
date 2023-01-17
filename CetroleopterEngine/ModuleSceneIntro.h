#pragma once
#include "Module.h"
//#include "p2DynArray.h"
#include "Globals.h"
#include "Timer.h"

class Primitive;
class ModuleGameObject;
//class  PhysBody3D;
class WwiseObject;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	ModuleGameObject* CreateEmptyGameObject(ModuleGameObject* parent = nullptr, const char* name = nullptr);

	bool SaveRequest();
	bool LoadRequest();

public:
	std::vector<ModuleGameObject*> gameObjects = {};
	std::string name = "DefaultScene";

	ModuleGameObject* musicGameObject = nullptr;

	uint sceneTimer = 0;
	//uint trainTimer = 0;

	uint trainTimer;
};
