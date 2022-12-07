
#include "Application.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleModelImport.h"
#include "ModuleGameObject.h"
#include "ModuleMeshComponent.h"
#include "ModuleTextureComponent.h"
#include "ModuleTransformComponent.h"
#include "ModuleCameraComponent.h"

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



	aabb.SetNegativeInfinity();
	obb.SetNegativeInfinity();

	aabbVertices = new float3[8];
	obbVertices = new float3[8];

	/*std::vector<BB_Vertex> vertices;
	vertices.push_back((BB_Vertex)(vec3(1.0, 1.0, 1.0)));
	vertices.push_back((BB_Vertex)(vec3(0.0f, 1.0, 1.0)));
	vertices.push_back((BB_Vertex)(vec3(1.0, 1.0, 0.0f)));
	vertices.push_back((BB_Vertex)(vec3(0.0f, 1.0, 0.0f)));
	vertices.push_back((BB_Vertex)(vec3(1.0, 0.0f, 1.0)));
	vertices.push_back((BB_Vertex)(vec3(0.0f, 0.0f, 1.0)));
	vertices.push_back((BB_Vertex)(vec3(0.0f, 0.0f, 0.0f)));
	vertices.push_back((BB_Vertex)(vec3(1.0, 0.0f, 0.0f)));*/
	
}

ModuleGameObject::~ModuleGameObject()
{
	//RELEASE_ARRAY(aabbVertices);
	//RELEASE_ARRAY(obbVertices);
}

bool ModuleGameObject::Init()
{


	return true;
}

update_status ModuleGameObject::Update()
{
	std::vector<MeshComponent*> meshesComponent;

	for (uint i = 0; i < objectComponents.size(); i++)
	{
		if (objectComponents[i]->IsComponentActive())
		{
			objectComponents[i]->Update();
		}

		if (objectComponents[i]->GetType() == ComponentTypes::MESH)
		{
			meshesComponent.push_back((MeshComponent*)objectComponents[i]);
		}
	}

	for (uint i = 0; i < meshesComponent.size(); ++i)
	{
		if (meshesComponent[i] == nullptr  || meshesComponent[i]->objMain_->componentMesh == nullptr)
		{
			continue;
		}

		obb = meshesComponent[i]->objMain_->componentMesh->objMain_->aabb;
		obb.Transform(GetTransformComponent()->GetWorldTransform());

		aabb.SetNegativeInfinity();
		aabb.Enclose(obb);
	}

	meshesComponent.clear();

	return UPDATE_CONTINUE;
}

void ModuleGameObject::Render()
{
	
	TransformComponent* transform = this->GetTransformComponent();
	App->renderer3D->RenderGameObjects(*this, transform->position);
	ModuleGameObject* base = this;
	for (int j = 0; j < base->childs.size(); j++)
	{
		App->renderer3D->RenderGameObjects(*base->childs.at(j), transform->position);
	}


	//Just for testing purposes
	//
	//std::vector<MeshComponent*> meshesComponent;
	//
	//for (uint i = 0; i < objectComponents.size(); i++)
	//{
	//
	//	if (objectComponents[i]->GetType() == ComponentTypes::MESH)
	//	{
	//		meshesComponent.push_back((MeshComponent*)objectComponents[i]);
	//	}
	//}
	//
	//for (uint i = 0; i < meshesComponent.size(); ++i)
	//{
	//	if (meshesComponent[i] == nullptr || meshesComponent[i]->objMain_->componentMesh == nullptr)
	//	{
	//		continue;
	//	}
	//
	//	obb = meshesComponent[i]->objMain_->componentMesh->objMain_->aabb;
	//	obb.Transform(GetTransformComponent()->GetWorldTransform());
	//
	//	aabb.SetNegativeInfinity();
	//	aabb.Enclose(obb);
	//}
	//
	//meshesComponent.clear();
	
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
	isObjectSelected_ = !isObjectSelected_;
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

CameraComponent* ModuleGameObject::GetCameraComponent()
{
	for (uint i = 0; i < objectComponents.size(); ++i)
	{
		if (objectComponents[i]->GetType() == ComponentTypes::CAMERA)
		{
			return (CameraComponent*)objectComponents[i];
		}
	}
	return nullptr;
}

bool ModuleGameObject::SaveObject()
{
	
	json_object_dotset_number(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID", id_);
	json_object_dotset_string(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID.Name", name_.c_str());
	json_object_dotset_boolean(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID.IsActive", isAtive_);

	if (this->GetMeshComponent() != nullptr)
	{
		this->GetMeshComponent()->SaveComponent();
	}
	else
	{
		json_object_dotset_boolean(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID.HasMeshComponent", id_);
	}

	if (this->GetTextureComponent() != nullptr)
	{
		this->GetTextureComponent()->SaveComponent();
	}
	else
	{
		json_object_dotset_boolean(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID.HasTextureComponent", id_);
	}

	if (this->GetTransformComponent() != nullptr)
	{
		this->GetTransformComponent()->SaveComponent();
	}
	else
	{
		json_object_dotset_boolean(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID.HasTransformComponent", id_);
	}

	return true;
}

bool ModuleGameObject::LoadObject()
{
	
	id_ = (int)json_object_dotget_number(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID");
	name_ = (char)json_object_dotget_string(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID.Name");
	isAtive_ = (bool)json_object_dotget_boolean(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID.IsActive");

	if ((bool)json_object_dotget_boolean(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID.HasMeshComponent") == true)
	{
		this->GetMeshComponent()->LoadComponent();

		if ((bool)json_object_dotget_boolean(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID.HasTextureComponent") == true)
		{
			this->GetTextureComponent()->LoadComponent();
		}
		else
		{

		}
	}	

	if((bool)json_object_dotget_boolean(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID.HasTransformComponent") == true)
	{
		this->GetTransformComponent()->LoadComponent();
	}

	return true;
}
