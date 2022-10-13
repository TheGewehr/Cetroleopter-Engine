#ifndef _MESH_IMPORTER_H_
#define _MESH_IMPORTER_H_

#include "Application.h"
#include "Module.h"

struct MeshVertexData
{
	uint id_index = 0; // index in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;
};

class ModuleModelImport : public Module
{
public:
	ModuleModelImport(bool start_enabled = true);
	~ModuleModelImport();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void LoadModel(const char* meshPath, const char* texturePath); //Loads the model (meshes and its textures)
	void LoadMesh(const char* path); //Loads the mesh
	void LoadTexture(const char* path); //Loads the textures

public:
	std::vector<MeshVertexData> meshes;
	
};

#endif // !_MESH_IMPORTER_H_