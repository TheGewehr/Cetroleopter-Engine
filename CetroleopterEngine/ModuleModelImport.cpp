#include "glew/include/GL/glew.h"

#include "Application.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleModelImport.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#include "devIL/include/ilu.h"
#include "devIL/include/ilut.h"

//#include "SDL\include\SDL_opengl.h"

#pragma comment (lib, "assimp/libx86/assimp-vc142-mt.lib")
//#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleModelImport::ModuleModelImport(bool start_enabled) : Module(start_enabled = true)
{
	
}

ModuleModelImport::~ModuleModelImport()
{
}

bool ModuleModelImport::Init()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);


	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION || ilGetInteger(ILU_VERSION_NUM) < ILU_VERSION || ilGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION)
	{
		LOG("Error: DevIL Version does not match with lib version.");
	}
	else
	{
		LOG("Initializing DevIL");
		ilInit();
		iluInit();
		ilutInit();
		ilutRenderer(ILUT_OPENGL);
	}

	return true;
}

update_status ModuleModelImport::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool ModuleModelImport::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();

	LOG("Shutting down DevIL");
	ilShutDown();

	return true;
}

void ModuleModelImport::LoadModel(const char* meshPath, const char* texturePath)
{
	LoadMesh(meshPath);
}

void ModuleModelImport::LoadMesh(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	MeshVertexData vertexData;
	//aiMesh* mesh = nullptr;
	
	if (scene != nullptr && scene->HasMeshes()) //The original: if (scene != nullptr && aiScene > HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array

		for (uint i = 0; i < scene->mNumMeshes; i++)
		{

			vertexData.num_vertices = scene->mMeshes[i]->mNumVertices;
			vertexData.vertices = new float[vertexData.num_vertices * 3];
			memcpy(vertexData.vertices, scene->mMeshes[i]->mVertices, sizeof(float) * vertexData.num_vertices * 3);
			LOG("New mesh with %d vertices", vertexData.num_vertices);

			//Can also be here??
			/*glGenBuffers(1, &vertexData.id_vertex);
			glBindBuffer(GL_ARRAY_BUFFER, vertexData.id_vertex);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.num_vertices * 3, vertexData.vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);*/

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

				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&vertexData.indices[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
			}

			glGenBuffers(1, &vertexData.id_vertex);
			glBindBuffer(GL_ARRAY_BUFFER, vertexData.id_vertex);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.num_vertices * 3, vertexData.vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &vertexData.id_index);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexData.id_index);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * vertexData.num_indices, vertexData.indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			meshes.push_back(vertexData);
		}

		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene % s", path);
	}

}

void ModuleModelImport::LoadTexture(const void* texture, uint width, uint height, uint format, uint internalFormat)
{
	uint textureID = 0;

	glGenTextures(1, (GLuint*)&textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, texture);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	//return textureID; <-- Necessary?
}



void ModuleModelImport::LoadCheckerTexture(GLuint textureID, const void* texture)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
}

void ModuleModelImport::CheckerTexture()
{
	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];

	for (int i = 0; i < CHECKERS_HEIGHT; i++)
	{
		for (int j = 0; j < CHECKERS_WIDTH; j++)
		{
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}

	}
}
