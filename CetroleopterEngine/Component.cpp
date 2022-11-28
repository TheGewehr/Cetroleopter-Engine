
#include "Globals.h"
#include "Module.h"
#include "Component.h"
#include "ModuleGameObject.h"

Component::Component(ModuleGameObject* objMain, ComponentTypes componentType, const char* name, bool isActive) : type_(componentType), objMain_(objMain), name_(name), isActive_(isActive)
{

}

Component::~Component()
{

}

bool Component::Init()
{


	return true;
}

update_status Component::Update()
{


	return UPDATE_CONTINUE;
}

bool Component::CleanUp()
{


	return true;
}

bool Component::IsComponentActive() const
{
	return isActive_;
}

void Component::SetComponentIsActive(const bool& state)
{
	isActive_ = state;

	for (int j = 0; j < objMain_->childs.size(); j++)
	{
		for (int i = 0; i < objMain_->objectComponents.size(); i++)
		{
			objMain_->childs[j]->objectComponents[i]->SetComponentIsActive(objMain_->objectComponents[i]->IsComponentActive());
		}
	}
}

const char* Component::GetName() const
{
	return name_;
}

void Component::SetName(const char* newName)
{
	name_ = newName;
}

ComponentTypes Component::GetType()
{
	return type_;
}
