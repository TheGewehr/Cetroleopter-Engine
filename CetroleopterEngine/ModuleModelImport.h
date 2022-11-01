#ifndef _MESH_IMPORTER_H_
#define _MESH_IMPORTER_H_

#include "Application.h"
#include "Module.h"
#include "ModuleTransformComponent.h"

#include "glew/include/GL/glew.h"

#define CHECKERS_HEIGHT 50
#define CHECKERS_WIDTH 50

struct TransformComponent;

enum TextureMaterialType
{
	NONE = 0,
	DIFFUSE,
	METALLIC,
	ROUGHNESS,
	HEIGH_MAP,
	NORMAL_MAP,
	EMISSIVE
};

struct TextureData
{
	TextureMaterialType materialType; //Will be used later to load different texture materials

	uint texture_ID = 0;
	uint image_ID = 0;

	uint width = 0;
	uint height = 0;

	uint format = 0;
	uint internalFormat = 0;

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

	/*GLuint id_normal = 0;
	aiVector3D num_normals[3] = {};
	float* normals = nullptr;

	GLuint id_normalVertices = 0;
	GLfloat* normalVertices = nullptr;*/

	uint id_UV = 0; // id of the UV
	uint num_UVs = 0;
	GLfloat* texture_coords_indices = nullptr;

	TextureData meshTexturesData;
	std::string	path;

	TransformComponent* transform = nullptr;
};

class ModuleModelImport : public Module
{
public:
	ModuleModelImport(bool start_enabled = true);
	~ModuleModelImport();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void LoadModelAndTexture(const char* meshPath, const char* texturePath); //Loads the model (meshes and a texture)
	void LoadModel_Textured(const char* meshPath, const char* texturePath); //Loads the model (meshes and its textures) and assigns texture IDs to it
	void LoadMesh(const char* path); //Loads the mesh
	uint LoadTexture(const char* path); //Loads the textures

	uint CheckerTexture();

public:
	//std::vector<MeshVertexData> meshes;
	//std::vector<TextureData> textures;

};

#endif // !_MESH_IMPORTER_H_