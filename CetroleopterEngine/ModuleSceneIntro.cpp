#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
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

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	/*for (int n = 0; n < primitives.Count(); n++)
	{
		delete primitives[n];
	}
	primitives.Clear();*/

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


	/*for (uint n = 0; n < primitives.Count(); n++)
	{
		primitives[n]->Update();
	}*/

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	/*for (uint n = 0; n < primitives.Count(); n++)
	{
		primitives[n]->Render();
	}*/

	App->renderer3D->RenderModels();
	//App->renderer3D->RenderTextures(); Not finished and needed function??


	//glEnable(GL_TEXTURE_2D);

	return UPDATE_CONTINUE;
}

