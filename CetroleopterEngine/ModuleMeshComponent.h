#ifndef _MODULE_MESH_COMPONENT_H_
#define _MODULE_MESH_COMPONENT_H_

#include "Application.h"
#include "Globals.h"
#include "glmath.h"
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

    bool SaveComponent(int positionInList);
    bool LoadComponent(int positionInList);

public:

	MeshVertexData mesh;

	const char* meshPath;

    float3* bb_vertices;
    std::vector<float> bb_normals;
    std::vector<float> bb_tex_coords;
    std::vector<uint> bb_indices;

    // Buffer data
    uint VBO;
    uint NBO;
    uint TBO;
    uint IBO;

    AABB bbox;
    vec bboxPoints[8];
};


#endif // !_MODULE_MESH_COMPONENT_H_

