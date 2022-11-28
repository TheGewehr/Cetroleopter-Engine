#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "ModuleGameObject.h"
//#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "BakerHouse"), "Assets/BakerHouse_BIG.fbx", "Assets/bakeHouse.png");

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");


	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	PlanePrimitive p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	if (App->debug == true)
	{
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			
		}
	}

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects.at(i)->Render();
		//gameObjects[i]->Render();
	}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{

	//App->renderer3D->RenderModels();



	return UPDATE_CONTINUE;
}

ModuleGameObject* ModuleSceneIntro::CreateEmptyGameObject(ModuleGameObject* parent, const char* name)
{
	if (parent == nullptr)
	{
		std::string gameObjName = name;

		if (!gameObjects.empty())
		{
			gameObjName += std::to_string(gameObjects.size());
		}
		ModuleGameObject* gameObject = new ModuleGameObject(gameObjects.size(), gameObjName, true);
		gameObjects.push_back(gameObject);
		return gameObject;
	}

	if (parent != nullptr)
	{
		ModuleGameObject* gameObject = new ModuleGameObject(parent->childs.size(), name, true);
		parent->childs.push_back(gameObject);
		return gameObject;

	}
}