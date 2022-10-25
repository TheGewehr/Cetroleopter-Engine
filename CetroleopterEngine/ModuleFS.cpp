#include "Application.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleFS.h"

//PhysFS
#include "physFS/include/physfs.h"
#include <fstream>
#include <filesystem>

#pragma comment (lib, "physFS/libx86/physfs.lib")
//Assimp
#include "assimp/include/cfileio.h"
#include "assimp/include/types.h"
#include "assimp/include/cimport.h"
#include "assimp/include/scene.h"
#include "assimp/include/postprocess.h"

#pragma comment (lib, "assimp/libx86/assimp-vc142-mt.lib")


ModuleFS::ModuleFS(bool start_enabled) : Module(start_enabled = true)
{
	// needs to be created before Init so other modules can use it
	char* base_path = SDL_GetBasePath();
	PHYSFS_init(nullptr);
	SDL_free(base_path);

	//Setting the working directory as the writing directory
	if (PHYSFS_setWriteDir(".") == 0)
		LOG("File System error while creating write dir: %s\n", PHYSFS_getLastError());

	AddPath("."); //ProjectFolder (working "Game" directory)
	AddPath("Assets"); //Assets folder
	
	// Make sure standard paths exist
	//Put all the different folder paths here
	const char* dirs[] = { CONFIG_FOLDER, ASSETS_FOLDER };

	for (uint i = 0; i < sizeof(dirs) / sizeof(const char*); ++i)
	{
		if (PHYSFS_exists(dirs[i]) == 0)
			PHYSFS_mkdir(dirs[i]);
	}
}

ModuleFS::~ModuleFS()
{
	PHYSFS_deinit();
}

bool ModuleFS::Init()
{
	LOG("Loading File System");

	// Ask SDL for a write dir
	char* write_path = SDL_GetPrefPath(ORGANIZATION, TITLE);

	SDL_free(write_path);


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

bool ModuleFS::AddPath(const char* filePath)
{
	bool ret = true;

	if (PHYSFS_mount(filePath, nullptr, 1) == 0)
	{
		LOG("PhysFS error when adding path: %s\n", PHYSFS_getLastError());
		ret = false;
	}
	else
	{
		ret = true;
	}
		

	return ret;
}

uint ModuleFS::Load(const char* file_path, char** buffer_path)
{
	uint ret = 0;

	PHYSFS_file* fs_file = PHYSFS_openRead(file_path);

	if (fs_file != nullptr)
	{
		PHYSFS_sint32 size = (PHYSFS_sint32)PHYSFS_fileLength(fs_file);

		if (size > 0)
		{
			*buffer_path = new char[size];
			uint readed = (uint)PHYSFS_read(fs_file, *buffer_path, 1, size);
			if (readed != size)
			{
				LOG("PhysFS error while reading from file %s: %s\n", file_path, PHYSFS_getLastError());
				RELEASE_ARRAY(buffer_path);
			}
			else
			{
				ret = readed;
			}
		}

		if (PHYSFS_close(fs_file) == 0)
			LOG("PhysFS error while closing file %s: %s\n", file_path, PHYSFS_getLastError());
	}
	else
		LOG("PhysFS error while opening file %s: %s\n", file_path, PHYSFS_getLastError());

	return ret;
}

uint ModuleFS::Save(const char* file_path, const void* buffer, unsigned int size, bool append)
{
	unsigned int ret = 0;

	bool overwrite = PHYSFS_exists(file_path) != 0;
	PHYSFS_file* fs_file = (append) ? PHYSFS_openAppend(file_path) : PHYSFS_openWrite(file_path);

	if (fs_file != nullptr)
	{
		uint written = (uint)PHYSFS_write(fs_file, (const void*)buffer, 1, size);
		if (written != size)
		{
			LOG("PhysFS error while writing to file %s: %s", file_path, PHYSFS_getLastError());
		}
		else
		{
			if (append == true)
			{
				LOG("Added %u data to [%s%s]", size, PHYSFS_getWriteDir(), file_path);

			}
			else if (overwrite == true)
			{
				LOG("File [%s%s] overwritten with %u bytes", PHYSFS_getWriteDir(), file_path, size);

			}
			else
			{
				LOG("New file created [%s%s] of %u bytes", PHYSFS_getWriteDir(), file_path, size);

			}

			ret = written;
		}

		if (PHYSFS_close(fs_file) == 0)
			LOG("PhysFS error while closing file %s: %s", file_path, PHYSFS_getLastError());
	}
	else
		LOG("PhysFS error while opening file %s: %s", file_path, PHYSFS_getLastError());

	return ret;
}

std::string ModuleFS::GetFileExtension(const char* file_path)
{
	if (file_path != nullptr)
	{
		std::string filePath = file_path;
		std::string extension = "";

		size_t dotPosition = filePath.find_last_of(".");

		extension = filePath.substr(dotPosition + 1);

		return extension;
	}
	else
	{
		std::string errorString = "GetFileExtension Error: File Path was nullptr";
	}
}
