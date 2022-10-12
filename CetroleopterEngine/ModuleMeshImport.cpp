#include "glew/include/GL/glew.h"

#include "Application.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleMeshImport.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

//#include "SDL\include\SDL_opengl.h"

#pragma comment (lib, "assimp/libx86/assimp-vc142-mt.lib")
//#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

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
			
			VertexBuffer(vertexData.vertices, vertexData.num_vertices, vertexData.id_vertex);
			IndexBuffer(vertexData.indices, vertexData.num_indices, vertexData.id_index);
			//TextureBuffer();
		}
		aiReleaseImport(scene);
		
	}
	else LOG("Error loading scene % s", path);

}

void ModuleMeshImport::LoadTexture()
{
	
}

void ModuleMeshImport::VertexBuffer(float* vertices, uint& size, uint& id_vertex)
{
	glGenBuffers(1, (GLuint*)&(id_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleMeshImport::IndexBuffer(uint* indices, uint& size, uint& id_index)
{
	glGenBuffers(1, (GLuint*)&(id_index));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * size, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleMeshImport::TextureBuffer()
{
	
}

void ModuleMeshImport::DeleteBuffer(uint& type)
{
	glDeleteBuffers(1, &(GLuint)type);
}
