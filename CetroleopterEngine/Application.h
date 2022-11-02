#pragma once

#include <vector>

//#include "p2List.h"
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleUi.h"
#include "ModuleModelImport.h"
#include "ModuleSaveLoad.h"
#include "ModuleFS.h"
#include "ModuleGameObject.h"

#include "glew/include/GL/glew.h"
//#include "ModulePhysics3D.h"

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleFS* moduleFS;
	ModuleModelImport* modelImport;
	ModuleSaveLoad* save_load;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleUi* moduleUi;
	ModuleGameObject* moduleGameObject;
	
	
	bool debug;
	bool appExit = false;
	bool enginePaused = false;
	bool AppTitleScreenFull = false;

private:

	
	
	std::vector<Module*> list_modules;

	// FPS variables
	Timer	ms_timer;
	float	dt;
	int maxFps = 0;
	float framMsCap = 0.0f;

	Timer secondCount;
	int frameCount;
	int lastFps;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void OpenBrowserWebPage(const char* url)const;

	// For log Windows
	void AddLogFromApp(const char* str);

	int GetMaxFPS()const;
	void SetMaxFPS(int value);

	void GetSDLVersion(int& major, int& minor, int& patch);
	void GetCPU(int& count, int& size);
	float GetRAM();
	void GetCPUFeatures(bool& threeD, bool& altiVec, bool& avx, bool& avx2, bool& mmx, bool& rdtsc, bool& sse, bool& sse2, bool& sse3, bool& sse41, bool& sse42);
	const GLubyte* GetGPUVendor();
	const GLubyte* GetGPURenderer();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
	void UpdateFrameData(float frames, float ms);
};