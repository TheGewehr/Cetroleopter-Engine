#ifndef _MESH_IMPORTER_H_
#define _MESH_IMPORTER_H_

#include "Application.h"
#include "Module.h"

#include "glew/include/GL/glew.h"

#define CHECKERS_HEIGHT 50
#define CHECKERS_WIDTH 50

struct TextureData
{
	uint texture_ID;
	uint image_ID;

	uint width;
	uint height;

	uint format;
	uint internalFormat;

	const void* texture = nullptr;
	std::string	path;
};

struct MeshVertexData
{

	uint id_index = 0; // index in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;

	uint id_UV = 0; // id of the UV
	uint num_UVs = 0;
	GLfloat* texture_coords_indices = nullptr;

	TextureData meshTexturesData;
};

class ModuleModelImport : public Module
{
public:
	ModuleModelImport(bool start_enabled = true);
	~ModuleModelImport();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void LoadModel(const char* meshPath, const char* texturePath); //Loads the model (meshes and its textures
	void LoadModelThroughMesh(const char* meshPath, const char* texturePath); //Loads the model (meshes and its textures)
	void LoadMesh(const char* path); //Loads the mesh
	uint LoadTexture(const char* path); //Loads the textures

	uint CheckerTexture();

public:
	std::vector<MeshVertexData> meshes;
	std::vector<TextureData> textures;

};

#endif // !_MESH_IMPORTER_H_