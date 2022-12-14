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

	// Store vertices
	bytes = sizeof(uint) * mesh->mesh.num_vertices;
	memcpy(cursor, mesh->mesh.vertices, bytes);
	cursor += bytes;

	// Store UVs (not working - pointer sintax errors)
	//bytes = sizeof(uint) * mesh->mesh.num_UVs;
	//memcpy(cursor, mesh->mesh.id_UV, bytes);
	//cursor += bytes;


	std::string filePath;
	if (mesh->objMain_->name_ == "child")
	{
		filePath = std::string("Library/Meshes/") + mesh->objMain_->name_.c_str() + std::to_string(childPostfix) + std::string(MESH_FILE_EXTENSION);
		childPostfix++;
	}
	else
	{
		filePath = std::string("Library/Meshes/") + mesh->objMain_->name_.c_str() + std::string(MESH_FILE_EXTENSION);
	}

	PHYSFS_file* fs_file;

	fs_file = PHYSFS_openWrite(filePath.c_str());

	if (fs_file != nullptr)
	{
		uint written = (uint)PHYSFS_write(fs_file, fileBuffer, 1, size);
		if (written != size)
		{
			LOG("PhysFS error while writing to file %s: %s", filePath, PHYSFS_getLastError());
		}

		bool closesCorrectly = PHYSFS_close(fs_file);
		if (closesCorrectly == false)
		{
			LOG("PhysFS error while closing file %s: %s", filePath, PHYSFS_getLastError());
		}
	}
	else
	{
		LOG("PhysFS error while opening file %s: %s", filePath, PHYSFS_getLastError());
	}

	filePath.clear();
	//Load_Mesh(mesh, cursor);

	return success;
}

bool ModuleModelImport::Load_Mesh(MeshComponent* mesh, char* pointer)
{
	bool success = true;

	char* cursor = pointer;

	// amount of indices / vertices / colors / normals / texture_coords
	uint ranges[5];
	uint bytes = sizeof(ranges);
	memcpy(ranges, cursor, bytes);
	cursor += bytes;
	mesh->mesh.num_indices = ranges[0];
	mesh->mesh.num_vertices = ranges[1];

	// Load indices
	bytes = sizeof(uint) * mesh->mesh.num_indices;
	mesh->mesh.indices = new uint[mesh->mesh.num_indices];
	memcpy(mesh->mesh.indices, cursor, bytes);
	cursor += bytes;

	// Load vertices
	bytes = sizeof(uint) * mesh->mesh.num_vertices;
	mesh->mesh.vertices = new float[mesh->mesh.num_vertices];
	memcpy(mesh->mesh.vertices, cursor, bytes);
	cursor += bytes;

	//Load UVs
	//UVs not stored so not loaded for the moment

	return success;
}

bool ModuleModelImport::Save_Texture(TextureComponent* texture, char** pointer)
{
	bool success = true;

	ilEnable(IL_FILE_OVERWRITE);
	ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);

	ILuint size = ilSaveL(IL_PNG, nullptr, 0);

	

	

	if (size > 0)
	{
		ILubyte* data = new ILubyte[size];

		if (ilSaveL(IL_PNG, data, size) > 0)
		{
			std::string filePath;
			//filePath = std::string("Library/Textures/") + texture->objMain_->name_.c_str() + std::string(TEXTURE_FILE_EXTENSION);
			filePath = std::string("Library/Textures/") + std::to_string(textPostfix) + std::string(TEXTURE_FILE_EXTENSION);
			textPostfix++;
			
			PHYSFS_file* fs_file;

			fs_file = PHYSFS_openWrite(filePath.c_str());

			if (fs_file != nullptr)
			{
				char* fileBuffer = (char*)data;
				uint written = (uint)PHYSFS_write(fs_file, fileBuffer, 1, size);
				if (written != size)
				{
					LOG("PhysFS error while writing to file %s: %s", filePath, PHYSFS_getLastError());
				}

				bool closesCorrectly = PHYSFS_close(fs_file);
				if (closesCorrectly == false)
				{
					LOG("PhysFS error while closing file %s: %s", filePath, PHYSFS_getLastError());
				}
			}
			else
			{
				LOG("PhysFS error while opening file %s: %s", filePath, PHYSFS_getLastError());
			}

			filePath.clear();
		}
	}

	Load_Texture(texture, pointer, size);

	return success;
}

bool ModuleModelImport::Load_Texture(TextureComponent* texture, char** pointer, uint size)
{
	bool success = true;

	ILuint il_image = 0;
	ilGenImages(1, &il_image);
	ilBindImage(il_image);

	success = ilLoadL(IL_TYPE_UNKNOWN, (const void*)pointer, size);

	if (success == true)
	{
		uint color_channels = ilGetInteger(IL_IMAGE_CHANNELS);
		if (color_channels == 3)
		{
			success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		}
		else if (color_channels == 4)
		{
			success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		}
		else
		{
			LOG("Texture has less than 3 color channels!");
		}
	}

	if (success == true)
	{
		ILinfo il_info;
		iluGetImageInfo(&il_info);

		ilGenImages(1, (ILuint*)&texture->objectTexture->image_ID);
		ilBindImage(texture->objectTexture->image_ID);

		if (il_info.Origin == IL_ORIGIN_UPPER_LEFT) iluFlipImage();

		texture->objectTexture->texture_ID = ilutGLBindTexImage();

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, (GLuint*)&texture->objectTexture->texture_ID);
		glBindTexture(GL_TEXTURE_2D, texture->objectTexture->texture_ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	ilDeleteImages(1, &il_image);

	return success;
}

void ModuleModelImport::LoadModel_Textured(ModuleGameObject* objMain, const char* meshPath, const char* texturePath)
{
	//GameObject newGameObject;

	//Mesh Loading part

	const aiScene* scene = aiImportFile(meshPath, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{

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

			// bounding box thing
			meshComponent->bbox.SetNegativeInfinity();
			float3* bbVertices = new float3[sizeof(float3) * meshComponent->mesh.num_vertices / 3];

			for (int l = 0; l < meshComponent->mesh.num_vertices / 3; l++)
			{


				bbVertices[l].x = meshComponent->mesh.vertices[l * 3];
				bbVertices[l].y = meshComponent->mesh.vertices[l * 3 + 1];
				bbVertices[l].z = meshComponent->mesh.vertices[l * 3 + 2];
			}

			meshComponent->bbox.Enclose(bbVertices, meshComponent->mesh.num_vertices / 3);
			meshComponent->bbox.GetCornerPoints(meshComponent->bboxPoints);


			// Mesh file format Save/Load part

			char* pointer = nullptr;
			bool success;
			success = Save_Mesh(meshComponent, &pointer);

			if (success == true)
			{
				//success = Load_Mesh(meshComponent, pointer);

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

				// Mesh file format Save/Load part

				char* pointer2 = nullptr;
				bool success2;
				success2 = Save_Texture(textureComponent, &pointer2);

				if (success2 == true)
				{
					//success2 = Load_Texture(textureComponent, &pointer2); Already inside Save_Texture();

					if (success2 == false) LOG("Error loading texture from custom file format");
				}
				else
				{
					LOG("Error saving texture to custom file format");
				}
			}
			else
			{
				LOG("ERROR loading image from path: %s - Or object does simply not have any texture", texturePath);
				textureComponent->objectTexture = nullptr;
			}

		}
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene % s", meshPath);
	}
}

uint ModuleModelImport::LoadTexture(ModuleGameObject* objMain, const char* path)
{
	//GameObject newGameObject;

	TextureData textureData;

	textureData.texture_ID = 0;
	textureData.image_ID = 0;

	TextureComponent* textureComponent;
	TextureData* texture = new TextureData();

	textureComponent = (TextureComponent*)objMain->GetComponentOfType(ComponentTypes::TEXTURE);

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

	
	if (textureData.texture_ID != 0)
	{
		textureData.path = path;

		textureData.width = ilGetInteger(IL_IMAGE_WIDTH);
		textureData.height = ilGetInteger(IL_IMAGE_HEIGHT);

		textureComponent->objectTexture = texture;
		textureComponent->textures.push_back(texture);
	}
	
	char* pointer = nullptr;
	bool success;
	success = Save_Texture(textureComponent, &pointer);

	if (success == true)
	{
		//success2 = Load_Texture(textureComponent, &pointer2); Already inside Save_Texture();

		if (success == false) LOG("Error loading texture from custom file format");
	}
	else
	{
		LOG("Error saving texture to custom file format");
	}

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