#include "ModuleSaveLoad.h"
#include "Application.h"
#include "Globals.h"

#include "ConfigurationWindow.h"
#include "MainMenuBar.h"


ModuleSaveLoad::ModuleSaveLoad(bool start_enabled) : Module(start_enabled)
{
	
}

ModuleSaveLoad::~ModuleSaveLoad()
{
}

bool ModuleSaveLoad::Init()
{
	LOG("Initializing ModuleSaveLoad");

	// Load Configuration.json file
	configurationFile = json_parse_file("Configuration.json");

	sceneFile = json_parse_file("SceneSave.json");

	return true;
}

update_status ModuleSaveLoad::PostUpdate(float dt)
{
	if (saveConfigurationTrigger == true)
	{
		SaveConfiguration();

		saveConfigurationTrigger = false;
	}

	if (loadConfigurationTrigger == true)
	{
		LoadConfiguration();

		loadConfigurationTrigger = false;
	}

	if (saveSceneTrigger == true)
	{
		SaveScene();

		saveSceneTrigger = false;
	}

	if (loadSceneTrigger == true)
	{
		LoadScene();

		loadSceneTrigger = false;
	}

	return UPDATE_CONTINUE;
}

bool ModuleSaveLoad::CleanUp()
{
	LOG("Cleaning ModuleSaveLoad");

	// Free file ptr
	json_value_free(configurationFile);
	json_value_free(sceneFile);

	//delete configurationFile;

	return true;
}

bool ModuleSaveLoad::SaveConfiguration()
{
	// calling save requests
	App->moduleUi->configurationWindow->SaveRequest();
	App->moduleUi->mainMenuBar->SaveRequest();

	// Aplying save to the .json file
	json_serialize_to_file(configurationFile, "Configuration.json");

	return true;
}

bool ModuleSaveLoad::LoadConfiguration()
{
	// calling LoadRequest functions 
	App->moduleUi->configurationWindow->LoadRequest();
	App->moduleUi->mainMenuBar->LoadRequest();

	return true;
}

bool ModuleSaveLoad::SaveScene()
{
	// calling save requests
	App->scene_intro->SaveRequest();
	App->camera->SaveRequest();

	// Aplying save to the .json file
	json_serialize_to_file(sceneFile, "SceneSave.json");

	return true;
}

bool ModuleSaveLoad::LoadScene()
{
	// calling LoadRequest functions 
	App->scene_intro->LoadRequest();
	App->camera->LoadRequest();

	return true;
}
