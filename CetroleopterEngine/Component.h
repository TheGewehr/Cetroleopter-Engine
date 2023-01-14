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
	CAMERA,
	AUDIOSOURCE,
	AUDIOLISTENER
};

class Component : public Module
{
public:
	Component(ModuleGameObject* objMain, ComponentTypes componentType, const char* name, bool isActive = true);
	~Component();

	bool Init();
	update_status Update();
	bool CleanUp();


	bool IsComponentActive() const;
	void SetComponentIsActive(const bool& state);

	const char* GetName() const;
	void SetName(const char* newName);
	ComponentTypes GetType();

	
public:
	ComponentTypes type_;

	ModuleGameObject* objMain_;

private:
	const char* name_;
	bool isActive_;
};

#endif // !__Component_H__