
#include "Application.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleModelImport.h"
#include "ModuleGameObject.h"
#include "ModuleMeshComponent.h"
#include "ModuleTextureComponent.h"
#include "ModuleTransformComponent.h"

ModuleGameObject::ModuleGameObject(uint obj_ID, std::string name, bool isActive) : id_(obj_ID), name_(name), isAtive_(isActive)
{
	this->id_ = obj_ID;
	this->name_ = name;
	this->isAtive_ = isActive;

	componentMesh = new MeshComponent(this);
	componentTexture = new TextureComponent(this);
	componentTransform = new TransformComponent(this);

	objectComponents.push_back(componentMesh);
	objectComponents.push_back(componentTexture);
	objectComponents.push_back(componentTransform);
}

ModuleGameObject::~ModuleGameObject()
{
}

bool ModuleGameObject::Init()
{
	

	return true;
}

update_status ModuleGameObject::Update()
{
	for (uint i = 0; i < objectComponents.size(); i++)
	{
		if (objectComponents[i]->IsComponentActive())
		{
			objectComponents[i]->Update();
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleGameObject::Render()
{
	for (int i = 0; i < App->scene_intro->gameObjects.size(); i++)
	{
		TransformComponent* transform = (TransformComponent*)App->scene_intro->gameObjects[i]->GetComponentOfType(ComponentTypes::TRANSFORM);
		App->renderer3D->RenderGameObjects(*App->scene_intro->gameObjects.at(i), transform->position);
		ModuleGameObject* base = App->scene_intro->gameObjects.at(i);
		for (int j = 0; j < base->childs.size(); j++)
		{
			App->renderer3D->RenderGameObjects(*base->childs.at(j), transform->position);
		}
	}
}

bool ModuleGameObject::CleanUp()
{
	

	return true;
}

bool ModuleGameObject::GetObjectIsActive()
{
	return isAtive_;
}

void ModuleGameObject::SetObjectActive(bool state)
{
	isAtive_ = state;

	for (int i = 0; i < childs.size(); i++)
	{
		childs[i]->SetObjectActive(state);
	}
}

bool ModuleGameObject::GetObjectIsSelected()
{
	return isObjectSelected_;
}

void ModuleGameObject::SelectObject()
{

}

void ModuleGameObject::SetName(const char* newName)
{
	name_ = newName;
}

std::string ModuleGameObject::GetName()
{
	return name_;
}

std::string ModuleGameObject::GetMeshPath()
{
	for (int i = 0; i < App->scene_intro->gameObjects.size(); i++)
	{
		if (App->scene_intro->gameObjects[i]->GetObjectIsSelected())
		{
			MeshComponent* mesh = (MeshComponent*)App->scene_intro->gameObjects[i]->GetComponentOfType(ComponentTypes::MESH);

			return mesh->meshPath;
		}
	}

	return std::string("No path found");
}

std::string ModuleGameObject::GetTexturePath()
{
	for (int i = 0; i < App->scene_intro->gameObjects.size(); i++)
	{
		if (App->scene_intro->gameObjects[i]->GetObjectIsSelected())
		{
			TextureComponent* texture = (TextureComponent*)App->scene_intro->gameObjects[i]->GetComponentOfType(ComponentTypes::TEXTURE);

			return texture->texturePath;
		}
	}

	return std::string("No path found");
}

void ModuleGameObject::AddChild(ModuleGameObject* child)
{
	child->parent = this;

	childs.push_back(child);
}

void ModuleGameObject::DeleteChild(ModuleGameObject* child)
{
	for (uint i = 0; i < childs.size(); i++)
	{
		if (childs[i] == child)
		{
			childs.erase(childs.begin() + i);
			break;
		}
	}
}

Component* ModuleGameObject::GetComponentOfType(ComponentTypes type)
{
	Component* component = nullptr;

	for (uint i = 0; i < objectComponents.size(); ++i)
	{
		if (objectComponents[i]->type_ == type)
		{
			component = objectComponents[i];
		}
	}

	return component;
}

TransformComponent* ModuleGameObject::GetTransformComponent()
{
	return (TransformComponent*)componentTransform;
}

TextureComponent* ModuleGameObject::GetTextureComponent()
{
	for (uint i = 0; i < objectComponents.size(); ++i)
	{
		if (objectComponents[i]->GetType() == ComponentTypes::TEXTURE)
		{
			return (TextureComponent*)objectComponents[i];
		}
	}
	return nullptr;
}

MeshComponent* ModuleGameObject::GetMeshComponent()
{
	for (uint i = 0; i < objectComponents.size(); ++i)
	{
		if (objectComponents[i]->GetType() == ComponentTypes::MESH)
		{
			return (MeshComponent*)objectComponents[i];
		}
	}
	return nullptr;
}
