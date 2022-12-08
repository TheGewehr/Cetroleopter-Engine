#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

//#include "Application.h"
#include <vector>
#include <string>
#include "Module.h"

#include "mathGeoLib/Geometry/AABB.h"
#include "mathGeoLib/Geometry/OBB.h"

//#include "ModuleModelImport.h"
//#include "Component.h"
//#include "ModuleTransformComponent.h"
//#include "ModuleTextureComponent.h"
//#include "ModuleMeshComponent.h"

enum class ComponentTypes;
class Component;
class TransformComponent;
class MeshComponent;
class TextureComponent;
class CameraComponent;

class ModuleGameObject
{
public:
	ModuleGameObject(uint obj_ID, std::string name, bool isActive);
	~ModuleGameObject();

	bool Init();
	update_status Update();
	void Render();
	bool CleanUp();

	bool GetObjectIsActive();
	void SetObjectActive(bool state);
	bool GetObjectIsSelected();
	void SelectObject();
	//std::string GetName();
	void SetName(const char* newName);
	std::string GetName();
	std::string GetMeshPath();
	std::string GetTexturePath();

	void AddChild(ModuleGameObject* child);
	void DeleteChild(ModuleGameObject* child);
	Component* GetComponentOfType(ComponentTypes type);

	// Getters for each possible components
	TransformComponent* GetTransformComponent();
	TextureComponent* GetTextureComponent();
	MeshComponent* GetMeshComponent();
	CameraComponent* GetCameraComponent();

	bool SaveObject(int positionInList);
	bool LoadObject(int positionInList);


public:

	std::vector<Component*> objectComponents;
	std::vector<ModuleGameObject*>	childs;

	ModuleGameObject* parent = nullptr;

	int currentSelectedObject = -1;

public:

	Component* componentMesh;
	Component* componentTexture;
	Component* componentTransform;
	Component* componentCamera;

	uint id_;
	std::string name_;
	bool isAtive_;
	bool isObjectSelected_ = false;
};

#endif // !_GAME_OBJECT