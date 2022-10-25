#include "glew/include/GL/glew.h"

#include "Application.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleFS.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#include "devIL/include/ilu.h"
#include "devIL/include/ilut.h"


#pragma comment (lib, "assimp/libx86/assimp-vc142-mt.lib")
#pragma comment (lib, "physFS/libx86/physfs.lib")


ModuleFS::ModuleFS(bool start_enabled) : Module(start_enabled = true)
{
	
}

ModuleFS::~ModuleFS()
{
}

bool ModuleFS::Init()
{

	return true;
}

update_status ModuleFS::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool ModuleFS::CleanUp()
{

	return true;
}