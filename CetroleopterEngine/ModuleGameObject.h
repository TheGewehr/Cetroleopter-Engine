#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Application.h"
#include "Module.h"
#include "ModuleModelImport.h"

struct MeshVertexData;
struct TextureData;

struct GameObject
{
	uint objectID;

	GameObject* parent = nullptr;

	std::vector<MeshVertexData> meshes;
	std::vector<TextureData> textures;
	std::vector<GameObject*> children;
	
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
	int currentSelectedObject = -1;

};

#endif // !_GAME_OBJECT