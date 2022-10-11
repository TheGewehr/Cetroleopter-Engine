#include "Application.h"
#include "Globals.h"
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
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return true;
}

update_status ModuleMeshImport::Update(float dt)
{





	return UPDATE_CONTINUE;
}

bool ModuleMeshImport::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();

	return true;
}

void ModuleMeshImport::LoadModel()
{

}

void ModuleMeshImport::LoadMesh(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	MeshVertexData vertexData;
	aiMesh* mesh = nullptr;
	
	if (scene != nullptr && scene->HasMeshes()) //The real one: if (scene != nullptr && aiScene > HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array

		for (int i = 0; i < scene->mNumMeshes; i++)
		{

			vertexData.num_vertices = scene->mMeshes[i]->mNumVertices;
			vertexData.vertices = new float[vertexData.num_vertices * 3];
			memcpy(vertexData.vertices, scene->mMeshes[i]->mVertices, sizeof(float) * vertexData.num_vertices * 3);
			LOG("New mesh with %d vertices", vertexData.num_vertices);

			/* The original:
			vertexData.num_vertices = mesh->mNumVertices;
			vertexData.vertices = new float[vertexData.num_vertices * 3];
			memcpy(vertexData.vertices, mesh->mVertices, sizeof(float) * vertexData.num_vertices * 3);
			LOG("New mesh with %d vertices", vertexData.num_vertices);
			*/

			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				vertexData.num_indices = scene->mMeshes[i]->mNumFaces * 3;
				vertexData.indices = new uint[vertexData.num_indices]; // assume each face is a triangle
				for (uint j = 0; j < scene->mMeshes[j]->mNumFaces; ++j) // <-- ERROR
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else memcpy(&vertexData.indices[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
				}
			}
		}
		aiReleaseImport(scene);
	}
	else LOG("Error loading scene % s", path);

}

void ModuleMeshImport::LoadTexture()
{
	
}
