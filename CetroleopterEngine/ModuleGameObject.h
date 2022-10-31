#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Application.h"
#include "Module.h"
#include "ModuleModelImport.h"

//struct TransformComponent //Hacerlo en un modulo ComponentTransorm
//{
//	//position
//	//rotation
//	//scale
//};

struct GameObject
{
	uint objectID;

	std::vector<MeshVertexData> meshes;
	std::vector<TextureData> textures;
	//std::vector<TransformComponent> transformComponents;
};

class ModuleGameObject : public Module
{
public:
	ModuleGameObject(bool start_enabled = true);
	~ModuleGameObject();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();


public:

	std::vector<GameObject> objects;

};

#endif // !_GAME_OBJECT