#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleMeshImport.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#pragma comment (lib, "assimp/libx86/assimp-vc142-mt.lib")

ModuleMeshImport::ModuleMeshImport(bool start_enabled) : Module(start_enabled = true)
{
	
}

ModuleMeshImport::~ModuleMeshImport()
{
}

bool ModuleMeshImport::Init()
{
	

	return true;
}

update_status ModuleMeshImport::Update(float dt)
{





	return UPDATE_CONTINUE;
}

bool ModuleMeshImport::CleanUp()
{
	

	return true;
}

void ModuleMeshImport::LoadModel()
{

}

void ModuleMeshImport::LoadMesh()
{

}
