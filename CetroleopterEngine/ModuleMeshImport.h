#ifndef _MESH_IMPORTER_H_
#define _MESH_IMPORTER_H_

#include "Application.h"
#include "Module.h"



class ModuleMeshImport : public Module
{
public:
	ModuleMeshImport(bool start_enabled = true);
	~ModuleMeshImport();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void LoadModel(); //Loads the model (meshes and its textures)
	void LoadMesh(); //Loads the mesh
	//void LoadTexture(); Not used for now //Loads the textures

public:

	
};

#endif // !_MESH_IMPORTER_H_