#ifndef __Component_H__
#define __Component_H__

#include "Module.h"
#include "ModuleGameObject.h"
#include <string>

class ModuleGameObject;

enum class ComponentTypes
{
	NONE = 0,
	MESH,
	TEXTURE,
	TRANSFORM,
};

class Component
{
public:
	Component(ModuleGameObject* objMain, ComponentTypes componentType, const char* name, bool isActive = true);
	~Component();

public:

	bool IsComponentActive() const;
	void SetComponentIsActive(const bool& state);

	const char* GetName() const;
	void SetName(const char* newName);

public:
	ComponentTypes type_;

	ModuleGameObject* objMain_;

private:
	const char* name_;
	bool isActive_;
};

#endif // !__Component_H__