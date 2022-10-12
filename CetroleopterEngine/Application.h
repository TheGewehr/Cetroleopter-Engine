#pragma once

#include <vector>

//#include "p2List.h"
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleUi.h"
#include "ModuleModelImport.h"

//#include "ModulePhysics3D.h"

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleModelImport* modelImport;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleUi* moduleUi;
	
	//ModulePhysics3D* physics;

	bool debug;
	bool appExit = false;
	bool enginePaused = false;

private:

	Timer	ms_timer;
	float	dt;
	//p2List<Module*> list_modules;
	std::vector<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void OpenBrowserWebPage(const char* url)const;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};