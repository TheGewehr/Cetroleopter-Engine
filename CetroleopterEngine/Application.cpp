#include "Application.h"


Application::Application() : debug(false)
{
	window = new ModuleWindow(true);
	input = new ModuleInput(true);
	scene_intro = new ModuleSceneIntro(true);
	camera = new ModuleCamera3D(true);
	moduleUi = new ModuleUi(true);
	renderer3D = new ModuleRenderer3D(true);
	save_load = new ModuleSaveLoad(true);
	moduleFS = new ModuleFS(true);
	modelImport = new ModuleModelImport(true);
	moduleGameObject = new ModuleGameObject(true);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);	
	AddModule(input);
	AddModule(moduleFS);
	AddModule(modelImport);
	AddModule(moduleGameObject);	
	
	// Scenes
	AddModule(scene_intro);
	
	// Renderer last!
	AddModule(moduleUi);	
	AddModule(renderer3D);
	
	//Allways save and load as the last task
	AddModule(save_load);
	
}

Application::~Application()
{
	std::vector<Module*>::reverse_iterator item = list_modules.rbegin();

	while (item != list_modules.rend())
	{
		delete* item;
		++item;
	}
}

bool Application::Init()
{
	bool ret = true;

	App = this;
	appExit = false;
	enginePaused = false;
	AppTitleScreenFull = false;

	// Call Init() in all modules
	std::vector<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == true)
	{
		ret = (*item)->Init();
		++item;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.begin();

	while (item != list_modules.end() && ret == true)
	{
		ret = (*item)->Start();
		++item;
	}
	
	ms_timer.Start();
	
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	if (maxFps > 0)
		framMsCap = 1000 / (float)maxFps;
	
	float frameMs = ms_timer.Read();
	if (frameMs > 0 && frameMs < framMsCap && maxFps != 0)
	{
		SDL_Delay(framMsCap - frameMs);
	}
	
	frameCount++;
	if (secondCount.Read() >= 1000)
	{
		secondCount.Start();
		lastFps = frameCount;
		frameCount = 0;
	}
	
	UpdateFrameData(lastFps, (float)ms_timer.Read());
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	std::vector<Module*>::iterator item = list_modules.begin();
	
	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PreUpdate(dt);
		++item;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->Update(dt);
		++item;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PostUpdate(dt);
		++item;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	std::vector<Module*>::reverse_iterator item = list_modules.rbegin();

	while (item != list_modules.rend() && ret == true)
	{
		ret = (*item)->CleanUp();
		++item;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

void Application::OpenBrowserWebPage(const char* url)const
{
	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

void Application::AddLogFromApp(const char* str)
{
	if (App->moduleUi != nullptr)
	{
		std::string full_log = str;                                                   

		uint log_start = full_log.find_last_of("\\") + 1;                           
		uint log_end = full_log.size();                                            

		std::string short_log = full_log.substr(log_start, log_end);                

		App->moduleUi->AddLogFromModuleUi(short_log.c_str());
	}
}

int Application::GetMaxFPS() const
{
	return maxFps;
}

void Application::SetMaxFPS(int value)
{
	maxFps = value;
}

void Application::UpdateFrameData(float frames, float ms)
{
	if (moduleUi != nullptr)
	{
		moduleUi->UpdateFrameData(frames, ms);
	}
	
}

void Application::GetSDLVersion(int& major, int& minor, int& patch)
{
	SDL_version v;
	SDL_GetVersion(&v);
	major = v.major;
	minor = v.minor;
	patch = v.patch;
}

void Application::GetCPU(int& count, int& size)
{
	count = SDL_GetCPUCount();
	size = SDL_GetCPUCacheLineSize();
}

float Application::GetRAM()
{
	return (float)SDL_GetSystemRAM() / 1000.0f;
}

const GLubyte* GetGPUVendor()
{
	return glGetString(GL_VENDOR);
}

const GLubyte* GetGPURenderer()
{
	return glGetString(GL_RENDERER);
}

void Application::GetCPUFeatures(bool& threeD, bool& altiVec, bool& avx, bool& avx2, bool& mmx, bool& rdtsc, bool& sse, bool& sse2, bool& sse3, bool& sse41, bool& sse42)
{
	threeD = SDL_Has3DNow();
	altiVec = SDL_HasAltiVec();
	avx = SDL_HasAVX();
	avx2 = SDL_HasAVX2();
	mmx = SDL_HasMMX();
	rdtsc = SDL_HasRDTSC();
	sse = SDL_HasSSE();
	sse2 = SDL_HasSSE2();
	sse3 = SDL_HasSSE3();
	sse41 = SDL_HasSSE41();
	sse42 = SDL_HasSSE42();
}


Application* App = nullptr;
