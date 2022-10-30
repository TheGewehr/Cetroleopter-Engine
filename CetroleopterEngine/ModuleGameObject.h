#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Application.h"
#include "Module.h"
#include "ModuleModelImport.h"

struct TransformComponent
{
	//position
	//rotation
	//scale
};

struct GameObject
{
	uint objectID;

	TransformComponent transform;

	MeshVertexData mesh;
	TextureData texture;

	//std::vector<MeshVertexData> meshes;
};

class ModuleGameObject : public Module
{
public:
	ModuleGameObject(bool start_enabled = true);
	~ModuleGameObject();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void AddGameObject(GameObject object);


public:

	std::vector<GameObject> objects;

};

#endif // !_GAME_OBJECT