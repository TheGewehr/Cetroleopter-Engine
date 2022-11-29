#ifndef _MODULE_MESH_COMPONENT_H_
#define _MODULE_MESH_COMPONENT_H_


#include "Globals.h"
//#include "ModuleGameObject.h"
#include "ModuleModelImport.h"
#include "Component.h"

class ModuleGameObject;
//class ModuleModelImport;
//struct MeshVertexData;

class MeshComponent : public Component
{
public:
	MeshComponent(ModuleGameObject* base);
	~MeshComponent();

	bool Init();
	update_status Update();
	bool CleanUp();

public:

	MeshVertexData mesh;

	const char* meshPath;

};


#endif // !_MODULE_MESH_COMPONENT_H_

