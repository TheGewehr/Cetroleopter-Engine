#include "Application.h"


Application::Application() : debug(false)
{
	window = new ModuleWindow(true);
	input = new ModuleInput(true);
	modelImport = new ModuleModelImport(true);
	audio = new ModuleAudio();
	scene_intro = new ModuleSceneIntro(true);
	camera = new ModuleCamera3D(true);
	moduleUi = new ModuleUi(true);
	renderer3D = new ModuleRenderer3D(true);
	save_load = new ModuleSaveLoad(true);
	//physics = new ModulePhysics3D();

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(modelImport);
	AddModule(audio);
	AddModule(save_load);
	//AddModule(physics);
	
	// Scenes
	AddModule(scene_intro);

	// Renderer last!
	AddModule(moduleUi);
	AddModule(renderer3D);
}

Application::~Application()
{
	//p2List_item<Module*>* item = list_modules.getLast();
	std::vector<Module*>::reverse_iterator item = list_modules.rbegin();

	/*while(item != NULL)
	{
		delete item->data;
		item = item->prev;
	}*/
	while (item != list_modules.rend())
	{
		delete* item;
		item++;  // Has to be ++item; and NOT item++; if not it crashes with an asertion error - Nevermind, now its the other way round...
	}
}

bool Application::Init()
{
	bool ret = true;

	App = this;
	appExit = false;
	enginePaused = false;

	// Call Init() in all modules
	//p2List_item<Module*>* item = list_modules.getFirst();
	std::vector<Module*>::iterator item = list_modules.begin();

	/*while(item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}*/
	while (item != list_modules.end() && ret == true)
	{
		ret = (*item)->Init();
		++item;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	//item = list_modules.getFirst();
	item = list_modules.begin();

	/*while(item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}*/
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
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	//p2List_item<Module*>* item = list_modules.getFirst();
	std::vector<Module*>::iterator item = list_modules.begin();
	
	/*while(item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->PreUpdate(dt);
		item = item->next;
	}*/
	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PreUpdate(dt);
		++item;
	}

	//item = list_modules.getFirst();
	item = list_modules.begin();

	/*while(item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->Update(dt);
		item = item->next;
	}*/
	while (item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->Update(dt);
		++item;
	}

	//item = list_modules.getFirst();
	item = list_modules.begin();

	/*while(item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->PostUpdate(dt);
		item = item->next;
	}*/
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
	//p2List_item<Module*>* item = list_modules.getLast();
	std::vector<Module*>::reverse_iterator item = list_modules.rbegin();

	/*while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}*/
	while (item != list_modules.rend() && ret == true)
	{
		ret = (*item)->CleanUp();
		++item;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	//list_modules.add(mod);
	list_modules.push_back(mod);
}

void Application::OpenBrowserWebPage(const char* url)const
{
	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

Application* App = nullptr;
