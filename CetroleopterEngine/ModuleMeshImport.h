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

class ModuleMeshImport : public Module
{
public:
	ModuleMeshImport(bool start_enabled = true);
	~ModuleMeshImport();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void LoadModel(); //Loads the model (meshes and its textures)
	void LoadMesh(const char* path); //Loads the mesh
	void LoadTexture(); //Loads the textures

public:

	
};

#endif // !_MESH_IMPORTER_H_