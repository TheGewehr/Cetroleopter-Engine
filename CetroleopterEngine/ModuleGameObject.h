#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Application.h"
#include "Module.h"
#include "ModuleModelImport.h"
#include "Component.h"

enum class ComponentTypes;
class Component;

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


	// Getters for the components
	template<typename T>
	T* GetComponent()const
	{
		ComponentTypes type = T::GetType();

		if (type == ComponentTypes::TRANSFORM)
			return (T*)transform;

		for (uint i = 0; i < components.size(); ++i)
		{
			if (components[i]->GetType() == type)
			{
				return (T*)components[i];
			}
		}
		return nullptr;
	}

	template <typename T>
	bool GetComponents(std::vector<T*>& componentType)
	{
		ComponentTypes type = T::GetType();
		for (uint i = 0; i < components.size(); ++i)
		{
			if (components[i]->GetType() == type)
			{
				componentType.push_back((T*)components[i]);
			}
		}

		return  (componentType.empty()) ? false : true;
	}


public:

	std::vector<Component*> objectComponents;
	std::vector<ModuleGameObject*>	childs;

	ModuleGameObject* parent;

	int currentSelectedObject = -1;

private:

	uint id_;
	std::string name_;
	bool isAtive_;
	bool isObjectSelected_ = false;
};

#endif // !_GAME_OBJECT