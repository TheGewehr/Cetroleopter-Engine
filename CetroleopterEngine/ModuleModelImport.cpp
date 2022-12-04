#include "glew/include/GL/glew.h"

#include "Application.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleModelImport.h"
#include "ModuleGameObject.h"
#include "ModuleTransformComponent.h"
#include "ModuleMeshComponent.h"
#include "ModuleTextureComponent.h"
#include "Component.h"

#include "assimp/include/cimport.h"
#include "assimp/include/scene.h"
#include "assimp/include/postprocess.h"
#include "physfs.h"

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

void ModuleModelImport::Import_Mesh(MeshComponent* mesh)
{

}

bool ModuleModelImport::Save_Mesh(MeshComponent* mesh, char** pointer)
{
	bool success = true;

	// amount of indices / vertices / colors / normals / texture_coords / AABB
	uint ranges[2] = { mesh->mesh.num_indices, mesh->mesh.num_vertices };
	uint size = sizeof(ranges) + sizeof(uint) * mesh->mesh.num_indices + sizeof(float) * mesh->mesh.num_vertices * 3;
	char* fileBuffer = new char[size]; // Allocate
	char* cursor = fileBuffer;
	uint bytes = sizeof(ranges); // First store ranges
	memcpy(cursor, ranges, bytes);
	cursor += bytes;
	// Store indices
	bytes = sizeof(uint) * mesh->mesh.num_indices;
	memcpy(cursor, mesh->mesh.indices, bytes);
	cursor += bytes;

	bytes = sizeof(uint) * mesh->mesh.num_vertices;
	memcpy(cursor, mesh->mesh.vertices, bytes);
	cursor += bytes;

	//bytes = sizeof(uint) * mesh->mesh.num_UVs;
	//memcpy(cursor, mesh->mesh.id_UV, bytes);
	//cursor += bytes;


	std::string filePath = std::string("Library/Meshes/") + mesh->GetName() + std::string(MESH_FILE_EXTENSION);

	PHYSFS_file* fs_file;																	// PHYSFS_file is a PhysFS file handle.
	/**/																					// Whenever an op (r,w, etc) is done to a file, a ptr to one of these file handles is returned.

	fs_file = PHYSFS_openWrite(filePath.c_str());

	if (fs_file != nullptr)
	{
		uint written = (uint)PHYSFS_write(fs_file, fileBuffer, 1, size);						// Method that writes data from a PHYSFS_File to the given buffer. Returns the n of bytes written.

		if (written != size)																// Checks whether or not all the data has been written.
		{
			LOG("[error] File System error while writing to file %s: %s", filePath, PHYSFS_getLastError());
		}

		bool closesCorrectly = PHYSFS_close(fs_file);						// Method that closes a PhysFS file handle. Returns 1 on success.
		if (closesCorrectly == false)
		{
			LOG("[ERROR] File System error while closing file %s: %s", filePath, PHYSFS_getLastError());
		}
	}
	else
	{
		LOG("[ERROR] File System error while opening file %s: %s", filePath, PHYSFS_getLastError());
	}

	return success;
}

bool ModuleModelImport::Load_Mesh(MeshComponent* mesh, const char* pointer)
{
	bool success = true;



	return success;
}

void ModuleModelImport::LoadModel_Textured(ModuleGameObject* objMain, const char* meshPath, const char* texturePath)
{
	//GameObject newGameObject;

	//Mesh Loading part

	const aiScene* scene = aiImportFile(meshPath, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		//MeshVertexData vertexData;
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		//TextureData textureData;
		//textureData.texture_ID = 0;
		//textureData.image_ID = 0;

		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			MeshComponent* meshComponent;
			TextureComponent* textureComponent;
			TextureData* texture = new TextureData();
			if (i == 0)
			{
				meshComponent = (MeshComponent*)objMain->GetComponentOfType(ComponentTypes::MESH);
				textureComponent = (TextureComponent*)objMain->GetComponentOfType(ComponentTypes::TEXTURE);
			}
			if (i > 0)
			{
				ModuleGameObject* child = App->scene_intro->CreateEmptyGameObject(objMain, "child");

				meshComponent = (MeshComponent*)child->GetComponentOfType(ComponentTypes::MESH);
				textureComponent = (TextureComponent*)child->GetComponentOfType(ComponentTypes::TEXTURE);
			}

			meshComponent->mesh.num_vertices = scene->mMeshes[i]->mNumVertices;
			meshComponent->mesh.vertices = new float[meshComponent->mesh.num_vertices * 3];
			memcpy(meshComponent->mesh.vertices, scene->mMeshes[i]->mVertices, sizeof(float3) * meshComponent->mesh.num_vertices);
			LOG("New mesh with %d vertices", meshComponent->mesh.num_vertices);

			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				meshComponent->mesh.num_indices = scene->mMeshes[i]->mNumFaces * 3;
				meshComponent->mesh.indices = new uint[meshComponent->mesh.num_indices]; // assume each face is a triangle

				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&meshComponent->mesh.indices[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
			}

			if (scene->mMeshes[i]->HasTextureCoords(0))
			{
				meshComponent->mesh.num_UVs = scene->mMeshes[i]->mNumVertices;
				meshComponent->mesh.texture_coords_indices = new float[meshComponent->mesh.num_UVs * 3];
				memcpy(meshComponent->mesh.texture_coords_indices, scene->mMeshes[i]->mTextureCoords[0], meshComponent->mesh.num_UVs * sizeof(float3));
				meshComponent->mesh.meshTexturesData.texture_ID = scene->mMeshes[i]->mMaterialIndex;
			}
			

			glGenBuffers(1, &meshComponent->mesh.id_vertex);
			glBindBuffer(GL_ARRAY_BUFFER, meshComponent->mesh.id_vertex);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * meshComponent->mesh.num_vertices * 3, meshComponent->mesh.vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &meshComponent->mesh.id_index);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshComponent->mesh.id_index);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * meshComponent->mesh.num_indices, meshComponent->mesh.indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glGenBuffers(1, &(meshComponent->mesh.id_UV));
			glBindBuffer(GL_ARRAY_BUFFER, meshComponent->mesh.id_UV);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * meshComponent->mesh.num_UVs * 3, meshComponent->mesh.texture_coords_indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



			// Mesh file format Save/Load part

			char* pointer = nullptr;
			bool success;
			success = Save_Mesh(meshComponent, &pointer);

			if (success == true)
			{
				success = Load_Mesh(meshComponent, pointer);

				if(success == false) LOG("Error loading mesh from custom file format");
			}
			else
			{
				LOG("Error saving mesh to custom file format");
			}


			//Texture Loading part

			if (texturePath != nullptr)
			{

				ilGenImages(1, (ILuint*)&texture->image_ID);
				ilBindImage(texture->image_ID);

				char* data = nullptr;
				uint file_size = App->moduleFS->Load(texturePath, &data);

				ILenum fileType = IL_TYPE_UNKNOWN;

				if (App->moduleFS->GetFileExtension(texturePath) == "png")
				{
					fileType = IL_PNG;
				}

				if (App->moduleFS->GetFileExtension(texturePath) == "dds")
				{
					fileType = IL_DDS;
				}

				if (ilLoadL(fileType, (const void*)data, file_size))
				{
					if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
					{
						LOG("Texture correctly loaded from path: %s", texturePath);

						texture->texture_ID = ilutGLBindTexImage();

						glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

						glGenTextures(1, (GLuint*)&texture->texture_ID);
						glBindTexture(GL_TEXTURE_2D, texture->texture_ID);

						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

						glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
						glGenerateMipmap(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, 0);


					}
					else LOG("ERROR converting image: %s", iluErrorString(ilGetError()));
				}
				else
				{
					LOG("ERROR loading image: %s", iluErrorString(ilGetError()));
					ilDeleteImages(1, &texture->image_ID);
				}

				if (texture->texture_ID != 0)
				{
					texture->path = texturePath;
					texture->width = ilGetInteger(IL_IMAGE_WIDTH);
					texture->height = ilGetInteger(IL_IMAGE_HEIGHT);
					meshComponent->mesh.path = meshPath;
					meshComponent->mesh.meshTexturesData.path = texturePath;
					meshComponent->mesh.meshTexturesData.texture_ID = texture->texture_ID;
					meshComponent->mesh.meshTexturesData.width = ilGetInteger(IL_IMAGE_WIDTH);
					meshComponent->mesh.meshTexturesData.height = ilGetInteger(IL_IMAGE_HEIGHT);

					textureComponent->objectTexture = texture;
					textureComponent->textures.push_back(texture);
				}
			}
			else
			{
				LOG("ERROR loading image from path: %s - Or object does simply not have any texture", texturePath);
				textureComponent->objectTexture = nullptr;
			}

			//newGameObject.meshes.push_back(vertexData);
		}

		

		//newGameObject.textures.push_back(textureData);

		//App->moduleGameObject->objects.push_back(newGameObject);
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene % s", meshPath);
	}
}

uint ModuleModelImport::LoadTexture(const char* path)
{
	//GameObject newGameObject;

	TextureData textureData;

	textureData.texture_ID = 0;
	textureData.image_ID = 0;

	//MeshComponent* meshComponent;
	//TextureComponent* textureComponent;
	//TextureData* texture = new TextureData();
	//textureComponent = (TextureComponent*)objMain->GetComponentOfType(ComponentTypes::TEXTURE);

	if (path != nullptr)
	{

		ilGenImages(1, (ILuint*)&textureData.image_ID);
		ilBindImage(textureData.image_ID);

		if (ilLoadImage(path))
		{
			if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
			{
				LOG("Texture correctly loaded from path: %s", path);

				textureData.texture_ID = ilutGLBindTexImage();

				glGenTextures(1, (GLuint*)&textureData.texture_ID);
				glBindTexture(GL_TEXTURE_2D, textureData.texture_ID);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
				glGenerateMipmap(GL_TEXTURE_2D);
				
			}
			else LOG("ERROR converting image: %s", iluErrorString(ilGetError()));
		}
		else LOG("ERROR loading image: %s", iluErrorString(ilGetError()));
	}
	else LOG("ERROR loading image from path: %s", path);

	//textureData.path = path;
	if (textureData.texture_ID != 0)
	{
		textureData.path = path;
	}
	//newGameObject.textures.push_back(textureData);

	//App->moduleGameObject->objects.push_back(newGameObject);

	return textureData.texture_ID;
}



uint ModuleModelImport::CheckerTexture()
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


	uint textureID = 0;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, (GLuint*)&textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}