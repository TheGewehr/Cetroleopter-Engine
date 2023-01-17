#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "ModuleGameObject.h"
#include "ModuleCamera3D.h"
#include "ModuleCameraComponent.h"
#include "ModuleMeshComponent.h"
#include "ModuleTransformComponent.h"
#include "ModuleAudioSourceComponent.h"
#include "ModuleAudioListenerComponent.h"
#include "MainMenuBar.h"
#include "ModuleAudio.h"


#include "Game/Library/Sounds/Wwise_IDs.h"

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

	//App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "BakerHouse"), "Assets/BakerHouse_BIG.fbx", "Assets/bakeHouse.png");

	App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Ground"), "Assets/railway_scene/ground.fbx", "Assets/railway_scene/TexturesCom_PolishedConcreteFloor_1024_alb.png");
	//App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Lights"), "Assets/railway_scene/lights.fbx", "Assets/railway_scene/black.png");
	App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Pipes"), "Assets/railway_scene/pipes.fbx", "Assets/railway_scene/iron_rusted4_basecolor.png");
	App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Rail"), "Assets/railway_scene/rail.fbx", "Assets/railway_scene/railway.png");
	App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Tube"), "Assets/railway_scene/tube.fbx", "Assets/railway_scene/TexturesCom_ConcreteWall_1024_albedo.png");
	App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Cables"), "Assets/railway_scene/cables.fbx", "Assets/railway_scene/black.png");
	App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "RandomComputer"), "Assets/railway_scene/random_computer.fbx", "Assets/railway_scene/computer.png");
	App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Train"), "Assets/railway_scene/train_posV2.fbx", "Assets/railway_scene/train_inverted.png");

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));


	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (App->scene_intro->gameObjects[i]->GetName() == "Train6")
		{
			App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->SetSoundID(AK::EVENTS::TRAINPLAY);
			//App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::TRAINPLAY);
		}
		if (App->scene_intro->gameObjects[i]->GetName() == "RandomComputer5")
		{
			App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->SetSoundID(AK::EVENTS::WINDOWS);
			App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::WINDOWS);

			App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->SetSoundID(AK::EVENTS::MUSICLOOPPLAY);
			//App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::MUSICLOOPPLAY);
		}
	}

	sceneTimer = 0;
	trainTimer = 0;

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
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			if (App->scene_intro->gameObjects[i]->GetName() == "RandomComputer5")
			{
				//gameObjects.at(i)->GetAudioSourceComponent()->SetSoundID(AK::EVENTS::TRAIN);
				App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->SetPosition(App->scene_intro->gameObjects[i]->GetTransformComponent()->position.x,
					App->scene_intro->gameObjects[i]->GetTransformComponent()->position.y,
					App->scene_intro->gameObjects[i]->GetTransformComponent()->position.z);
				gameObjects.at(i)->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::WINDOWS);
			}
		}
		

		if (App->scene_intro->gameObjects[i]->isObjectSelected_ == true)
		{
			glPolygonMode(GL_FRONT, GL_LINE);
			App->camera->mainCamera->frustum.GetCornerPoints(App->scene_intro->gameObjects[i]->GetMeshComponent()->bboxPoints);
			App->camera->mainCamera->DrawBoundingBox(App->scene_intro->gameObjects[i]->GetMeshComponent()->bboxPoints, App->camera->mainCamera->frustumColor);
		}

		if (App->renderer3D->wireframeMode == false)
		{
			glPolygonMode(GL_FRONT, GL_FILL);
		}

		if (App->scene_intro->gameObjects[i]->GetName() == "Train6")
		{
			float trainPosition = (15.f * trainTimer);
			App->scene_intro->gameObjects[i]->GetTransformComponent()->SetPosition(0.f, 0.f, trainPosition - 1500.f);

			if (trainTimer >= 300)
			{
				trainTimer = 0;
			}

			

			App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->SetPosition(App->scene_intro->gameObjects[i]->GetTransformComponent()->position.x,
				App->scene_intro->gameObjects[i]->GetTransformComponent()->position.y,
				App->scene_intro->gameObjects[i]->GetTransformComponent()->position.z);
		}

		if (App->scene_intro->gameObjects[i]->GetName() == "Ground")
		{
			App->scene_intro->gameObjects[i]->GetTransformComponent()->SetPosition(0.f, 0.5f, 0);
		}

		gameObjects.at(i)->Render();
	}

	

	if (App->moduleUi->mainMenuBar->counterON == true)
	{
		sceneTimer++;
		trainTimer++;
	}

	if (App->camera->mainCamera->Position.z > -400 && App->camera->mainCamera->Position.z < 400)
	{
		App->moduleAudio->soundEffectType_ID = SoundEffectType_ID::REVERB;
	}
	else
	{
		App->moduleAudio->soundEffectType_ID = SoundEffectType_ID::NONE;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	

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

bool ModuleSceneIntro::SaveRequest()
{
	
	json_object_dotset_string(json_object(App->save_load->sceneFile),"Scene01.Name", name.c_str());
	json_object_dotset_number(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.Size", gameObjects.size());	

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects.at(i)->SaveObject(i);		
	}

	return true;
}

bool ModuleSceneIntro::LoadRequest()
{
	name = (char)json_object_dotget_string(json_object(App->save_load->sceneFile), "Scene01.Name");
	int listSize = (int)json_object_dotget_number(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.Size");
	
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects.at(i)->CleanUp();
	}

	gameObjects.clear();

	for (int i = 0; i < listSize; i++)
	{
		gameObjects.push_back(new ModuleGameObject(-1, "Missigno", true));		
	}

	for (int i = 0; i < listSize; i++)
	{
		gameObjects.at(i)->LoadObject(i);
	}

	return true;
}
