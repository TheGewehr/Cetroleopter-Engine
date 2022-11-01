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
	

	/*template<typename T>
	T* GetComponent()const
	{
		COMPONENT_TYPE type = T::GetType();

		if (type == COMPONENT_TYPE::TRANSFORM)
			return (T*)transform;

		for (uint i = 0; i < components.size(); ++i)
		{
			if (components[i]->GetType() == type)
			{
				return (T*)components[i];
			}
		}
		return nullptr;
	}*/
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