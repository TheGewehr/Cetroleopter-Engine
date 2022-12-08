#include "ModuleTextureComponent.h"
#include "ModuleGameObject.h"
#include "Component.h"

TextureComponent::TextureComponent(ModuleGameObject* base) : Component(base, ComponentTypes::TEXTURE, "Texture")
{
	
}

TextureComponent::~TextureComponent()
{
	
}

bool TextureComponent::Init()
{


	return true;
}

update_status TextureComponent::Update()
{


	return UPDATE_CONTINUE;
}

bool TextureComponent::CleanUp()
{


	return true;
}

bool TextureComponent::SaveComponent(int positionInList)
{
	std::string listPosition = std::to_string(positionInList);
	texturePath = textures[0]->path.c_str();
	json_object_dotset_string(json_object(App->save_load->sceneFile), std::string("Scene01.GameObjectsList." + listPosition + ".TextureComponent.Path").c_str(), texturePath);

	return false;
}

bool TextureComponent::LoadComponent(int positionInList)
{
	std::string listPosition = std::to_string(positionInList);

	texturePath = json_object_dotget_string(json_object(App->save_load->sceneFile), std::string("Scene01.GameObjectsList." + listPosition + ".TextureComponent.Path").c_str());

	return false;
}
