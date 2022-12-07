#ifndef _MODULE_MESH_COMPONENT_H_
#define _MODULE_MESH_COMPONENT_H_


#include "Globals.h"
#include "glmath.h"
//#include "ModuleGameObject.h"
#include "ModuleModelImport.h"
#include "Component.h"

class ModuleGameObject;
//class ModuleModelImport;
//struct MeshVertexData;

struct BB_Vertex
{

    BB_Vertex() {}

    vec3 Position;
    vec3 Normal;
    vec2 TexCoords;

    BB_Vertex(vec3 v)
    {
        Position = v;
    }

    BB_Vertex(vec v)
    {
        Position.x = v.x;
        Position.y = v.y;
        Position.z = v.z;
    }


};

class MeshComponent : public Component
{
public:
	MeshComponent(ModuleGameObject* base);
	~MeshComponent();

	bool Init();
	update_status Update();
	bool CleanUp();

    bool SaveComponent();
    bool LoadComponent();

public:

	MeshVertexData mesh;

	const char* meshPath;

    std::vector<BB_Vertex> bb_vertices;
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

